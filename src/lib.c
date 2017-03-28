#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void ePrint(char *text, float speed){
    int i = 0;
    int len = strlen(text);
    while(text[i] != '\0'){
        printf("%c", (text[i]));
        fflush(stdout);
        usleep(1000*45/speed);
        i++;
    }
}

void ClearScreen(){
    printf("\033[2J\033[1;1H");
}
