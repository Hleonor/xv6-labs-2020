#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main()
{
    int x = 10;

    x += 1;
    printf("%d" , x);
    return 0;
}