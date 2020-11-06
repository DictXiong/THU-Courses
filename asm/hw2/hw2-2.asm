; 请分别输出如下变量的字节数：
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
vala dword 0h
valb sword 0h
valc byte 0h
string_dword byte "size of dword: %d", 0dh, 0ah, 0
string_sword byte "size of sword: %d", 0dh, 0ah, 0
string_byte byte "size of byte: %d", 0dh, 0ah, 0

.code
main proc
    invoke printf, offset string_dword, sizeof vala
    invoke printf, offset string_sword, sizeof valb
    invoke printf, offset string_byte, sizeof valc
    
    invoke ExitProcess,0
main endp
end main