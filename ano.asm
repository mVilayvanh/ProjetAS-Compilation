section .bss
	globals: resd 4
	digit: resb 1
	number: resd 1
	BUFFER: resb 10
section .text
global getint
global putchar
global putint
global getchar
global foo
global foo2
global _start
getint:
	push rbp
	mov rbp, rsp
	mov dword [number] , 0
	mov r8 , 0
digitOrNot:
	mov rax , 0
	mov rdi , 0
	mov rsi , digit
	mov rdx , 1
	syscall
	cmp byte [digit] , 48  
	jl notDigit
	cmp byte [digit] , 57
	jg notDigit
	inc r8
	sub byte [digit] , 48
	 mov r10d , dword [number]
	  mov r9d , 10
	imul r10d , r9d
	mov dword [number] , r10d
	mov al ,byte [digit]
	add dword [number] , eax
	jmp digitOrNot
notDigit:
	cmp r8 , 0
	je error 
	jmp end 
	 error:
	call readuntilnewline
	mov rax , 60 
	mov rdi , 5 
	syscall
 end:
	mov eax , dword [number]
	mov rsp , rbp
	pop rbp
	ret
readuntilnewline:
	push rbp
	mov rbp, rsp
	cmp byte [digit] , 0
	je end_r
loop:
	cmp byte [digit],10
	je end_r
	mov rax , 0
	mov rdi , 0
	mov rsi , digit
	mov rdx , 1
	syscall
	jmp loop
end_r:
	mov rsp , rbp
	pop rbp
	ret

getchar:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, 0
	mov rdi, 0  
	mov rsi, rsp
	mov rdx, 1
	syscall
	pop rax
	mov rsp,rbp
	pop rbp
	ret

putint:
	push rbp
	mov rbp, rsp
	mov r8 , 10
	mov r9 , 0
	mov eax , edi 
	mov rbx , 10
calc:
	mov rdx , 0
	idiv rbx
	add rdx , 48
	mov [BUFFER + r8 -1] , dl
	inc r9
	dec r8
	cmp rax , 0  
	je end_p
	jmp calc
end_p:
	mov rax , 1
	mov rdi , 1
	mov rsi , BUFFER
	add rsi , r8
	  mov rdx , r9
	syscall
	mov rax , 1
	mov rdi , 1
	mov byte [digit] , 10
	mov rsi , digit
	mov rdx , 1  
	syscall
	 	mov rsp , rbp
	pop rbp
	ret

putchar:
	push rbp
	mov rbp, rsp
	mov rcx, rbp
	add rcx, 8
	mov rax, 1
	mov rdi, 1
	mov rsi, rcx
	mov rdx, 1
	syscall
	mov rsp, rbp
	pop rbp
	ret

foo:
	push rbp
	mov rbp, rsp
	call getchar
	mov dword [globals + 4], eax
	mov rsp, rbp
	pop rbp
	ret
foo2:
	push rbp
	mov rbp, rsp
	mov rax, 0
	push rax
	mov rax, qword [rbp - 8]
	push rax
	mov rax, 10
	push rax
	pop rcx
	pop rax
	cmp rax, rcx
	jl .E2
	jmp .E1
.E2:
	mov rax, qword [rbp + 16]
	push rax
	mov rax, 10
	push rax
	pop rcx
	pop rax
	cmp rax, rcx
	jl .E0
	jmp .E1
.E0:
	mov rax, qword [rbp + 16]
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
	push rax
	call foo2
	pop rcx
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
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
.E1:
	mov rax, qword [rbp + 16]
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
main:
	push rbp
	mov rbp, rsp
	mov rax, 1
	push rax
	mov rax, qword [rbp - 8]
	push rax
	mov rax, qword [rbp - 16]
	push rax
	mov rax, 0
	mov qword [rbp - 8], rax
	sub rsp, 8
	call foo
	add rsp, 8
	sub rsp, 8
	call getchar
	add rsp, 8
	push rax
	call putchar
	pop rcx
	mov eax, dword [globals + 4]
	pop rcx
	pop rcx
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
_start:
	mov rbp, rsp
	sub rsp, 8
	push rax
	call main
	pop rcx
	add rsp, 8
	mov rdi, rax
	mov rax, 60
	syscall
