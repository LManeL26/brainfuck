#include <stdio.h>
#include "global.h"
#include "list.h"
#include "brainfuck.h"

int main(int argc, char const *argv[])
{
    BrainFuckContext* ctx = bf_init(100);
    bf_exec_file(ctx, argv[1]);
    printf("\n\n");
    bf_free(ctx);
    return 0;
}
