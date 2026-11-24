#include "vm.h"

static void push(VM *vm, int v) { vm->stack[vm->sp++] = v; }
static int  pop(VM *vm)         { return vm->stack[--vm->sp]; }

/* Writes the state after one instruction as a JSON object. */
static void dump_state(const VM *vm, Opcode op, FILE *f) {
    fprintf(f, "{\"op\":%d,\"ip\":%d,\"sp\":%d,\"stack\":[", op, vm->ip, vm->sp);
    for (int i = 0; i < vm->sp; i++)
        fprintf(f, "%s%d", i ? "," : "", vm->stack[i]);
    fprintf(f, "],\"vars\":[");
    for (int i = 0; i < NUM_VARS; i++)
        fprintf(f, "%s%d", i ? "," : "", vm->vars[i]);
    fprintf(f, "]}");
}

void run(const Instr *code, int count, FILE *trace) {
    VM vm = {0};
    fprintf(trace, "[");

    int first = 1;
    while (vm.ip < count) {
        Instr in = code[vm.ip++];

        switch (in.op) {
            case OP_PUSH:  push(&vm, in.arg); break;
            case OP_LOAD:  push(&vm, vm.vars[in.arg]); break;
            case OP_STORE: vm.vars[in.arg] = pop(&vm); break;
            case OP_ADD: {
                int b = pop(&vm), a = pop(&vm);
                push(&vm, a + b);
                break;
            }
            case OP_PRINT: printf("%d\n", pop(&vm)); break;
            case OP_HALT:  vm.ip = count; break;
        }

        if (!first) fprintf(trace, ",");
        first = 0;
        dump_state(&vm, in.op, trace);
    }

    fprintf(trace, "]\n");
}