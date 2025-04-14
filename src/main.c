#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>

#include <parse.h>
#include <tokens_translate.h>
#include <tokens_optimise.h>
#include <asm_funcs.h>



#define ERROR_EXIT(_exit_code, ...) {perror(__VA_ARGS__); exit(_exit_code);}

#define OUT_TEMPFILE_NAME ".bfx86.asm-src.tmp"



void src_2_asm(FILE *src, FILE *out, int memsize, int optimise){
    FILE *bf_tmp_out_file = fopen(OUT_TEMPFILE_NAME, "w");
    // parse src code to tokens
    TokenString ts = parse_src(src);

    if(optimise > 0){
        TokenString ts_new = squash_tokens(&ts);
        TokenString_destroy(&ts);
        ts = ts_new;
    }
    // translate tokens to asm
    translate_tokens_2_asm(bf_tmp_out_file, ts);

    fclose(bf_tmp_out_file); // Reopen with read mode
    bf_tmp_out_file = fopen(OUT_TEMPFILE_NAME, "r");

    // add definitions of functions used in asm
    write_asm_head(bf_tmp_out_file, out, memsize);

    // Cleanup
    fclose(bf_tmp_out_file);
    remove(OUT_TEMPFILE_NAME); // delete temp file
}



void print_help_menu_exit(int exit_code){

    exit(exit_code);
}


int main(int argc, char *argv[]){
    char *input_src_path = NULL;
    char *output_path = "./a.asm";

    int optimise = 1;
    uint32_t memsize = 0xfff;

    // Parse options ==============================
    int opt;
    while ((opt = getopt(argc, argv, "o:m:O:")) != -1) {
        switch (opt) {
            case 'o':
                output_path = optarg;
                break;
            case 'm':
                memsize = atoi(optarg);
                break;
            case 'O':
                optimise = atoi(optarg);
                break;
            default:
                print_help_menu_exit(1);
        }
    }
    // Parse positionals ===========================
    // optind holds the positional arg index after getopt is done
    input_src_path = argv[optind];
    //==================
    if(input_src_path == NULL) ERROR_EXIT(1, "Invalid src input path\n");


    FILE *bf_src_file = fopen(input_src_path, "r");
    FILE *output_file = fopen(output_path, "w");
    
    src_2_asm(bf_src_file, output_file, memsize, optimise);

    fclose(bf_src_file);
    fclose(output_file);

    return 0;
}