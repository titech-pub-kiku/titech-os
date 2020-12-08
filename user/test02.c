
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stdio.h"

int main(){
    printf("exec test02 file!\n");
    int fd = open("02.txt",  O_CREATE| O_WRONLY |O_APPEND);
    write(fd, "toukyoukougyoudaigaku\n", 22);
    lseek(fd, 200, SEEK_SET);
    int res = write(fd, "pppppppp\n", 9);
    printf("res = %d\n", res);
    close(fd);
    printf("finish test02!\n");
    exit(0);
}
