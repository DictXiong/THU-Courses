; ʹ�û������ʵ��һ��С���̣�����Ļ����ʾ������Ϣ��������ѧ�š��༶�ȣ���ʽ�Զ��壩����Դ�����ļ�(.asm)�Ϳ�ִ�г���(.exe)���ѹ�����ύ��ͬʱ��д��������ѧ�ţ���"ѧ��_����_���1.rar"��

.386
.model flat,stdcall
.stack 4096
option casemap:none

includelib msvcrt.lib
printf proto c : ptr sbyte, : VARARG

.data
student_name byte "����: �ܵ�", 0ah, 0dh, 0
student_number byte "ѧ��: 2017012113", 0ah, 0dh, 0
class byte "�༶: ��72", 0ah, 0dh, 0

.code 
main proc
    invoke printf, offset student_name
    invoke printf, offset student_number
    invoke printf, offset class
    ret
main endp
end main