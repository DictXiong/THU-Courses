;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
int_out byte "%d, ", 0
new_line byte 0dh, 0ah, 0
array_1 word 3, 1, 7, 5, 2, 9, 4, 3
array_2 word 14, 10, 18, 16, 20, 26, 23, 29, 26, 35, 32, 37

.code

bubble_sort proc uses eax ebx ecx,
        array: ptr word,
        len: dword
    L0:
        mov ecx, array
        add ecx, len 
        add ecx, len 
        sub ecx, 2
        mov ebx, 0
        L1:
            mov ax, [ecx]
            cmp ax, [ecx - 2]
            jbe L2
                xchg ax, [ecx - 2]
                xchg ax, [ecx]
                mov ebx, 1
            L2:
            sub ecx, 2
            cmp ecx, array
        jne L1
        cmp ebx, 0
    jne L0
    ret
bubble_sort endp  

print_array proc uses eax ecx,
        array: ptr word,
        len: dword
    mov eax, array
    mov ecx, len  
    L3:
        push eax
        push ecx
        invoke printf, offset int_out, word ptr [eax]
        pop ecx
        pop eax
        add eax, 2
    loop L3 
    invoke printf, offset new_line
    ret
print_array endp

main proc
    invoke print_array, offset array_1, lengthof array_1
    invoke bubble_sort, offset array_1, lengthof array_1
    invoke print_array, offset array_1, lengthof array_1

    invoke print_array, offset array_2, lengthof array_2
    invoke bubble_sort, offset array_2, lengthof array_2
    invoke print_array, offset array_2, lengthof array_2

    invoke ExitProcess,0
main endp
end main