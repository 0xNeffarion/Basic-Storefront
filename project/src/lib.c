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

void enterPrompt();
void ePrint(const char *text);
void printErr(const char *fmt, ...);
void clearScreen();
void fillArray(int *data, int size, int value);
void removeSpaces(char *src);
bool isInt(const char *str);
int *intcpy(int const *src, size_t len);
unsigned int rand_interval(unsigned int min, unsigned int max);
unsigned int crc32b(char *message);

/*
 * I: Prompts user to press enter to continue
 * P: -
 * R: -
 */
void enterPrompt(){
	printf("Pressione [Enter] para continuar.\n");
	while(getchar() != '\n'){
		;
	}
	getchar();
}

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
		usleep(1000 * 40 / TEXT_WRITE_SPEED);
		i++;
	}
}

/*
 * I: Printf wrapper for errors
 * P: Same as printf
 * R: -
 */
void printErr(const char *fmt, ...){
	printf(COLOR_RED "[ERRO] " COLOR_RESET);
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
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
bool isInt(const char *str){
	if((atoi(str) != 0)){
		return(true);
	}
	return(false);
}

/*
 * I: Copies/Duplicates int array
 * P: int * src: first index pointer, len: lenght to copy
 * R: Copied array
 */
int *intcpy(int const *src, size_t len){
	int *p = malloc(len * sizeof(int));

	memcpy(p, src, len * sizeof(int));
	return(p);
}

/*
 * I: Removes spaces from string
 * P: char* src: string to remove spaces
 * R: -
 */
void removeSpaces(char *src){
	char *i = src;
	char *j = src;

	while(*j != 0){
		*i = *j++;
		if(*i != ' '){
			i++;
		}
	}
	*i = 0;
}

/*
 * I: Generates random number
 * P: int min: minimum, int max: maximum (exclusive)
 * R: random number between min and max-1
 */
unsigned int rand_interval(unsigned int min, unsigned int max){
	int r;
	const unsigned int range   = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit   = buckets * range;

	do {
		r = rand();
	} while(r >= limit);

	return(min + (r / buckets));
}

/*
 * I: Simple strig hashing with crc32
 * P: char* message: string to hash
 * R: digested string
 */
unsigned int crc32b(char *message){
	int          i, j;
	unsigned int byte, crc, mask;

	i   = 0;
	crc = 0xFFFFFFFF;
	while(message[i] != 0){
		byte = message[i];
		crc  = crc ^ byte;
		for(j = 7; j >= 0; j--){
			mask = -(crc & 1);
			crc  = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return(~crc);
}

// DECLARATIONS

#include "lib_dir.c"
#include "lib_files.c"
#include "lib_dates.c"
#include "lib_stocks.c"
#include "lib_users.c"
#include "lib_stats.c"
#include "lib_stats_cv.c"
