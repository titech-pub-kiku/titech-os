

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stdio.h"

int main(){
    printf("exec test04 file!\n");
    int fd = open("04.txt",  O_CREATE| O_WRONLY |O_APPEND);
    write(fd, "TOKYOTECH\n", 10);
    int res = lseek(fd, 0, SEEK_END);
    printf("res = %d\n",res);
    write(fd, "pppppppp\n", 9);
    close(fd);
    printf("finish testExec!\n");
    exit(0);
}
