
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stdio.h"

int main(){
    printf("exec test01!\n");
    int fd = open("01.txt",  O_CREATE| O_WRONLY |O_APPEND);
    write(fd, "test01initial\n", 14);
    lseek(fd, 0, SEEK_SET);
    write(fd, "ppppp\n", 6);
    close(fd);
    printf("finish test01!\n");
    exit(0);
}
