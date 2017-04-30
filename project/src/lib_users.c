typedef struct {
	int   uid;
	char  username[30];
	char  password[128];
	float balance;
	int   buylist[128];
        int quant[128];
	bool  admin;
	bool  valid;
} userdb;

// FILE LAYOUT: ID[#]USERNAME[#]PASSWORD[#]ADMIN[#]BALANCE[#]BUYLIST

userdb users[512];
int    numUsers = 0;

void parseUsers();
void deleteUser(int id);
int getLastId();
int createUser(char name[], char pw[], bool isadmin);
bool validatePassword(int userid, char *pw);
int getIdByUsername(char user[]);
int getUsernameById(int id, char out[]);
int getPosition(int id);

void parseUsers(){
	char fp[512];

	getUsersFilePath(fp);
	int i = 0;
	if(fileExists(&fp[0]) == true){
		FILE *f = fopen(&fp[0], "r");
		if(f != NULL){
			char line[256];
			while(fgets(line, sizeof(line), f) != NULL){
				if(strlen(line) > 1){
					char *tk_id    = strtok(line, FILE_DELIM);
					char *tk_user  = strtok(NULL, FILE_DELIM);
					char *tk_pw    = strtok(NULL, FILE_DELIM);
					char *tk_admin = strtok(NULL, FILE_DELIM);
					char *tk_bal   = strtok(NULL, FILE_DELIM);
					char *tk_list  = strtok(NULL, FILE_DELIM);
					users[i].uid     = atoi(tk_id);
					users[i].balance = atof(tk_bal);
					users[i].admin   = false;
					strcpy(users[i].username, tk_user);
					strcpy(users[i].password, tk_pw);
					users[i].valid = true;
					if(atoi(tk_admin) == 1){
						users[i].admin = true;
					}

					int  *buyl = malloc(128);
					int  z     = 1;
					char *tkb  = strtok(tk_list, BUYLIST_DELIM);
					if(strcmp(tkb, "-1") == 0){
						i++;
						continue;
					}
					else{
						*buyl = strtol(tkb, NULL, 0);
					}

					while(tkb != NULL || strlen(tkb) >= 1){
						tkb = strtok(NULL, BUYLIST_DELIM);
						if(tkb != NULL){
							int val = strtol(tkb, NULL, 0);
							buyl++;
							*buyl = val;
						}
						else{
							break;
						}
						z++;
					}
					memcpy(users[i].buylist, buyl, z);
					memcpy(users[i].quant, buyl, z);
					i++;
				}
			}
			fclose(f);
		}
	}

	numUsers = i + 1;

	i++;
	for(; i < 256; i++){
		users[i].valid = false;
	}
}

int getLastId(){
	char fp[512];
	char line[256];

	getUsersFilePath(fp);
	FILE *fr = fopen(&fp[0], "r");
	int  i   = -1;
	if(fr != NULL){
		while(fgets(line, sizeof(line), fr) != NULL){
			if(strlen(line) > 1){
				char *tk_id = strtok(line, FILE_DELIM);
				int  u      = atoi(tk_id);
				if(u > 0){
					if(u > i){
						i = u;
					}
				}
			}
		}
	}

	return(i);
}

void deleteUser(int id){
	char fp_users[512];

	getUsersFilePath(fp_users);
	char fp_temp[512];
	getUsersTempFilePath(fp_temp);

	if(fileExists(&fp_users[0]) == false){
		printErr("Ficheiro de utilizadores nao existe!\n");
		return;
	}

	if(id < 0){
		printErr("ID negativo\n");
		return;
	}

	int  did = 0;
	FILE *fr = fopen(fp_users, "r");
	FILE *fw = fopen(fp_temp, "w+");

	if(fr != NULL && fw != NULL){
		char line[256];
		char linecp[256];
		while(fgets(line, sizeof(line), fr) != NULL){
			if(strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0){
				continue;
			}
			if(strlen(line) > 1){
				strcpy(linecp, line);
				char *tk_id = strtok(line, FILE_DELIM);
				int  myid   = atoi(tk_id);
				if(myid != id){
					fprintf(fw, "%s", &linecp[0]);
				}
				else{
					did = 1;
				}
			}
		}

		fclose(fr);
		fclose(fw);

		remove(fp_users);
		rename(fp_temp, fp_users);

		if(did == 1){
			printErr("Utilizador '%d' nao existe\n", id);
		}
		parseUsers();
	}
}

int createUser(char name[], char pw[], bool isadmin){
	char fp[512];

	getUsersFilePath(fp);
	if(fileExists(&fp[0]) == true){
		FILE *fa = fopen(&fp[0], "a");
		if(fa != NULL){
			int a = -1;
			if(isadmin == true){
				a = 1;
			}
			int myid = getLastId() + 1;
			fprintf(fa, "\n%d[#]%s[#]%s[#]%d[#]0.00[#]-1", myid, name, pw, a);
			fclose(fa);
			printf("Utilizador [%s] registado com sucesso! Id: %d\n\n", name, myid);
			parseUsers();
			return(myid);
		}
	}
	return(-1);
}

bool validatePassword(int userid, char *pw){
	int i = 0, size = numUsers;

	for(i = 0; i < size; i++){
		if(users[i].valid == true){
			if(users[i].uid == userid){
				if(strcmp((users[i].password), pw) == 0){
					return(true);
				}
			}
		}
	}
	return(false);
}

int getIdByUsername(char user[]){
	int i = 0, size = numUsers;

	for(; i < size; i++){
		if(users[i].valid == true){
			if(strcmp(users[i].username, user) == 0){
				return(users[i].uid);
			}
		}
	}

	return(-1);
}

int getUsernameById(int id, char out[]){
	int i = 0, size = numUsers;

	for(i = 0; i < size; i++){
		if(users[i].valid == true){
			if(users[i].uid == id){
				strcpy(out, users[i].username);
				return(users[i].uid);
			}
		}
	}

	return(-1);
}

int getPosition(int id){
	int i = 0, size = numUsers;

	for(i = 0; i < size; i++){
		if(users[i].valid == true){
			if(users[i].uid == id){
				return(i);
			}
		}
	}

	return(-1);
}
