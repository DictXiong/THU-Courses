;
; Dict Xiong is learning asm

include Irvine32.inc
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib


.data
num_a sbyte 24
num_b sword 2334
num_c sdword 35324543

.code

mWriteInt macro integer
    if (sizeof integer) eq 4
        mov eax, integer
    else 
        movsx eax, integer
    endif
    call WriteInt
endm

main proc
    mWriteInt num_a
    call Crlf
    mWriteInt num_b
    call Crlf
    mWriteInt num_c

quit:
    invoke ExitProcess,0
main endp
end main