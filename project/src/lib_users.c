typedef struct{
   int uid;
  char username[30];
  char password[128];
  float balance;
  int buylist[128];
} userdb;

userdb users[256];
int numRegs = 0;

void parseUsers();

void parseUsers(){
	char fp[512];
	getUsersFilePath(fp);
	printf("%s\n", &fp[0]);
	if(fileExists(&fp[0])==true){
		FILE *f = fopen(&fp[0], "r");
		if(f!=NULL){
			char line[185];
			int i = 0;
			while(fgets(line,sizeof(line),f) != NULL){
				if(strlen(line) > 1){
					char* tk_id = strtok(line,FILE_DELIM);
					char* tk_user = strtok(NULL,FILE_DELIM);
					char* tk_pw = strtok(NULL,FILE_DELIM);
					printf("PARSED USER %d: %s\n", atoi(tk_id),tk_user);

					users[i].uid = atoi(tk_id);
					strcpy(users[i].username,tk_user);
					strcpy(users[i].password,tk_pw);
					i++;
				}
			}
			fclose(f);
			numRegs = i+1;
		}
	}
}
