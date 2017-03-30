#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <termios.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include "lib_dir.c"

#define TXT_SPEED 2.0
#define FILE_DELIM ";"

void ePrint(char *text){
    int i = 0;
    int len = strlen(text);
    while(text[i] != '\0'){
        printf("%c", (text[i]));
        fflush(stdout);
        usleep(1000*40/TXT_SPEED);
        i++;
    }
}

void ClearScreen(){
    printf("\033[2J\033[1;1H");
}

void FillArray(int *data, int size, int value){
    int i = 0;
    for(i = 0; i < size; i++){
        data[i] = value;
    }
}

