#include "brainfuck.h"
#include <stdlib.h>
#include <stdio.h>

BrainFuckContext *bf_init(u32 len)
{
    void *ptr;
    BrainFuckContext *bf = malloc(sizeof(BrainFuckContext));
    if (bf == NULL)
        return NULL;

    bf->len = len;
    bf->data = (u8 *)malloc(len * sizeof(u8));
    if (bf->data == NULL)
    {
        free(bf);
        return NULL;
    }
    for (size_t i = 0; i < len; i++)
    {
        bf->data[i] = 0;
    }

    bf->whileInstuctions = list_init();

    bf->position = 0;
    bf->inWhile = 0;

    if (bf->data == NULL)
        return NULL;
    return bf;
}
void bf_free(BrainFuckContext *bf)
{
    if (bf == NULL)
        return;
    if (bf->data != NULL)
        free(bf->data);
    if (bf->whileInstuctions != NULL)
        list_free(bf->whileInstuctions);

    free(bf);
}

u32 checkInstruction(u32 inWhile, char instruction)
{
    if (instruction == BRAINFUCK_WHILE_START)
        ++inWhile;
    else if (instruction == BRAINFUCK_WHILE_END)
        --inWhile;

    return inWhile;
}
u64 bf_check_data(const char *data, u64 len)
{
    u32 inWhile = 0;
    for (u64 i = 0; i < len; i++)
    {
        char instruction = data[i];
        inWhile = checkInstruction(inWhile, instruction);
        if (inWhile == -1)
            return i;
    }
    return -1;
}
u64 bf_check_file(const char *const filepath)
{
    FILE *fptr = fopen(filepath, "r");
    if (fptr == NULL)
        return -2;
    fseek(fptr, 0, 0);
    char instruction;
    u32 inWhile = 0;
    for (u64 i = 0; (instruction = fgetc(fptr)); i++)
    {
        inWhile = checkInstruction(inWhile, instruction);
        if (inWhile == -1)
            return i;
    }
    fclose(fptr);
}

void handleWhileEnd(BrainFuckContext *bf)
{
    VoidList *instructions = bf->whileInstuctions;
    bf->whileInstuctions = list_init();
    while (bf->data[bf->position] != 0)
    {
        VoidNode *node = instructions->head;
        while (node != NULL)
        {
            char instruction = *(char *)node->value;
            bf_exec_instruction(bf, instruction);
            node = node->next;
        }
    }

    list_free(instructions);
}
void bf_exec_instruction(BrainFuckContext *bf, char instruction)
{
    if (bf->inWhile > 0)
    {
        if (instruction == BRAINFUCK_WHILE_END)
        {
            if (--bf->inWhile == 0)
            {
                handleWhileEnd(bf);
            }
            else
            {
                list_pusht(char, bf->whileInstuctions, BRAINFUCK_WHILE_END);
            }
        }
        else if (instruction == BRAINFUCK_WHILE_START)
        {
            bf->inWhile++;
            list_pusht(char, bf->whileInstuctions, BRAINFUCK_WHILE_START);
        }
        else
            list_pusht(char, bf->whileInstuctions, instruction);
        
        return;
    }

    switch (instruction)
    {
    case BRAINFUCK_LEFT:
        bf->position--;
        bf->position %= bf->len;
        break;
    case BRAINFUCK_RIGHT:
        bf->position++;
        bf->position %= bf->len;
        break;

    case BRAINFUCK_ADD:
        bf->data[bf->position]++;
        break;
    case BRAINFUCK_SUB:
        bf->data[bf->position]--;
        break;

    case BRAINFUCK_OUTPUT:
        printf("%c", bf->data[bf->position]);
        break;

    case BRAINFUCK_INPUT:
        char c;
        scanf(" %c", &c);
        bf->data[bf->position] = c;
        break;

    case BRAINFUCK_WHILE_START:
        bf->inWhile++;
        break;

    case BRAINFUCK_WHILE_END:
        fprintf(stderr, "Syntax Error\n");
        bf_free(bf);
        exit(1);
        break;

    default:
        // as a comment
        break;
    }
}

void bf_exec_code(BrainFuckContext *bf, const char *data, u64 len)
{
    for (size_t i = 0; i < len; i++)
    {
        bf_exec_instruction(bf, data[i]);
    }
}
void bf_exec_file(BrainFuckContext *bf, const char *const path)
{
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "Path %s cannot be found\n", path);
        exit(1);
    }
    fseek(fptr, 0, 0);
    
    i32 ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        bf_exec_instruction(bf, ch);
    }

    fclose(fptr);
}
