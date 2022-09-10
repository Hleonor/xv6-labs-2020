#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

char* buf[512];
int main(int argc , char* argv[])
{
    // xargs后面跟的参数是固定输出的
    // 额外的参数是需要从管道中读取的，在管道中循环读取字符的时候如果遇到了换行符的的话就将之前读取的字符作为参数传递给xargs后面的命令一并输出
    // 如果没有遇到换行符的话就继续读取字符
    // 如果管道中没有字符的话就直接退出
    if (argc <= 1)
    {
        fprintf(2, "usage: xargs command\n");
        exit(1);
    }
    char* argvs[MAXARG]; // 宏定义，用来存储xargs后面的命令
    int index = 0;
    for (int i = 1; i < argc; i++) // 略过xargs
    {
        argvs[index++] = argv[i];
    }
    
    char buffer[1024]; // 缓冲区
    while (read(0 , buffer , 1024)) // 循环读取管道的数据，存入buffer中
    {
        char temp[1024] = {'\0'}; // 用来存储每一行的数据
        argvs[index] = temp; // 将temp作为xargs后面命令的参数
        for (int i = 0; i < 1024; i++)
        {
            if (buffer[i] == '\n')
            {
                argvs[index] = temp; // 将temp作为xargs后面命令的参数
                argvs[index + 1] = 0; // 将argvs的最后一个参数置为0
                if (fork() == 0)
                {
                    exec(argvs[0] , argvs); // 执行xargs后面的命令
                }
                wait(0);
                // index = argc - 1; // 重置index
                // memset(temp , '\0' , 1024); // 清空temp
            }
            else
            {
                temp[i] = buffer[i]; // 将buffer中的字符存入temp中
            }
        }
    }
    
    return 0;
}