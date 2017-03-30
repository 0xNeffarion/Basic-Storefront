#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <termios.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include "const.c"
#include "lib_dir.c"
#include "lib_files.c"

/* 
* I: Writes to console a string with typewritter effect
* P: char* text: text to write
* R: -
*/
void ePrint(char *text){
    int i = 0;
    int len = strlen(text);
    while(text[i] != '\0'){
        printf("%c", (text[i]));
        fflush(stdout);
        usleep(1000*40/TEXT_WRITE_SPEED);
        i++;
    }
}

/* 
* I: Clears console/terminal screen
* P: -
* R: -
*/
void clearScreen(){
    printf("\033[2J\033[1;1H");
}

/* 
* I: Fills array with value
* P: int *data: array pointer | int size: array size
* P: int value: value to fill array
* R: -
*/
void fillArray(int *data, int size, int value){
    int i = 0;
    for(i = 0; i < size; i++){
        data[i] = value;
    }
}

