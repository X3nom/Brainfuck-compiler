#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>

#include <asm_strings.h>

#define ERROR_EXIT(_exit_code, ...) {perror(__VA_ARGS__); exit(_exit_code);}




void write_head(FILE *output, uint32_t memsize){
    fprintf(output, "\
\
section .bss \n\
    mem resb %u \n\
section .data \n\
    mem_len db %u \n\
%s",
    memsize,
    memsize,
    BF_ASM_HEAD_FULL
    );
}

void write_exit(FILE *output){
    fprintf(output, "call _exit\n");
}


void write_code(FILE *output, FILE *input){
    uint32_t bracketpair_id = 0;
    char c;
    for(c = getc(input); c != EOF; c = getc(input)){
        switch(c){
            case '+':
                fprintf(output, "inc al\n");
                break;
            case '-':
                fprintf(output, "dec al\n");
                break;

            case '<':
                fprintf(output, "call left_operator\n");
                break;
            case '>':
                fprintf(output, "call right_operator\n");
                break;

            case '.':
                fprintf(output, "call dot_operator\n");
                break;
            case ',':
                fprintf(output, "call comma_operator\n");
                break;

            case '[':
                fprintf(output, "lb%u:\ncmp al, 0\njz rb%u\n", bracketpair_id, bracketpair_id);
                bracketpair_id++;
                break;
            case ']':
                bracketpair_id--;
                fprintf(output, "rb%u:\ncmp al, 0\njnz lb%u\n", bracketpair_id, bracketpair_id);
                break;
        }
    }
}





int main(int argc, char *argv[]){
    char *input_src_path = NULL;
    char *output_path = "./a.asm";

    uint32_t memsize = 0xffff;

    // Parse options ==============================
    int opt;
    while ((opt = getopt(argc, argv, "o:m:")) != -1) {
        switch (opt) {
            case 'o':
                output_path = optarg;
                break;
            case 'm':
                memsize = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-o output] input1 input2 ...\n", argv[0]);
                return 1;
        }
    }
    // Parse positionals ===========================
    // optind holds the positional arg index after getopt is done
    input_src_path = argv[optind];
    //==================
    if(input_src_path == NULL) ERROR_EXIT(1, "Invalid src input path\n");


    FILE *bf_src_file = fopen(input_src_path, "r");
    FILE *output_file = fopen(output_path, "w");


    write_head(output_file, memsize);

    write_code(output_file, bf_src_file);

    write_exit(output_file);

    // Cleanup
    fclose(bf_src_file);
    fclose(output_file);

    return 0;
}