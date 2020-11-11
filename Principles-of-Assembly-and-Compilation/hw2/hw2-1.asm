; 1. 分别计算varA+varB，varA * varB，结果分别保存至sum和product中，并输出：
;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg

.data
varA dword 5
varB dword 6
sum dword 0
product dword 0
string_sum byte "a + b = %d", 0ah, 0dh, 0
string_product byte "a * b = %d", 0ah, 0dh, 0

.code
main proc
    mov eax, varA
    add eax, varB
    mov sum, eax

    mov eax, varA
    imul varB
    mov product, eax

    invoke printf, offset string_sum, sum
    invoke printf, offset string_product, product

    invoke ExitProcess,0
main endp
end main