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
int validatePassword(int userid, char* pw);
int getIdByUsername(char[] user, char[] out);
int getIdByUsername(char[] user, char[] out);
int getUsernameById(int id, char[] out);

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

int validatePassword(int userid, char* pw){
  int i = 0, size = sizeof(users);
  for(i = 0; i < size; i++){
    if(users[i].username != NULL && users[i].uid != NULL){
      if(users[i].uid == userid){
        if(strcmp(&(users[i].password[0]), pw) == 0){
          return true;
        }
      }
    }
  }
  return false;
}

int getIdByUsername(char[] user, char[] out){
    int i = 0, size = sizeof(users);
    for(i = 0; i < size; i++){
      if(users[i].username != NULL && users[i].uid != NULL){
        if(strcmp(&(users[i].username[0]), user) == 0){
          return users[i].uid;
        }
      }
    }

    return -1;
}

int getUsernameById(int id, char[] out){
    int i = 0, size = sizeof(users);
    for(i = 0; i < size; i++){
      if(users[i].username != NULL && users[i].uid != NULL){
        if(users[i].uid == id){
          strcpy(out, users[i].username);
          return users[i].uid;
        }
      }
    }

    return -1;
}
