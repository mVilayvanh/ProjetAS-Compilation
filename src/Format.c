#include "Format.h"

int read_option(int argc, char *argv[]){
    int opt, opt_index = 0;
    static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"tree", no_argument, 0, 't'},
          {"symbol", no_argument, 0, 's'},
          {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hts", long_options, &opt_index)) != -1) {
        switch (opt) {
            case 't':
                tree_flag = 1;
                break;
            case 'h':
                help_flag = 1;
                break;
            case 's':
                sym_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage : %s [OPTIONS] [file.tpc]\n",
                argv[0]);
                fprintf(stderr, "use --help or -h to get more informations.\n");
                return 1;
        }
        if (help_flag){
            return 0;
        }
    }
    return 0;
}

FILE * open_sysopsis_path(){
    FILE *in ;
    if((in = fopen("../src/Synopsis.txt", "r"))){
           
        return in;
    }
    else{
        in = fopen("./src/Synopsis.txt", "r");
        return in;
    
    }
        
}
void print_synopsis(){
    char c;
    FILE *in;
    if ((in = open_sysopsis_path()) != NULL){
        while (fscanf(in, "%c", &c) != -1){
            fprintf(stderr, "%c", c);
        }
        fclose(in);
    }
}

int last_is_option(int argc, char **argv){
    return argv[argc - 1][0] == '-';
}


