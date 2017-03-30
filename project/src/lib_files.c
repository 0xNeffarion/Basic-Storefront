const char usersFileName[17] = "reg_users.data"

char* getUsersFilePath(){
    const char *dataDir = getDataDirectory();
    char* retVal = malloc(512);
    sprintf(retVal, "%s/%s", dataDir, usersFileName);
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
* P: char* f: file | char[] str: char string
* R: 0 if it appends without errors, otherwise 1
*/
int append(const char* f, const char str[]){
    FILE *fa = fopen(f, "a");
    if(fa!=NULL){
	    if(fprintf(fa,"%s",&str) > 0){
	        fclose(fa);
	        return 0;
	    }
	}
    return 1;
}

/* 
* I: Creates blank file for writting
* P: char* f: file | char[] str: char string
* R: 0 if it appends without errors, otherwise 1
*/
int create(){
    FILE *fa = fopen(dataUser, "a");
    if(fa!=NULL){
	    if(fprintf(fa,"%s",&str) > 0){
	        fclose(fa);
	        return 0;
	    }
	}
    return 1;
}
