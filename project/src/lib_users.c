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
void deleteUser(int id);
int getLastId();
int createUser(char name[], char pw[]);
bool validatePassword(int userid, char* pw);
int getIdByUsername(char user[], char out[]);
int getUsernameById(int id, char out[]);
int getPosition(int id);

void parseUsers(){
	char fp[512];
	getUsersFilePath(fp);
	if(fileExists(&fp[0])==true){
		FILE *f = fopen(&fp[0], "r");
		if(f!=NULL){
			char line[256];
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

int getLastId(){
  char fp[512];
  char line[256];
	getUsersFilePath(fp);
  FILE *fr = fopen(&fp[0], "r");
  int i = -1;
  if(fr!=NULL){
    while(fgets(line,sizeof(line),fr) != NULL){
      if(strlen(line)>1){
        char* tk_id = strtok(line,FILE_DELIM);
        int u = atoi(tk_id);
        if(u>0){
          i = u;
        }
      }
    }
  }

  return i;
}

void deleteUser(int id){
  char fp_users[512];
	getUsersFilePath(fp_users);
  char fp_temp[512];
	getUsersTempFilePath(fp_temp);

  if(fileExists(&fp_users[0])==false){
    printErr("Ficheiro com os utilizadores nao existe!\n");
    return;
  }

  if(id < 0){
    printErr("ID negativo\n");
    return;
  }

  if(getLastId() < id){
    printErr("Utilizador com o id %d nao existe\n", id);
    return;
  }

  FILE *fr = fopen(fp_users, "r");
  FILE *fw = fopen(fp_temp, "w+");

  if(fr!=NULL && fw!=NULL){
    char line[256];
    while(fgets(line,sizeof(line),fr) != NULL){
      if(strlen(line) > 1){
        char* tk_id = strtok(line,FILE_DELIM);
        int myid = atoi(tk_id);
        if(myid != id){
          fprintf(fw,"%s\n", &line[0]);
        }
      }
    }

    fclose(fr);
    fclose(fw);

    remove(fp_users);
    rename(fp_temp,fp_users);

  }
}

int createUser(char name[], char pw[]){
  char fp[512];
	getUsersFilePath(fp);
  if(fileExists(&fp[0])==true){
    FILE *fa = fopen(&fp[0], "a");
    if(fa != NULL){
      int myid = getLastId()+1;
      fprintf(fa,"%d[#]%s[#]%s[#]0[#]-1\n",myid,name,pw);
      fclose(fa);
      printf("Utilizador %s registado com sucesso! Id: %d\n\n", name, myid);
      return myid;
    }
  }
  return -1;
}

bool validatePassword(int userid, char* pw){
  int i = 0, size = sizeof(users);
  for(i = 0; i < size; i++){
    if(users[i].username != NULL && users[i].uid > 0){
      if(users[i].uid == userid){
        if(strcmp(&(users[i].password[0]), pw) == 0){
          return true;
        }
      }
    }
  }
  return false;
}

int getIdByUsername(char user[], char out[]){
    int i = 0, size = sizeof(users);
    for(i = 0; i < size; i++){
      if(users[i].username != NULL && users[i].uid > 0){
        if(strcmp(&(users[i].username[0]), user) == 0){
          return users[i].uid;
        }
      }
    }

    return -1;
}

int getUsernameById(int id, char out[]){
    int i = 0, size = sizeof(users);
    for(i = 0; i < size; i++){
      if(users[i].username != NULL && users[i].uid > 0){
        if(users[i].uid == id){
          strcpy(out, users[i].username);
          return users[i].uid;
        }
      }
    }

    return -1;
}

int getPosition(int id) {
  int i = 0, size = sizeof(users);
  for(i = 0; i < size; i++){
    if(users[i].username != NULL && users[i].uid > 0){
      if(users[i].uid == id) {
	return i;
      }
    }
  }
  
  return -1;
}
