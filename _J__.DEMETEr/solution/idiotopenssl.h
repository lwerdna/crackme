// OPENSSL "forgets" to put all this shit in bn.h on windows build

#include "crypto\cryptlib.h"
#include "crypto\bn\bn_lcl.h"

/* TODO list
 *
 * 1. Check a bunch of "(words+1)" type hacks in various bignum functions and
 * check they can be safely removed.
 *  - Check +1 and other ugliness in BN_from_montgomery()
 *
 * 2. Consider allowing a BN_new_ex() that, at least, lets you specify an
 * appropriate 'block' size that will be honoured by bn_expand_internal() to
 * prevent piddly little reallocations. OTOH, profiling bignum expansions in
 * BN_CTX doesn't show this to be a big issue.
 */

/* How many bignums are in each "pool item"; */
#define BN_CTX_POOL_SIZE	16
/* The stack frame info is resizing, set a first-time expansion size; */
#define BN_CTX_START_FRAMES	32

/***********/
/* BN_POOL */
/***********/

/* A bundle of bignums that can be linked with other bundles */
typedef struct bignum_pool_item
	{
	/* The bignum values */
	BIGNUM vals[BN_CTX_POOL_SIZE];
	/* Linked-list admin */
	struct bignum_pool_item *prev, *next;
	} BN_POOL_ITEM;
/* A linked-list of bignums grouped in bundles */
typedef struct bignum_pool
	{
	/* Linked-list admin */
	BN_POOL_ITEM *head, *current, *tail;
	/* Stack depth and allocation size */
	unsigned used, size;
	} BN_POOL;
static void		BN_POOL_init(BN_POOL *);
static void		BN_POOL_finish(BN_POOL *);
#ifndef OPENSSL_NO_DEPRECATED
static void		BN_POOL_reset(BN_POOL *);
#endif
static BIGNUM *		BN_POOL_get(BN_POOL *);
static void		BN_POOL_release(BN_POOL *, unsigned int);

/************/
/* BN_STACK */
/************/

/* A wrapper to manage the "stack frames" */
typedef struct bignum_ctx_stack
	{
	/* Array of indexes into the bignum stack */
	unsigned int *indexes;
	/* Number of stack frames, and the size of the allocated array */
	unsigned int depth, size;
	} BN_STACK;
static void		BN_STACK_init(BN_STACK *);
static void		BN_STACK_finish(BN_STACK *);
#ifndef OPENSSL_NO_DEPRECATED
static void		BN_STACK_reset(BN_STACK *);
#endif
static int		BN_STACK_push(BN_STACK *, unsigned int);
static unsigned int	BN_STACK_pop(BN_STACK *);

/**********/
/* BN_CTX */
/**********/

/* The opaque BN_CTX type */
struct bignum_ctx
	{
	/* The bignum bundles */
	BN_POOL pool;
	/* The "stack frames", if you will */
	BN_STACK stack;
	/* The number of bignums currently assigned */
	unsigned int used;
	/* Depth of stack overflow */
	int err_stack;
	/* Block "gets" until an "end" (compatibility behaviour) */
	int too_many;
	};


