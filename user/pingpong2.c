// pingpong2.c for xv6 (assignment #3 for CSC.T371)
// name: Haruki Kikuchi
// id: 18B04686

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// <<<remove this comment and fill your code here if needed>>>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(1, "usage: %s N\n", argv[0]);
        exit(1);
    }

    // # of rounds
    int n = atoi(argv[1]);

    // time before starting rounds
    int start_time = rtime();

    // <<<remove this comment and fill your code here>>>
    /**
     * 1)pipeを作成する
     * 2)forkする
     * 3)pipeをつなぐ
     * 4)相互に送り合う 
     * %)子プロセスは最後にexit()する
     * 6) closeする
     */

    int pid;
    // parent to child
    int pipefd[2];
    // child to parent
    int pipe2fd[2];

    int round = 0;
    int parentTurn = 1;

    // pipe error
    if (pipe(pipefd) == -1 || pipe(pipe2fd) == -1)
    {
        fprintf(1, "error: pipe\n");
        exit(1);
    }

    // fork error
    if ((pid = fork()) == -1)
    {
        fprintf(1, "error: fork\n");
        exit(1);
    }

    if (pid == 0)
    {
        // child process
        unsigned char data = 0;
        close(pipe2fd[0]);
        close(pipefd[1]);
        while (round < n)
        {
            if (!(parentTurn == 1))
            {
                write(pipe2fd[1], &data, 1);
                parentTurn = 1;
                round++;
            }
            else
            {
                read(pipefd[0], &data, 1);
                data = data + 1;
                parentTurn = 0;
            }
        }
        close(pipe2fd[1]);
        close(pipefd[0]);
        exit(0);
    }
    else
    {
        // parent process
        unsigned char data = 0;
        close(pipe2fd[1]);
        close(pipefd[0]);
        while (round < n)
        {
            if (parentTurn == 1)
            {
                write(pipefd[1], &data, 1);
                parentTurn = 0;
            }
            else
            {
                read(pipe2fd[0], &data, 1);
                data = data + 1;
                round++;
                parentTurn = 1;
            }
        }
        int *status = 0;
        wait(status);
        close(pipe2fd[0]);
        close(pipefd[1]);
    }
    // print # of time in n rounds
    printf("# of time in %d rounds: %d[μs]\n", n, rtime() - start_time);
    exit(0);
}
