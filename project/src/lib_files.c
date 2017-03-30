/* 
* I: Retrieves full filepath for users data file
* P: -
* R: Users data file path
*/
char* getUsersFilePath(){
    const char *dataDir = getDataDirectory();
    char* retVal = malloc(512);
    sprintf(retVal, "%s/%s", dataDir, USERS_FILENAME);
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
* I: Appends string to end of file
* P: char* f: file | char* appstr: char string
* R: 0 if it appends without errors, otherwise 1
*/
int append(const char* f, const char* appstr){
    FILE *fa = fopen(f, "a");
    if(fa!=NULL){
	    if(fprintf(fa,"%s",appstr) > 0){
	        fclose(fa);
	        return 0;
	    }
	}
    return 1;
}

/* 
* I: Creates blank empty file
* P: char* f: file | char[] str: char string
* R: 0 if it appends without errors, otherwise 1
*/
int create(const char* f){
    FILE *fa = fopen(f, "w+");
    if(fa!=NULL){
	    if(fprintf(fa,"") > 0){
	        fclose(fa);
	        return 0;
	    }
	}
    return 1;
}
