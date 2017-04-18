#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include "const.c"

void ePrint(const char *text);
void printErr(const char *fmt, ...);
void clearScreen();
void fillArray(int *data, int size, int value);
bool isInt(const char *str);
int* intcpy(int const * src, size_t len);

/*
* I: Writes to console a string with typewritter effect
* P: char* text: text to write
* R: -
*/
void ePrint(const char *text){
    int i = 0;
    while(text[i] != '\0'){
        printf("%c", (text[i]));
        fflush(stdout);
        usleep(1000*40/TEXT_WRITE_SPEED);
        i++;
    }
}

/*
* I: Printf wrapper for errors
* P: Same as printf
* R: -
*/
void printErr(const char *fmt, ...) {
    printf(COLOR_RED "[ERRO] " COLOR_RESET);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt , args);
    va_end(args);
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
* I: Fills array with a value
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

/*
* I: Checks if string is a valid integer
* P: char* str: string to check
* R: true if string is an int, otherwise false
*/
bool isInt(const char *str)
{
   if (*str == '-'){
      ++str;
   }

   if (!*str){
      return false;
   }

   while (*str){
      if (!isdigit(*str))
         return false;
      else
         ++str;
   }
   return true;
}

/*
* I: Copies/Duplicates int array
* P: int * src: first index pointer, len: lenght to copy
* R: Copied array
*/
int* intcpy(int const * src, size_t len){
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}


// DECLARATIONS

#include "lib_dir.c"
#include "lib_files.c"
#include "lib_users.c"
