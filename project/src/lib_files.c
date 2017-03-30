/* 
* I: Retrieves full filepath for users data file
* P: -
* R: Users data file path
*/
char* getUsersFilePath(){
    char *dataDir = getDataDirectory();
    char* retVal = malloc(512);
    sprintf(retVal, "%s/%s", dataDir, USERS_FILENAME);
    free(dataDir);
    return retVal;
}

/* 
* I: Check if file exists
* P: char* f: file
* R: 0 if exists, otherwise 1
*/
int fileExists(const char* f){
    if(access(f, F_OK) != -1) {
        return 0; // Exists
    } else {
        return 1;
    }
}


/* 
* I: Reads a specified line
* P: char* f: file | int line: line to read (0+) | char[] out: output from line
* R: 0 if line was read, otherwise 1
*/
int readline(const char* f, const int line, char out[]){
    FILE *fa = fopen(f, "r");
    if(fa!=NULL && line >= 0){
        int i = 0, size = sizeof(out);
        while(fgets(out,size,fa) != NULL){
            if(i==line){
                fclose(fa);
                return 0;
            }
            i++;
        }
    }

    fclose(fa);
    return -1;
}

/* 
* I: Appends string to end of file
* P: char* f: file | char* appstr: char string
* R: 0 if it appends without errors, otherwise 1
*/
int append(const char* f, const char* appstr){
    FILE *fa = fopen(f, "a");
    int r = 1;
    if(fa!=NULL){
	    if(fprintf(fa,"%s",appstr) > 0){
	        r = 0;
	    }
	}

    fclose(fa);
    return r;
}

/* 
* I: Creates blank empty file
* P: char* f: file | char[] str: char string
* R: 0 if it appends without errors, otherwise 1
*/
int create(const char* f){
    FILE *fa = fopen(f, "ab+");
    int r = 1;
    if(fa!=NULL){
	   r = 0;
	}

    fclose(fa);
    return r;
}
