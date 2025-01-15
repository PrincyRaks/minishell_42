#include "minishell.h"

int main(int argc, char *argv[])
{
    printf("file: %s & exist: %d\n", argv[1],access(argv[1], F_OK));
    return 0;
}
