#ifndef _PARSEASM_H_
#define _PARSEASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "symbole.h"

#define GETINTFUNC "getint:\n\tpush rbp\n\tmov rbp, rsp\n\tmov dword [number] , 0\n\tmov r8 , 0\n\
digitOrNot:\n\tmov rax , 0\n\tmov rdi , 0\n\tmov rsi , digit\n\tmov rdx , 1\n\tsyscall\n\tcmp byte [digit] , 48 \
 \n\tjl notDigit\n\tcmp byte [digit] , 57\n\tjg notDigit\n\tinc r8\n\tsub byte [digit] , 48\n\t \
mov r10d , dword [number]\n\t  mov r9d , 10\n\timul r10d , r9d\n\tmov dword [number] , r10d\n\tmov al ,byte [digit]\n\t\
add dword [number] , eax\n\tjmp digitOrNot\nnotDigit:\n\tcmp r8 , 0\n\tje error \n\tjmp end \n\t \
error:\n\tcall readuntilnewline\n\tmov rax , 60 \n\tmov rdi , 5 \n\tsyscall\n \
end:\n\tmov eax , dword [number]\n\tmov rsp , rbp\n\tpop rbp\n\tret\n\
readuntilnewline:\n\tpush rbp\n\tmov rbp, rsp\n\tcmp byte [digit] , 0\n\tje end_r\nloop:\n\tcmp byte [digit],10\n\t\
je end_r\n\tmov rax , 0\n\tmov rdi , 0\n\tmov rsi , digit\n\tmov rdx , 1\n\tsyscall\n\tjmp loop\n\
end_r:\n\tmov rsp , rbp\n\tpop rbp\n\tret\n\n"\

#define GETCHARFUNC "getchar:\n\tpush rbp\n\tmov rbp, rsp\n\tsub rsp, 8\n\tmov rax, 0\n\tmov rdi, 0 \
 \n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n\tpop rax\n\tmov rsp,rbp\n\tpop rbp\n\tret\n\n"\

#define PUTCHARFUNC "putchar:\n\tpush rbp\n\tmov rbp, rsp\n\tpush rdi\n\tmov rax, 1\n\tmov rdi, 1\n\tmov rsi, rsp\
 \n\tmov rdx, 1\n\tsyscall\n\tmov rsp, rbp\n\tpop rbp\n\tret\n\n"\

#define PUTINTFUNC "putint:\n\tpush rbp\n\tmov rbp, rsp\n\tmov r8 , 10\n\tmov r9 , 0\n\tmov eax , edi \n\tmov rbx , 10\n\
calc:\n\tmov rdx , 0\n\tidiv rbx\n\tadd rdx , 48\n\tmov [BUFFER + r8 -1] , dl\n\tinc r9\n\tdec r8\n\tcmp rax , 0 \
 \n\tje end_p\n\tjmp calc\nend_p:\n\tmov rax , 1\n\tmov rdi , 1\n\tmov rsi , BUFFER\n\tadd rsi , r8\n\t \
 mov rdx , r9\n\tsyscall\n\tmov rax , 1\n\tmov rdi , 1\n\tmov byte [digit] , 10\n\tmov rsi , digit\n\tmov rdx , 1 \
 \n\tsyscall\n\t \tmov rsp , rbp\n\tpop rbp\n\tret\n\n" \

#define BUFFERSIZE 2048

void write_Asm(SymbolTable *global);

#endif
