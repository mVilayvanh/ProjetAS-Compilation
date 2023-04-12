#ifndef _PARSEASM_H_
#define _PARSEASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "symbole.h"

#define BUFFERSIZE 2048

void writeAsm(SymbolTable * global );

#endif
