#ifndef _FORMAT_
#define _FORMAT_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

extern int tree_flag;
extern int help_flag;

int read_option(int argc, char *argv[]);

void print_synopsis();

int last_is_option(int argc, char **argv);

void writeinit(FILE * f);

void writeend(FILE * f);

#endif