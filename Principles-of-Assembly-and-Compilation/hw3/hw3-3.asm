;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
string_num byte "%d ", 0
a dword 0
b dword 1

.code
main proc
    mov ecx, 10
    L1:
        push ecx
        invoke printf, offset string_num, b
        pop ecx
        mov eax, a
        add eax, b
        xchg eax, b
        mov a, eax
    loop L1

    invoke ExitProcess,0
main endp
end main