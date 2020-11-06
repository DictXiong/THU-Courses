; 编写一条语句计算下面数组所包含的字节数，并输出结果。
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
myArray WORD 20 DUP(?)
size_myArray dword ?
string_myArray byte "size of myArray: %d", 0dh, 0ah, 0

.code
main proc
    mov size_myArray, sizeof myArray
    invoke printf, offset string_myArray, size_myArray
    invoke ExitProcess,0
main endp
end main