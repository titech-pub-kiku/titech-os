

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stdio.h"

int main(){
    printf("exec test03 file!\n");
    int fd = open("03.txt",  O_CREATE| O_WRONLY |O_APPEND);
    write(fd, "TOKYOTECH\n", 10);
    lseek(fd, -4, SEEK_CUR);
    write(fd, "pppppppp\n", 9);
    close(fd);
    printf("finish test03!\n");
    exit(0);
}
