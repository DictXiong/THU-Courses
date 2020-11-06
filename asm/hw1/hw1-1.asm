; 使用汇编语言实现一个小例程，在屏幕上显示个人信息（姓名、学号、班级等，格式自定义）。将源代码文件(.asm)和可执行程序(.exe)打成压缩包提交，同时请写明姓名和学号，如"学号_姓名_汇编1.rar"。

.386
.model flat,stdcall
.stack 4096
option casemap:none

includelib msvcrt.lib
printf proto c : ptr sbyte, : VARARG

.data
student_name byte "姓名: 熊典", 0ah, 0dh, 0
student_number byte "学号: 2017012113", 0ah, 0dh, 0
class byte "班级: 材72", 0ah, 0dh, 0

.code 
main proc
    invoke printf, offset student_name
    invoke printf, offset student_number
    invoke printf, offset class
    ret
main endp
end main