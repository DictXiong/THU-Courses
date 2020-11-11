;
; Dict Xiong is learning asm

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib
printf proto c : ptr sbyte, : vararg


.data
ShowParams_message_b byte "Address %.8X = %.8X", 0dh, 0ah, 0
ShowParams_message_a byte "Stack parameters:", 0dh, 0ah, "---------------------------", 0dh, 0ah, 0

.code
ShowParams proc paramCount:dword
    invoke printf, offset ShowParams_message_a
    mov eax, [ebp]
    add eax, 4
    mov ecx, paramCount
    L1:
        add eax, 4
        push eax
        push ecx
        invoke printf, offset ShowParams_message_b, eax, dword ptr [eax]
        pop ecx
        pop eax
    loop L1
    ret
ShowParams endp

MySample PROC first:DWORD, second:DWORD, third:DWORD
	paramCount = 3
	INVOKE ShowParams, paramCount
	ret
MySample ENDP

main proc
    invoke MySample, 10h, 8421h, 40
    invoke ExitProcess,0
main endp
end main