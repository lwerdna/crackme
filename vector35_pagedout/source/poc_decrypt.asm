; decrypt one block (ECB), use debugger to see xmm0 is expected plaintext
; when done

default rel

global start

section .data
	; test vector from:
	; https://github.com/ircmaxell/quality-checker/blob/master/ \
	; tmp/gh_18/PHP-PasswordLib-master/test/Data/Vectors/aes-ecb.test-vectors
	;
	key:
	db 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6
	db 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	plain:
	db 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
	db 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
	cipher:
	db 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
	db 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97

section .text
start:
	;call	read_block
	; key into xmm0
	movaps	xmm0, [key]

key_setup:
	movaps  xmm5, xmm0
	pxor    xmm2, xmm2
	aeskeygenassist xmm1, xmm0, 0x1
	call    key_combine
	aesimc  xmm6, xmm0
	aeskeygenassist xmm1, xmm0, 0x2
	call    key_combine
	aesimc  xmm7, xmm0
	aeskeygenassist xmm1, xmm0, 0x4
	call    key_combine
	aesimc  xmm8, xmm0
	aeskeygenassist xmm1, xmm0, 0x8
	call    key_combine
	aesimc  xmm9, xmm0
	aeskeygenassist xmm1, xmm0, 0x10
	call    key_combine
	aesimc  xmm10, xmm0
	aeskeygenassist xmm1, xmm0, 0x20
	call    key_combine
	aesimc  xmm11, xmm0
	aeskeygenassist xmm1, xmm0, 0x40
	call    key_combine
	aesimc  xmm12, xmm0
	aeskeygenassist xmm1, xmm0, 0x80
	call    key_combine
	aesimc  xmm13, xmm0
	aeskeygenassist xmm1, xmm0, 0x1b
	call    key_combine
	aesimc  xmm14, xmm0
	aeskeygenassist xmm1, xmm0, 0x36
	call    key_combine
	movaps  xmm15, xmm0

encrypt:
	movaps	xmm0, [cipher]
	pxor	xmm0, xmm15
	aesdec  xmm0, xmm14
	aesdec  xmm0, xmm13
	aesdec  xmm0, xmm12
	aesdec  xmm0, xmm11
	aesdec  xmm0, xmm10
	aesdec  xmm0, xmm9
	aesdec  xmm0, xmm8
	aesdec  xmm0, xmm7
	aesdec  xmm0, xmm6
	aesdeclast xmm0, xmm5

	; plain is in xmm0 now, use `po $xmm0` in lldb
	int 3

output:
	mov	 rax, 0x2000004 ; write
	mov	 rdi, 1 ; stdout
	mov	 rsi, msg
	mov	 rdx, msg.len
	syscall

exit:
	mov	 rax, 0x2000001 ; exit
	mov	 rdi, 0
	syscall

key_combine:
	pshufd  xmm1, xmm1, 0xff
	shufps  xmm2, xmm0, 0x10
	pxor	xmm0, xmm2
	shufps  xmm2, xmm0, 0x8c
	pxor	xmm0, xmm2
	pxor	xmm0, xmm1
	retn	

section .data

msg:	db	  "Hello, world!", 10
.len:   equ	 $ - msg

