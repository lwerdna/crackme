.586
.model flat, stdcall
locals
unicode = 0

extrn GetModuleHandleA:PROC
extrn DialogBoxParamA:PROC
extrn ExitProcess:PROC
extrn EndDialog:PROC
extrn SetWindowTextA:PROC
extrn GetDlgItem:PROC
extrn SendMessageA:PROC
extrn SetFocus:PROC
extrn MessageBoxA:PROC
extrn _wsprintfA:PROC

.data

;win32 stuff
WM_INITDIALOG		equ 0110h
WM_COMMAND		equ 0111h
WM_CLOSE		equ 0010h

WM_GETTEXT		equ 000Dh
WM_SETTEXT		equ 000Ch
EM_SETLIMITTEXT		equ 00C5h

MB_OK			equ 0h


;ressource stuff
IDD_DIALOG1	equ	100
ID_GEN		equ	1006
IDC_NAME	equ	1004
IDC_SERIAL	equ	1005
ID_ABOUT        equ	1007

MIN_LEN equ 5
MAX_LEN equ 30

sname db 150 dup(0)
serial db 150 dup(0)

stable db 60h dup(0)
dword_AB dd 2 dup(0)
dword_B3 dd 2 dup(0)

result db 30 dup(0)

dword_10A dd 2 dup(0)
dword_93 dd 2 dup(0)

okay_guy db 4Fh,4Bh,41h,59h,5Fh,47h,55h,59h

charset_t db "aAb0cBd1eCf2gDh3jEk4lFm5nGp6qHr7sJt8uKv9w",0


titledlg db "VM Genaytik - Keygen by artif / ???", 0
initText db "Enter a name and press Generate ...", 0
errorlen db "Name too short ...", 0
about_title db "A propos !",0
about_content db "Keygen VM Geynatik by artif",13,10
	      db "Protection : VIRTUAL MACHINE + homemade CRYPTO",13,10
	      db "Coded with TASM 5.0",13,10
	      db 13,10
	      db "(c) 2008 - 2008 : all shits reserved",0


.data?

hdlg 		dd ?
handleName 	dd ?
handleSerial 	dd ?

keyValue dd ?
dword_A3 dd ?
dword_9B dd ?
dword_9F dd ?
d dd ?
table_remain db 10 dup(?)

.code

start:
	pushad
	call GetModuleHandleA, 0
	call DialogBoxParamA, eax, IDD_DIALOG1, 0, offset DlgProc, 0
	popad
	call ExitProcess, 0
	ret

DlgProc proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	uses ebx, edi, esi
	mov eax, wmsg
	
	cmp eax, WM_INITDIALOG
	jz _wminitdialog
	cmp eax, WM_COMMAND
	jz _wmcommand
	cmp eax, WM_CLOSE
	jz _wmclose
	
_fuck:
	sub eax, eax
	ret

_wmclose:
	call EndDialog, hdlg, 0
	ret

_wmcommand:
	mov eax, wparam
	cmp ax, ID_ABOUT
	jz printAbout
	cmp ax, ID_GEN
	jnz _fuck
	call Generateserial
 	jmp _fuck

printAbout:
	call MessageBoxA, hwnd, offset about_content, offset about_title, MB_OK
	jmp _fuck

_wminitdialog:
	mov eax, hwnd
	mov hdlg, eax
	call SetWindowTextA, hwnd, offset titledlg

	call GetDlgItem, hwnd, IDC_NAME
	mov handleName, eax
	call SendMessageA, eax, EM_SETLIMITTEXT, MAX_LEN, 0
	call GetDlgItem, hwnd, IDC_SERIAL
	mov handleSerial, eax
	call SendMessageA, eax, WM_SETTEXT, 0, offset initText
	
	mov eax, 1
	ret
DlgProc endp

Generateserial proc
	LOCAL len:DWORD
	call SendMessageA, handleName, WM_GETTEXT, MAX_LEN+1, offset sname
	mov len, eax
	cmp eax, MIN_LEN
	jl @len_error

	pushad
	
	call genTable
	call genTableValue
	mov keyValue, eax
	call gen2dwords


	; ciphertext à reverser
	mov eax, dword ptr[okay_guy]
	mov dword ptr[dword_93], eax
	mov eax, dword ptr[okay_guy+4]
	mov dword ptr[dword_93+4], eax
	
	; création de la clef de décryptage
	mov eax, keyValue
	mov dword ptr[dword_B3], eax
	mov dword ptr[dword_B3+4], 6B79745Fh

	mov edx, 0Fh
@algo1:
	lea ebx, dword_B3
	lea eax, dword_93
	call reversed_algo
	dec edx
	cmp edx, 0
	jnz @algo1

	mov eax, dword ptr[dword_93+4]
	mov dword_A3, eax ; on stocke dword_A3


; algo de somme sur la table de dword
	call sumTable
	mov dword ptr[dword_93+4], eax


	mov edx, 0Ah
@algo2:
	lea ebx, dword_AB
	lea eax, dword_93
	call reversed_algo
	dec edx
	cmp edx, 0
	jnz @algo2

	mov eax, dword_A3 ; eax = dword_ABdelta
	sub eax, dword ptr[dword_93+4]
	add eax, dword ptr[dword_93]
	rol eax, 0Bh
	mov dword_A3, eax
	
	mov eax, dword ptr[dword_93] ; eax = dword_9Bdelta
	xor eax, dword ptr[dword_93+4]
	ror eax, 7
	mov dword_9B, eax

	mov eax, dword ptr[dword_93+4]
	rol eax, 9h
	mov dword_9F, eax

	mov eax, dword_9B
	lea edi, result
	call convBase

	add edi, 7
	mov byte ptr[edi-1], 2Dh
	mov eax, dword_9F
	call convBase
	
	mov eax, dword_A3
	add edi, 7
	mov byte ptr[edi-1], 2Dh
	call convBase
	
	popad
	
	call SendMessageA, handleSerial, WM_SETTEXT, 0, offset result
@sortie:
	call SetFocus, handleName
	ret
@len_error:
	call SendMessageA, handleSerial, WM_SETTEXT, 0, offset errorlen
	jmp @sortie
Generateserial endp

convBase proc
	push ebx
	push esi
	mov d, eax
	xor ecx, ecx
boucle_b:
	
	push 29h
	pop ebx     ; ebx = 29h
	xor edx, edx
	idiv ebx
	mov d, eax
	mov byte ptr[table_remain+ecx], dl
	inc ecx
	cmp eax, 29h
	jae boucle_b

	mov al, byte ptr[charset_t+eax]
	mov byte ptr[edi], al ; dernier quotient

	; initialisation
	xor ebx, ebx
	mov edx, 1 ; new compteur = count
	dec ecx ; ecx = compteur-1

boucle_c:
	mov al, byte ptr[table_remain+ecx]
	mov bl, byte ptr[charset_t+eax]
	mov byte ptr[edi+edx], bl
	inc edx
	dec ecx
	cmp ecx, -1
	jnz boucle_c
	pop esi
	pop ebx
	ret
convBase endp

sumTable proc
	xor eax, eax
	lea esi, stable
	mov edi, esi
	add edi, 5Dh
@addr_408: 
	add eax, dword ptr[esi]
	inc esi
	cmp esi, edi
	jnz @addr_408
	ret
sumTable endp

reversed_algo proc
	
	pushad
	push eax
	mov edx, dword ptr[ebx]        ; sauvegarde dans un autre buffer
	mov dword ptr[dword_10A], edx
	mov edx, dword ptr[ebx+4]
	mov dword ptr[dword_10A+4], edx
	call genValueKey
	mov edi, eax
	pop esi
	
	mov edx, 64h ; compteur

@bigloop:
	push ebx
	; 1er algo à rev
	mov ebx, dword ptr[esi+4]
	rol ebx, 7
	mov dword ptr[esi+4], ebx
	mov ebx, dword ptr[esi]
	ror ebx, 7
	mov dword ptr[esi], ebx

	;2nd algo à reverse
	
	; x0' = ror(c0^ror(c7,3),3)
	mov bl, byte ptr[esi+7]	
	ror bl, 3
	xor bl, byte ptr[esi]
	ror bl,3
	mov byte ptr[esi], bl

	; x1' = ror(c1^ror(c6,3),3)
	mov bl, byte ptr[esi+6] 	
	ror bl, 3
	xor bl, byte ptr[esi+1]
	ror bl,3
	mov byte ptr[esi+1], bl

	; x2' = ror(c2^ror(c5,3),3)
	mov bl, byte ptr[esi+5] 
	ror bl, 3
	xor bl, byte ptr[esi+2]
	ror bl,3
	mov byte ptr[esi+2], bl

	; x3' = ror(c3^ror(c4,3),3)
	mov bl, byte ptr[esi+4] 	
	ror bl, 3
	xor bl, byte ptr[esi+3]
	ror bl,3
	mov byte ptr[esi+3], bl

	; x4' = ror(c4,3) ^ x3'
	mov bl, byte ptr[esi+4]
	ror bl, 3
	xor bl, byte ptr[esi+3]
	mov byte ptr[esi+4], bl

	; x5' = ror(c5,3)^x2'
	mov bl, byte ptr[esi+5]
	ror bl, 3
	xor bl, byte ptr[esi+2]
	mov byte ptr[esi+5], bl

	; x6' = ror(c6,3)^x1'
	mov bl, byte ptr[esi+6]
	ror bl, 3
	xor bl, byte ptr[esi+1]
	mov byte ptr[esi+6], bl

	; x7' = ror(c7,3)^x0'
	mov bl, byte ptr[esi+7]
	ror bl, 3
	xor bl, byte ptr[esi]
	mov byte ptr[esi+7], bl
	pop ebx


; reverse de l'algo de bits
	;xor ecx, ecx
	mov ecx, 7
	mov ebp, 1  	; on commence cette fois par le 1er bits
@adr_55C: 
	call getBits
	cmp eax, 0
	jz @adr_5A9
	push ebp
	cmp ebp, 7
	jbe @adr_589
@adr_578:
	sub ebp, 7
	cmp ebp, 7
	ja @adr_578
@adr_589:
	; partie reversé
	mov al, byte ptr[ebx+ecx]
	xor byte ptr[esi+ebp], al
	pop ebp
	jmp @adr_5D9
@adr_5A9: 
	push ecx      	; save ecx sur la pile
	cmp ecx, 7
	jbe @adr_5C7
@adr_5B6:
	sub ecx, 7
	cmp ecx, 7
	ja @adr_5B6    	; ecx modulo
@adr_5C7:
	;partie reversé
	xor byte ptr[esi+ecx], cl
	not byte ptr[esi+ecx]
	pop ecx
@adr_5D9:
	;inc ecx
	;cmp ecx, 8
	;jb @adr_5EA
	dec ecx
	cmp ecx, -1
	jnz @adr_5EA
	mov ecx, 7
@adr_5EA: 
	inc ebp
	cmp ebp, 20h
	jbe @adr_55C

; l'algo des bits est à présent reversé

	xor ecx, ecx

@rolloop:
	; esi = dword_93
	; ebx = dword_AB

	; dword_97 = dword_97 - dword_AB
	mov eax, dword ptr[ebx]
	sub dword ptr[esi+4], eax

	; dword_93 = dword_93 - dword_AB+4
	mov eax, dword ptr[ebx+4]
	sub dword ptr[esi], eax

	; dword_97 = dword_97 XOR dword_AB+4
	mov eax, dword ptr[ebx+4]
	xor dword ptr[esi+4], eax

	; dword_93 = dword_93 XOR dword_AB
	mov eax, dword ptr[ebx]
	xor dword ptr[esi], eax

	; dword_97 = dword_97 rol 3
	mov eax, dword ptr[esi+4]
	rol eax, 3
	mov dword ptr[esi+4], eax

	; dword_93 = dword_93 ror 3
	mov eax, dword ptr[esi]
	ror eax, 3
	mov dword ptr[esi], eax
	
	inc ecx
	cmp ecx, 10h
	jnz @rolloop


	; dernier algo à reverser
	xor eax, eax
	xor ecx, ecx
	push esi
 	push ebx
	mov ecx, esi
	add ecx, 7

@adr_4B5:
	mov al, byte ptr[esi]
	sub al, 12h
	inc ebx
	add al, byte ptr[ebx]
	dec ebx
	xor al, byte ptr[ebx]
	mov byte ptr[esi], al
	inc ebx
	inc esi
	cmp esi, ecx
	jnz @adr_4B5
	pop ebx
	pop esi

	dec edx
	cmp edx, 0
	jnz @bigloop
	
	and dword ptr[dword_10A], 0
	and dword ptr[dword_10A+4], 0
	popad
	ret
reversed_algo endp

getBits proc
	push ebp
	push edi
	mov eax, 1
	jmp @adr_77A
@adr_776: 
	shl eax, 1
@adr_77A: 
	dec ebp
	cmp ebp, 0FFFFFFFFh
	jnz @adr_776
	and edi, eax
	cmp edi, 0
	jz @adr_7A1
	mov eax, 1
	jmp @adr_7A5
@adr_7A1: 
	xor eax, eax
@adr_7A5: 
	pop edi
	pop ebp
	ret
getBits endp

genValueKey proc
	xor ecx, ecx

@adr_686:
	lea esi, dword_10A
	inc esi
	add esi, ecx
	mov al, byte ptr[esi]
	dec esi
	add byte ptr[esi], al
	sub byte ptr[esi], cl
	lea esi, dword_10A
	mov eax, dword ptr[esi]
	rol eax, 5
	mov dword ptr[esi], eax
	add esi, 4
	mov eax, dword ptr[esi]
	ror eax, 5
	mov dword ptr[esi], eax
	inc ecx
	cmp ecx, 7
	jnz @adr_686

	xor eax, eax
	xor ecx, ecx
	xor edx, edx
	mov esi, 45h
	push edi ; je sauve edi pour m'en servir d'offset
@adr_6E9:
	lea edi, dword_10A
	add edi, ecx
	mov al, byte ptr[edi]
	add edx, eax
	imul esi, esi
	inc edx
	imul edx, esi
	inc ecx
	cmp ecx, 4
	jnz @adr_6E9
	pop edi ; on recupere la valeur de edi

	push edx   ; sauve edx sur la pile
	xor eax, eax
	xor ecx, ecx
	xor edx, edx
	mov esi, 35h
	push edi   ; save edi pour offset
@adr_72A:
	lea edi, dword_10A
	add edi, 4
	add edi, ecx
	mov al, byte ptr[edi]
	sub edx, eax
	imul esi, esi
	inc edx
	imul edx, esi
	inc ecx
	cmp ecx, 4
	jnz @adr_72A
	pop edi ; recup edi
	pop eax
	imul eax, edx
	ret
genValueKey endp

genTable proc
	lea edi, sname
	mov ebx, edi
	add ebx, eax
 	lea esi, stable
	add esi, 5Fh
	xor edx, edx
	xor eax, eax
@boucletable:
	xor al, byte ptr[edi]
	xor al, 75h
	add al, dl
	add edx, 3
	xor edx, 45h
	rol edx, 3
	inc edi
	mov [esi], al
	cmp esi, offset stable
	jz @outgen
	dec esi
	cmp edi, ebx
	jnz @boucletable
	lea edi, sname
	jmp @boucletable
@outgen:
	ret
genTable endp

genTableValue proc
	mov eax, 1A2B3C4Dh
	mov edx, 0FFh
@adr425:
	lea esi, stable
	mov edi, esi
	add edi, 5Dh
@boucleval:
	mov ecx, dword ptr[esi]
	xor eax, ecx
	rol eax, 7
	inc esi
	cmp esi, edi
	jnz @boucleval
	dec dl
	cmp dl, 0
	jnz @adr425
	ret
genTableValue endp

gen2dwords proc
	mov eax, 13A1DCB4h
	mov ecx, 45E8ADC1h
	mov edx, 28h ; compteur
@adr381:
	lea esi, stable
	mov edi, esi
	add edi, 30h
	mov ebx, edi
@adr397:
	xor eax, dword ptr[esi]
	rol eax, 3
	add eax, dword ptr[edi]
	add esi, 4
	add edi, 4
	cmp esi, ebx
	jnz @adr397
	xor eax, ecx
	xchg eax, ecx
	dec edx
	cmp edx, 0
	jnz @adr381
	mov dword ptr[dword_AB], eax
	mov dword ptr[dword_AB+4], ecx
	ret
gen2dwords endp

end start



	