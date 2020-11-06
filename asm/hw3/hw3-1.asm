;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
intArray WORD 500h, 400h, 300h, 200h, 100h
str_sum byte "sum = %d", 0dh, 0ah, 0

.code
main proc
    ; 不循环
    mov ax, intArray[0]
    add ax, intArray[2]
    add ax, intArray[4]
    add ax, intArray[6]
    add ax, intArray[8]
    invoke printf, offset str_sum, ax

    ; 循环
    mov ecx, lengthof intArray
    mov edi, offset intArray
    mov ax, 0
    L1:
        add ax, [edi]
        add edi, type intArray
    loop L1
    invoke printf, offset str_sum, ax

    invoke ExitProcess,0
main endp
end main