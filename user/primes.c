#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void redir(int n , int p[])
{
    close(n);
    dup(p[n]);
    close(p[0]);
    close(p[1]);
}

void getPrimes()
{
    int next , previous;
    int p[2];
    //pipe(p);
    if (read(0 , &previous , sizeof(int)))
    {
        printf("prime %d\n" , previous);
        pipe(p);
        if (fork() == 0)
        {
            redir(1, p);
            while(read(0 , &next , sizeof(int)))
            {
                if (next % previous != 0)
                {
                    write(1 , &next , sizeof(int));
                }
            }
            exit(0);
        }
        else
        {
            wait(0);
            redir(0 , p);
            getPrimes();
        }
    }
}

int main()
{
    int fd[2];
    pipe(fd);
    if(fork() == 0)
    {
        redir(1 , fd);
        for (int i = 2; i <= 35; i++)
        {
            write(1 , &i , sizeof(int));
        }
    }
    else
    {
        wait(0);
        redir(0 , fd);
        getPrimes();
    }
    exit(0);
}