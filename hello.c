#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

int main (int argc, char *argv[]){
    printf("\n\nGOOD NEWS, HELLO IS WORKING!\n");

    for (int i = 0; i < argc; i ++){
        printf("ARGV INPUT %d is [%s]\n", i , argv [i]);
    }
    //printf(" the argv input is [%s]\n\n", argv[0]);
    char d[100];
    scanf("%s",d);
    printf("THE MODIFIED STDIN is [%s]\n\n", d);

    exit(0);
}