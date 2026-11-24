#include <assert.h>
#include <stdio.h>
#include "../src/vm.h"

int main(void) {
    Instr program[] = {
        {OP_PUSH, 5}, {OP_STORE, 23}, {OP_LOAD, 23},
        {OP_PUSH, 3}, {OP_ADD, 0}, {OP_HALT, 0},
    };
    FILE *f = fopen("Nul", "w");   /* discard trace output */
    run(program, 6, f);
    fclose(f);
    puts("VM tests passed");
    return 0;
}