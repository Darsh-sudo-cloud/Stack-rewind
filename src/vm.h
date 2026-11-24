#ifndef VM_H
#define VM_H

#include <stdio.h>

typedef enum { OP_PUSH, OP_LOAD, OP_STORE, OP_ADD, OP_PRINT, OP_HALT } Opcode;

typedef struct {
    Opcode op;
    int arg;          /* constant for PUSH, variable index (0-25) for LOAD/STORE */
} Instr;

#define STACK_MAX 256
#define NUM_VARS 26

typedef struct {
    int ip;                    /* instruction pointer: which instruction runs next */
    int sp;                    /* stack pointer: how many items are on the stack */
    int stack[STACK_MAX];
    int vars[NUM_VARS];        /* variables a..z */
} VM;

void run(const Instr *code, int count, FILE *trace);

#endif