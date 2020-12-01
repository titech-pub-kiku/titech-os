// pingpong2.c for xv6 (assignment #3 for CSC.T371)
// name: Haruki Kikuchi
// id: 18B04686

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(){
    printf("exec testExec file!\n");
    int fd = open("hoge.txt",  O_CREATE| O_WRONLY |O_APPEND);
    write(fd, "coconuts\n", 9);
    close(fd);
    printf("finish testExec!\n");
    exit(0);
}
