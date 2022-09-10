#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please input sleep seconds!");
        exit(1);
    }
    int tick = atoi(argv[1]);
    sleep(tick);
    printf("(nothing happens for a little while)\n");
    exit(0);

    return 0;
}