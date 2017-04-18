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
int getIdByUsername(char user[]);
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
          char* tk_bal = strtok(NULL,FILE_DELIM);
          char* tk_list = strtok(NULL,FILE_DELIM);
					printf("PARSED USER %d: %s | PASS: %s\n", atoi(tk_id),tk_user,tk_pw);
					users[i].uid = atoi(tk_id);
          users[i].balance = atof(tk_bal);
					strcpy(users[i].username,tk_user);
					strcpy(users[i].password,tk_pw);
          printf("buylist: %s\n", tk_list);
          int flag = 0, z = 1;
          while(1){
            if(flag==0){
              char* tk = strtok(tk_list, BUYLIST_DELIM);
              flag = 1;
              if(tk != NULL && strlen(tk) >= 1){
                int val = atoi(tk);
                users[i].buylist[0] = val;
              }else{
                break;
              }
            }else{
              char* tk = strtok(NULL, BUYLIST_DELIM);
              if(tk != NULL && strlen(tk) >= 1){
                int val = atoi(tk);
                users[i].buylist[z] = val;
                z++;
              }else{
                break;
              }
            }
          }

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
          if(u>i){
            i = u;
          }
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
    printErr("Ficheiro de utilizadores nao existe!\n");
    return;
  }

  if(id < 0){
    printErr("ID negativo\n");
    return;
  }

  int did = 0;
  FILE *fr = fopen(fp_users, "r");
  FILE *fw = fopen(fp_temp, "w+");

  if(fr!=NULL && fw!=NULL){
    char line[256];
    char linecp[256];
    while(fgets(line,sizeof(line),fr) != NULL){
      if(strcmp(line,"\n") == 0 || strcmp(line,"\r\n") == 0){
        continue;
      }
      if(strlen(line) > 1){
        strcpy(linecp,line);
        char* tk_id = strtok(line,FILE_DELIM);
        int myid = atoi(tk_id);
        if(myid != id){
          fprintf(fw,"%s", &linecp[0]);
        }else{
          did = 1;
        }
      }
    }

    fclose(fr);
    fclose(fw);

    remove(fp_users);
    rename(fp_temp,fp_users);

    if(did==1){
      printErr("Utilizador com o id '%d' nao existe\n", id);
    }

  }
}

int createUser(char name[], char pw[]){
  char fp[512];
	getUsersFilePath(fp);
  if(fileExists(&fp[0])==true){
    FILE *fa = fopen(&fp[0], "a");
    if(fa != NULL){
      int myid = getLastId()+1;
      fprintf(fa,"\n%d[#]%s[#]%s[#]0.0[#]-1",myid,name,pw);
      fclose(fa);
      printf("Utilizador [%s] registado com sucesso! Id: %d\n\n", name, myid);
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

int getIdByUsername(char user[]){
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
