;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
str_a byte ", ", 0
str_b byte 0dh, 0ah, 0
targetStr byte "ABCDE", 10 dup(0)
sourceStr byte "FGH", 0


.code
Str_concat proc uses eax ebx edx,
        dest:dword,
        src:dword
    mov eax, dest
    sub eax, 1
    L1:
        inc eax
        cmp byte ptr [eax], 0
    jne L1
    mov ebx, src 
    L2:
        mov dl, [ebx]
        mov [eax], dl
        inc eax
        inc ebx 
        cmp byte ptr [ebx], 0
    jne L2
    mov byte ptr [eax], 0
    ret
Str_concat endp


main proc
    invoke printf, offset targetStr
    invoke printf, offset str_a
    invoke printf, offset sourceStr
    invoke printf, offset str_b

    invoke Str_concat, addr targetStr, addr sourceStr

    invoke printf, offset targetStr
    invoke ExitProcess,0
main endp
end main