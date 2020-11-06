;
; Dict Xiong is learning asm

include Irvine32.inc
ExitProcess proto, dwExitCode:dword
includelib msvcrt.lib

BUFFER_SIZE = 100

.data
msg_please byte "请输入", 0
msg_student_num byte "学号: ", 0
msg_name byte "姓名: ", 0
msg_birth byte "生日: ", 0
msg_count byte "学生数量: ", 0
msg_error_creating_file byte "文件创建错误", 0
msg_error_number byte "学生数量异常", 0

CR_LF byte 0dh, 0ah, 0
buffer byte BUFFER_SIZE dup(0)
string_len dword ?
filename byte "StudentRecord.txt", 0
file_handle handle 0
student_count dword 0


.code

newline proc 
    mov eax, file_handle
    mov edx, offset CR_LF
    mov ecx, lengthof CR_LF
    dec ecx
    call WriteToFile
    ret
newline endp

request_and_save proc,
        msg: ptr byte
    mov edx, offset msg_please
    call WriteString
    mov edx, msg
    call WriteString
    ; read
    mov ecx, BUFFER_SIZE
    mov edx, offset buffer
    call ReadString
    mov string_len, eax 
    ; write msg
    invoke Str_length, msg 
    mov ecx, eax
    mov eax, file_handle
    mov edx, msg
    call WriteToFile
    ; write buffer
    mov eax, file_handle
    mov edx, offset buffer
    mov ecx, string_len
    call WriteToFile
    call newline
    ret
request_and_save endp

main proc
    mov edx, offset msg_count
    call WriteString
    call ReadInt
    mov student_count, eax
    
    cmp eax, 0
    jne number_ok
    mov edx, offset msg_error_number
    call WriteString
    jmp quit

number_ok:
    call Crlf 
    mov edx, offset filename
    call CreateOutputFile
    mov file_handle, eax

    cmp eax, INVALID_HANDLE_VALUE
    jne file_ok
    mov edx, offset msg_error_creating_file
    call WriteString
    jmp quit

file_ok:
    invoke request_and_save, offset msg_student_num
    invoke request_and_save, offset msg_name
    invoke request_and_save, offset msg_birth
    call Crlf 
    call newline

    mov eax, student_count
    dec eax 
    mov student_count, eax 
    cmp eax, 0
    jne file_ok

quit:
    invoke ExitProcess,0
main endp
end main