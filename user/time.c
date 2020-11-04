#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(1, "usage: %s command\n", argv[0]);
        exit(1);
    }
    int i, start_time;
    char *args[argc - 1];
    for (i = 0; i < argc - 1; i++)
    {
        args[i] = argv[i + 1];
    }

    start_time = uptime();
    int pid = fork();
    if (pid == 0)
    {
        exec(args[0], args);
        // ここには戻ってこない
        exit(1);
    }
    else
    {
        wait(&pid);
        int elapse_time = uptime() - start_time;

        printf("# of ticks in command : ");
        for (i = 0; i < argc - 1; i++)
        {
            printf("%s ", args[i]);
        }
        printf(": %d\n", elapse_time);
    }
    exit(0);
}
