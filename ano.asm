global _start
extern show_registers
section .text
_start:
	; Add Leaf
	mov eax, 2
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute sub
	pop rcx
	pop rax
	sub rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute sub
	pop rcx
	pop rax
	sub rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute sub
	pop rcx
	pop rax
	sub rax, rcx
	push rax
	mov rbx, rax
	call show_registers
	mov rax, 60
	mov rdi, 0
	syscall
