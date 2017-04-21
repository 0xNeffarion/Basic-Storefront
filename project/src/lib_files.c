
void getUsersFilePath(char buff[]);
void getUsersTempFilePath(char buff[]);
void getStocksFilePath(char buff[]);
void getStocksTempFilePath(char buff[]);
bool fileExists(char* f);
bool readline(const char* f, const int line, char out[]);
bool append(const char* f, const char* appstr);
bool create(const char* f);

/*
* I: Retrieves full filepath for users data file
* P: char[] buff: buffer to output
* R: -
*/
void getUsersFilePath(char buff[]){
    char b[512];
    getDataDirectory(b);
    sprintf(buff, "%s/%s", b, USERS_FILENAME);
}

/*
* I: Retrieves full filepath for users temp data temporary file
* P: char[] buff: buffer to output
* R: -
*/
void getUsersTempFilePath(char buff[]){
    char b[512];
    getDataDirectory(b);
    sprintf(buff, "%s/%s", b, USERS_TEMP_FILENAME);
}

/*
* I: Retrieves full filepath for items stock data file
* P: char[] buff: buffer to output
* R: -
*/
void getStocksFilePath(char buff[]){
    char b[512];
    getDataDirectory(b);
    sprintf(buff, "%s/%s", b, ITEMS_FILENAME);
}

/*
* I: Retrieves full filepath for items stock data temporary file
* P: char[] buff: buffer to output
* R: -
*/
void getStocksTempFilePath(char buff[]){
    char b[512];
    getDataDirectory(b);
    sprintf(buff, "%s/%s", b, ITEMS_TEMP_FILENAME);
}

/*
* I: Check if file exists
* P: char* f: file
* R: true if exists, otherwise false
*/
bool fileExists(char* f){
    if(access(f, F_OK) != -1) {
        return true; // Exists
    } else {
        return false;
    }
}

/*
* I: Reads a specified line
* P: char* f: file | int line: line to read (0+) | char[] out: output from line
* R: true if line was read, otherwise false
*/
bool readline(const char* f, const int line, char out[]){
    FILE *fa = fopen(f, "r");
    if(fa!=NULL && line >= 0){
        int i = 0, size = strlen(out);
        while(fgets(out,size,fa) != NULL){
            if(i==line){
                fclose(fa);
                return true;
            }
            i++;
        }
    }

    fclose(fa);
    return false;
}

/*
* I: Appends string to end of file
* P: char* f: file | char* appstr: char string
* R: true if it appends without errors, otherwise false
*/
bool append(const char* f, const char* appstr){
    FILE *fa = fopen(f, "a");
    int r = false;
    if(fa!=NULL){
	    if(fprintf(fa,"%s",appstr) > 0){
	        r = true;
	    }
	}

    fclose(fa);
    return r;
}

/*
* I: Creates blank empty file
* P: char* f: file | char[] str: char string
* R: true if it creates without errors, otherwise false
*/
bool create(const char* f){
    FILE *fa = fopen(f, "w+");
    int r = false;
    if(fa!=NULL){
	   r = true;
	  }

    fclose(fa);
    return r;
}
