const char dataFolderName[15] = "labc_sm_data";

char* getHomeDirectory(){
    char* homedir = malloc(512);
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}

char* getDataDirectory(){
    char* homedir = getHomeDirectory();
    char* end = malloc(512);
    sprintf(end, "%s/%s", homedir, dataFolderName);
    return end;
}

int dirExists(const char* mydir){
    DIR* cdir = opendir(mydir);
    int returnVal = 0;
    if (cdir){
        returnVal = 0;
        closedir(cdir);
    }else{
        returnVal = -1;
    }
    
    return returnVal;
}

int createDir(const char* mydir){
    return mkdir(mydir, 0777);
}




