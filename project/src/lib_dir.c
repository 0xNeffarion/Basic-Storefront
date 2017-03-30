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
    sprintf(end, "%s/%s", homedir, DATA_FOLDERNAME);
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

int deleteDir(const char* mydir){
    char params[256];
    sprintf(params, "-rf \"%s\"", mydir);
    if(fork()){
        execvp("rm", &params);
    }else{
        wait(NULL);
        usleep(1000*1000);
        if(!dirExists(mydir)){
            return 0;
        }
        return 1;
    }
    
    return 1;
}

int createDir(const char* mydir){
    return mkdir(mydir, 0777);
}




