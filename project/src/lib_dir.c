void getHomeDirectory(char buff[]);
void getDataDirectory(char buff[]);
bool dirExists(const char* mydir);
bool deleteDir(const char* mydir);
bool createDir(const char* mydir);


/*
* I: Retrieves home directory path
* P: char[] buff: buffer to output
* R: -
*/
void getHomeDirectory(char buff[]){
    char* homedir = malloc(512);
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    sprintf(buff,"%s",homedir);
}

/*
* I: Retrieves data directory path in home
* P: char[] buff: buffer to output
* R: -
*/
void getDataDirectory(char buff[]){
    char b[512];
    getHomeDirectory(b);
    sprintf(buff, "%s/%s", b, DATA_FOLDERNAME);
}

/*
* I: Checks if directory exists
* P: char* mydir: directory to check
* R: true if exists, otherwise false
*/
bool dirExists(const char* mydir){
    DIR* cdir = opendir(mydir);
    int returnVal = false;
    if (cdir){
        returnVal = true;
        closedir(cdir);
    }else{
        returnVal = false;
    }

    return returnVal;
}

/*
* I: Deletes specified directory, including sub files and directories
* P: char* mydir: directory path to delete
* R: true if it was deleted, otherwise false
*/
bool deleteDir(const char* mydir){
    char params[256];
    sprintf(params, "-rf \"%s\"", mydir);
    char* d = &params[0];
    char* cmd = "rm";
    if(fork()){
        execlp(cmd, d, NULL);
    }else{
        wait(NULL);
        usleep(1000*1000);
        if(!dirExists(mydir)){
            return true;
        }
        return false;
    }

    return false;
}

/*
* I: Creates new directory with full chmod access (777)
* P: char* mydir: directory path to create
* R: false if failed, true otherwise
*/
bool createDir(const char* mydir){
    int r = mkdir(mydir, 0777);
    if(r==-1){
      return false;
    }else{
      return true;
    }
}
