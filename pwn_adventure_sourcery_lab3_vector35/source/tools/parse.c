#include <stdint.h>

int 
parse_nib(const char *str, unsigned char *val)
{
    int rc = -1;
    char c = *str;

    if(c>='0' && c<='9') {
        *val = c-'0';
        rc = 0;
    }
    else if(c>='a' && c<='f') {
        *val = 10 + (c-'a');
        rc = 0;
    }
    else if(c>='A' && c<='F') {
        *val = 10 + (c-'A');
        rc = 0;
    }
    else {
        
    }

    return rc;
}

/* will parse 1 or 2 characters from its input 
    ... 0 characters results in error
    ... > 2 characters results in parsing of just the first two */
int 
parse_value_hex(const char *str, int limit, uint64_t *result)
{
    int i, rc = -1;
    uint64_t value;

    /* discards optional "0x" prefix */
    if(str[0]=='0' && (str[1]=='x' || str[1]=='X')) {
        str += 2;
    }

    /* empty string is error */
    if(!(*str))
        goto cleanup;

    /* loop over nibbles */
    for(value=0, i=0; str[i] && i<limit; ++i) { 
        unsigned char nib;

        if(parse_nib(str+i, &nib)) {
            goto cleanup;
        }

        value = (value<<4) + nib;
    }

    /* made it this far? success */
    *result = value;
    rc = 0;

    /* done */
    cleanup:

    if(rc) {
        
    }

    return rc;
}

int 
parse_uint8_hex(const char *str, uint8_t *result)
{
    int rc=-1;
    uint64_t value;

    if(parse_value_hex(str, 2, &value)) {
        
        goto cleanup;
    }

    rc = 0;
    *result = value & 0xFF;

    cleanup:
    return rc;
}

int 
parse_uint16_hex(const char *str, uint16_t *result)
{
    int rc=-1;
    uint64_t value;

    if(parse_value_hex(str, 4, &value)) {
        
        goto cleanup;
    }

    rc = 0;
    *result = value & 0xFFFF;

    cleanup:
    return rc;
}

int 
parse_uint32_hex(const char *str, uint32_t *result)
{
    int rc=-1;
    uint64_t value;

    if(parse_value_hex(str, 8, &value)) {
        
        goto cleanup;
    }

    rc = 0;
    *result = value & 0xFFFFFFFF;

    cleanup:
    return rc;
}

int 
parse_uint64_hex(const char *str, uint64_t *result)
{
    int rc=-1;
    uint64_t value;

    if(parse_value_hex(str, 16, &value)) {
        
        goto cleanup;
    }

    rc = 0;
    *result = value;

    cleanup:
    return rc;
}


