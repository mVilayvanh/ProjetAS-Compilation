section .bss
globals: resd 4
section .text
global getint
global putchar
global putint
global getchar
global foo
global foo2
global _start
getint:
putchar:
	ret
putint:
	ret
getchar:
foo:
	ret
foo2:
	mov rax, qword [rbp - 0]
	ret
_start:
	mov rbp, rsp
	mov eax, 5
	push rax
	mov rax, qword [rbp - 8]
	push rax
	mov rax, qword [rbp - 16]
	push rax
	push rax
	; Add Leaf
	mov eax, 20
	push rax
	; Add Leaf
	mov eax, 10
	push rax
	; Compute sub
	pop rcx
	pop rax
	sub rax, rcx
	push rax
	pop rax
	mov qword [rbp - 8], rax
	mov rax, 4
	mov dword [globals + 12], eax
	mov rax, qword [rbp - 8]
	push rax
	mov eax, dword [globals + 12]
	push rax
	; Add Leaf
	mov eax, 2
	push rax
	; Compute Mul
	pop rcx
	pop rax
	imul rax, rcx
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	pop rax
	mov qword [rbp - 8], rax
	mov rax, qword [rbp - 8]
	push rax
	mov rax, 2
	push rax
	pop rcx
	pop rax
	cmp rax, rcx
	jl .E0
	jmp .E1
.E0:
	mov rax, 6
	mov dword [globals + 12], eax
	mov rax, 1
	mov rdi, rax
	mov rax, 60
	syscall
.E1:
	mov rax, qword [rbp - 8]
	push rax
	mov rax, 18
	push rax
	pop rcx
	pop rax
	; Compute Eq
	cmp rax, rcx
	je .E2
	jmp .E3
.E2:
	call foo
.E3:
	mov rax, 0
	mov rdi, rax
	mov rax, 60
	syscall
