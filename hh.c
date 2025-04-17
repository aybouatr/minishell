#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    pid_t id = fork();

    if (id == 0)
    {
        while (1337)
        {
            printf("\n\nrunning in child \n");
            sleep(1);
        }
    }
    else
    {
        int nb = wait();
        while (1337)
        {
            printf("\n\nrunning in parent \n");
            sleep(1);
        }
    }
    
}