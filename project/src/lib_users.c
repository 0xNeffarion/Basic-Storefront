typedef struct{
   int uid;
  char username[30];
  char password[128];
} userdb;

userdb users[256];
int numRegs = 0;

void parseUsers(){
	char* fp = getUsersFilePath();
	FILE *f = fopen(fp, "r");
	if(f!=NULL){
		char line[185];
		int i = 0;
		while(fgets(line,sizeof(line),f) != NULL){
			if(strlen(line) > 1){
				char* tk_id = strtok(line,FILE_DELIM);
				char* tk_user = strtok(line,FILE_DELIM);
				char* tk_pw = strtok(line,FILE_DELIM);

				users[i].uid = atoi(tk_id);
				strcpy(users[i].username,tk_user);
				strcpy(users[i].password,tk_pw);
				i++;
			}
		}
		free(fp);
		fclose(f);
		numRegs = i+1;
	}
}