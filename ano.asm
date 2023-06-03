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
	mov eax, dword [globals + 12]
	mov rsp, rbp
	pop rbp
	ret
_start:
	mov rbp, rsp
	mov rax, 5
	push rax
	mov rax, qword [rbp - 8]
	push rax
	mov rax, qword [rbp - 16]
	push rax
	mov rax, qword [rbp - 8]
	mov rdi, rax
	sub rsp, 8
	call foo2
	add rsp, 8
	push rax
	; Add Leaf
	mov eax, 5
	push rax
	; Add Leaf
	mov eax, 97
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	pop rax
	mov qword [rbp - 32], rax
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
	cmp rax, 0
	jne .E0
	jmp .E1
.E0:
	mov rax, 12
	mov dword [globals + 12], eax
	mov eax, dword [globals + 12]
	push rax
	; Add Leaf
	mov eax, 6
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	pop rax
	push rax
	mov rax, 18
	push rax
	pop rcx
	pop rax
	; Compute Eq
	cmp rax, rcx
	jne .E2
	jmp .E4
.E2:
	call foo
	jmp .E3
.E4:
	mov rax, 8
	mov dword [globals + 12], eax
.E3:
	mov rax, 6
	mov dword [globals + 12], eax
.E1:
	mov rax, 0
	mov qword [rbp - 8], rax
	jmp .E5
.E6:
	mov rax, qword [rbp - 8]
	push rax
	; Add Leaf
	mov eax, 1
	push rax
	; Compute add
	pop rcx
	pop rax
	add rax, rcx
	push rax
	pop rax
	mov qword [rbp - 8], rax
.E5:
	mov rax, qword [rbp - 8]
	push rax
	mov rax, 0
	push rax
	pop rcx
	pop rax
	; Compute Eq
	cmp rax, rcx
	je .E6
.E7:
	mov rax, 0
	mov rdi, rax
	mov rax, 60
	syscall
