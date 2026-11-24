#include "vm.h"

int main(void) {
    /* Program: x = 5; print x + 3; */
    Instr program[] = {
        {OP_PUSH, 5},
        {OP_STORE, 'x' - 'a'},
        {OP_LOAD, 'x' - 'a'},
        {OP_PUSH, 3},
        {OP_ADD, 0},
        {OP_PRINT, 0},
        {OP_HALT, 0},
    };

    FILE *f = fopen("trace.json", "w");
    if (!f) return 1;

    run(program, sizeof program / sizeof program[0], f);
    fclose(f);
    return 0;
}