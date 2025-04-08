# x86 Brainfuck compiler
Compile **Brainfuck** $\rightarrow$ **x86-64 asm**

I'm making this project to learn a bit more about assembly and compilers.

## Example usage
```bash
# compile brainfuck to assembly
$ bfx86 input.bf -o output.asm

# asseble and link
$ nasm output.asm -o output.o -f elf64
$ ld ./output.o -o executable_output
```