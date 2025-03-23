#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
    // out put pipe
    int d ;
    scanf("%d",&d);
    printf("HERE IS PIPE, WHAT WE RECEIVED is [%d]\n\n", d);
}