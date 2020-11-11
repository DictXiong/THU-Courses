;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
str_num byte "gcd: %d", 0dh, 0ah, 0
a sdword ?
b sdword ? 

; 输入两个数, 输出它们的最大公约数
; 以变量a,b输入, 得到的结果存在a中
.code
gcd proc
    mov eax, a
    cmp eax, 0
    jge L1
    neg a
L1:
    mov eax, b
    cmp eax, 0
    jge L2
    neg b
L2:
    mov eax, a
	mov edx, 0
    div b
    cmp edx, 0
    xchg edx, b
    mov a, edx
    jg L2
    ret
gcd endp


main proc
    mov a, 3210
    mov b, 100
    call gcd
    invoke printf, offset str_num, a

    mov a, -3210
    mov b, 150
    call gcd
    invoke printf, offset str_num, a

    mov a, 3210
    mov b, -154
    call gcd
    invoke printf, offset str_num, a

    mov a, 32
    mov b, 57
    call gcd
    invoke printf, offset str_num, a

    invoke ExitProcess,0
main endp
end main