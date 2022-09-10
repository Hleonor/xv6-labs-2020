#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int p1[2]; // 管道1
    int p2[2]; // 管道2
    pipe(p1); // create pipe1
    pipe(p2); // create pipe2
    char buffer[] = {'X'};
    long length = sizeof(buffer);

    if (fork() == 0)
    {
        close(p1[1]);
        close(p2[0]);
        if(read(p1[0] , buffer , length) != length)
        {
            printf("parent--->son read error!\n");
            exit(1);
        }
        printf("%d: received ping\n" , getpid());
        if(write(p2[1] , buffer , length) != length)
        {
            printf("son--->parent write error!\n");
            exit(1);
        }
        exit(0);
    }

    close(p1[0]);
    close(p2[1]);
    if(write(p1[1] , buffer , length) != length) // 父进程应该先写，至少有一个进程应该先写入
    {
        printf("parent--->son write error!\n");
        exit(1);
    }
    if(read(p2[0] , buffer , length) != length)
    {
        printf("son--->parent read error!\n");
        exit(1);
    }
    printf("%d: received pong\n" , getpid());
    wait(0);
    exit(1);
    return 0;
}
