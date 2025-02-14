#ifndef BRAINFUCK_FLAG
#define BRAINFUCK_FLAG

#include "global.h"
#include "list.h"

#define BRAINFUCK_LEFT '<'
#define BRAINFUCK_RIGHT '>'

#define BRAINFUCK_ADD '+'
#define BRAINFUCK_SUB '-'

#define BRAINFUCK_INPUT ','
#define BRAINFUCK_OUTPUT '.'

#define BRAINFUCK_WHILE_START '['
#define BRAINFUCK_WHILE_END ']'

typedef struct _bfc
{
    char *data;
    u32 len;

    VoidList *whileInstuctions;

    u32 position;
    u16 inWhile;
} BrainFuckContext;

BrainFuckContext *bf_init(u32 len);
void bf_free(BrainFuckContext *bf);

u64 bf_check_data(const char *data, u64 len);
u64 bf_check_file(const char *const filepath);

void bf_exec_instruction(BrainFuckContext *bf, const char instruction);
void bf_exec_file(BrainFuckContext *bf, const char *const path);
void bf_exec_code(BrainFuckContext *bf, const char *const data, u64 len);

#endif
