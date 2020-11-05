// pingpong.c for xv6 (assignment #1 for CSC.T371)
// name: Haruki Kikuchi
// id: 18B04686

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(1, "usage: %s N\n", argv[0]);
        exit(1);
    }

    // # of rounds
    int n = atoi(argv[1]);

    // tick value before starting rounds
    int start_tick = uptime();

    int pid;
    // parent to child
    int pipePtoC[2];
    // child to parent
    int pipeCtoP[2];

    int round = 0;
    int parentTurn = 1;

    if (pipe(pipePtoC) == -1 || pipe(pipeCtoP) == -1)
    {
        fprintf(1, "error: pipe\n");
        exit(1);
    }

    if ((pid = fork()) == -1)
    {
        fprintf(1, "error: fork\n");
        exit(1);
    }

    if (pid == 0)
    {
        // child process
        unsigned char data = 0;
        close(pipeCtoP[0]);
        close(pipePtoC[1]);
        while (round < n)
        {
            if (!(parentTurn == 1))
            {
                write(pipeCtoP[1], &data, 1);
                parentTurn = 1;
                round++;
            }
            else
            {
                read(pipePtoC[0], &data, 1);
                data = data + 1;
                parentTurn = 0;
            }
        }
        exit(0);
    }
    else
    {
        // parent process
        unsigned char data = 0;
        close(pipeCtoP[1]);
        close(pipePtoC[2]);
        while (round < n)
        {
            if (parentTurn == 1)
            {
                write(pipePtoC[1], &data, 1);
                parentTurn = 0;
            }
            else
            {
                read(pipeCtoP[0], &data, 1);
                data = data + 1;
                round++;
                parentTurn = 1;
            }
        }
        int *status = 0;
        wait(status);
    }
    // print # of ticks in nrounds
    printf("# of ticks in %d rounds: %d\n", n, uptime() - start_tick);
    exit(0);
}
