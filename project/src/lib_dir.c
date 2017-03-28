const char dataFolderName[15] = "labc_sm_data";

static char* getHomeDirectory(){
    char* homedir = malloc(512);
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}

static char* getDataDirectory(){
    char* homedir = getHomeDirectory();
    char* end = malloc(512);
    sprintf(end, "%s/%s", homedir, dataFolderName);
    return end;
}

static int dirExists(char* mydir){
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

static int createDir(char* mydir){
    return mkdir(mydir, 0777);
}




