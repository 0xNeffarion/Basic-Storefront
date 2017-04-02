
void getHomeDirectory(char buff[]);
void getDataDirectory(char buff[]);
int dirExists(const char* mydir);
int deleteDir(const char* mydir);
int createDir(const char* mydir);

void getHomeDirectory(char buff[]){
    char* homedir = malloc(512);
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    sprintf(buff,"%s",homedir);
}

void getDataDirectory(char buff[]){
    char b[512];
    getHomeDirectory(b);
    sprintf(buff, "%s/%s", b, DATA_FOLDERNAME);
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
    
    free(cdir);
    return returnVal;
}

int deleteDir(const char* mydir){
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
            return 0;
        }
        return 1;
    }
    
    return 1;
}

int createDir(const char* mydir){
    return mkdir(mydir, 0777);
}