; CSAW 2018 crypto challenge

extern parse_uint32_hex
extern decipher

global	_start

	section .text
_start:
	; greet user
	mov		edx, msg1len	; arg2: message length
	mov		ecx, msg1		; arg1: message
	mov		ebx, 1			; arg0: stdout
	mov		eax, 4			; __NR_write
	int		0x80
	
	; read in the input, expect "XXXXXXXX-XXXXXXXX"
	mov		edx, 17			; arg2: len
	mov		ecx, inbuf		; arg1: buffer
	mov 	ebx, 0			; arg0: stdin
	mov		eax, 3 			; __NR_read
	int		0x80

	; check input format
	mov		esi, inbuf
	cmp		[esi+8], byte '-'
	jne		.fail
	mov		byte [esi+8], 0

	; parse first ctext
	push	v0
	push	inbuf
	call	parse_uint32_hex
	cmp		eax, -1
	je		.fail

	; parse second ctext
	push	v1
	push	inbuf+9
	call	parse_uint32_hex
	cmp		eax, -1
	je		.fail

	; decipher
	push	v0
	call	decipher

	; check
	cld
	mov		esi, v0
	lodsd
	cmp		eax, 0x57415343		; 'CSAW'
	jne		.fail
	lodsd
	cmp		eax, 0x41484148		; 'HAHA'
	jne		.fail

.pass:
	mov		edx, msg2len
	mov		ecx, msg2
	jmp		.done
.fail:
	mov		edx, msg3len
	mov		ecx, msg3
.done:
	mov		ebx, 1
	mov		eax, 4
	int		0x80

	mov		ebx, 0			; arg0: status
	mov		eax, 1			; __NR_exit
	int		0x80

	section .data
msg1:		db	"enter key: ", 0
msg1len:	equ	$ - msg1
msg2:		db	"pass", 10
msg2len:	equ	$ - msg2
msg3:		db	"fail", 10
msg3len:	equ	$ - msg3

	section .bss
inbuf:	resb 32					; reserve bytes
v0:		resb 4
v1:		resb 4
