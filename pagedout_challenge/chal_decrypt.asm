default rel

global start

section .data
	key:
	db 0x00, 0x00, 0x00, 0x00, 0x62, 0x69, 0x6e, 0x61, 0x72, 0x79, 0x20, 0x6e, 0x69, 0x6e, 0x6a, 0x61
	plain:
	db 0x76, 0x33, 0x35, 0x2e, 0x75, 0x73, 0x2f, 0x70, 0x61, 0x67, 0x65, 0x64, 0x2d, 0x6f, 0x75, 0x74
	cipher:
	db 0x76, 0x82, 0xc1, 0x84, 0xdc, 0x38, 0xb5, 0x89, 0xf8, 0x84, 0xd4, 0xf7, 0xae, 0xc5, 0xaf, 0x35

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

