;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
source BYTE 'This is the source string', 0
target BYTE SIZEOF source DUP('#')


.code
main proc
    mov ecx, lengthof source
    sub ecx, type source
    mov target[ecx], 0
    mov edi, 0
    L1:
        mov eax, ecx
        sub eax, 1
        mov al, source[eax]
        mov target[edi], al
        add edi, type target
    loop L1
    invoke printf, offset target

    invoke ExitProcess,0
main endp
end main