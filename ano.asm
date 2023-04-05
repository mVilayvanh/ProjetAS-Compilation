global _start
extern show_registers
section .text
_start:
	mov rbx, rax
	call show_registers
	mov rax, 60
	mov rdi, 0
	syscall
