typedef struct {
	int   uid;
	char  username[30];
	char  password[128];
	float balance;
	int   buylist[128];
	int   quantidade[128];
	bool  admin;
	bool  valid;
} userdb;

// FILE LAYOUT: ID[#]USERNAME[#]PASSWORD[#]ADMIN[#]BALANCE[#]QUANTIDADE[#]BUYLIST

userdb users[512];
char   myusr[30];
int    numUsers = 0;

void parseUsers();
void writeUsers();
void resetUsers();
void getUsernameById(int id, char out[]);
void removeAllItems(const int id, const int itemid);
void removeItem(const int id, const int itemid, const int quant);
void addItem(const int id, const int itemid, const int quant);
void addBalance(const int id, float b);
void removeBalance(const int id, float b);
void getAllBuylistItems(const int id, char out[]);
void getAllQuantidade(const int id, char out[]);
bool deleteUser(int id);
bool validatePassword(const int userid, char *pw);
bool isAdmin(const int id);
bool isValid(const int id);
int getLastUserId();
int createUser(char name[], char pw[], bool isadmin);
int getIdByUsername(char user[]);
int getUserPosition(const int id);
int getQuantidade(const int id, const int buylist_index);
int getLastBuylistIndex(const int id);
int getTotalQuant(const int id);
int getUserId(const int index);
int getBuyListItemId(const int id, const int buylist_index);
int getIndexFromBuylist(const int id, const int itemid);
float getBalance(const int id);

void resetUsers(){
	memset(users, 0, sizeof(users));
}

void writeUsers(){
	char fp[512];
	char fp_temp[512];

	getUsersFilePath(fp);
	getUsersTempFilePath(fp_temp);
	FILE *fw = fopen(&fp_temp[0], "w");
	if(fw != NULL){
		int i = 0;
		for(i = 0; i < 512; i++){
			if(users[i].valid == true){
				char by[512];
				char qt[512];
				int  admin = 0;
				int  k     = 0;
				for(k = 0; k < 127; k++){
					if(k > 0){
						if(users[i].buylist[k] > 0){
							sprintf(by, "%s;%d", by, users[i].buylist[k]);
						}
					}
					else if(k == 0){
						sprintf(by, "%d", users[i].buylist[k]);
					}
				}
				for(k = 0; k < 127; k++){
					if(k > 0){
						if(users[i].quantidade[k] > 0){
							sprintf(qt, "%s;%d", qt, users[i].quantidade[k]);
						}
					}
					else if(k == 0){
						sprintf(qt, "%d", users[i].quantidade[k]);
					}
				}
				if(users[i].admin == true){
					admin = 1;
				}
				fprintf(fw, "%d[#]%s[#]%s[#]%d[#]%.2f[#]%s[#]%s\n", users[i].uid, users[i].username,
						users[i].password, admin, users[i].balance, qt, by);
			}
		}

		fclose(fw);
		remove(fp);
		rename(fp_temp, fp);
	}
}

void parseUsers(){
	char fp[512];

	resetUsers();
	getUsersFilePath(fp);
	int i = 0;
	if(fileExists(&fp[0]) == true){
		FILE *f = fopen(&fp[0], "r");
		if(f != NULL){
			char line[256];
			while(fgets(line, sizeof(line), f) != NULL){
				if(strcmp(line, "\n") == 0){
					continue;
				}
				if(strlen(line) > 1){
					char *tk_id    = strtok(line, FILE_DELIM);
					char *tk_user  = strtok(NULL, FILE_DELIM);
					char *tk_pw    = strtok(NULL, FILE_DELIM);
					char *tk_admin = strtok(NULL, FILE_DELIM);
					char *tk_bal   = strtok(NULL, FILE_DELIM);
					char *tk_qt    = strtok(NULL, FILE_DELIM);
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

					int  z     = 1;
					char *tkb2 = strtok(tk_qt, BUYLIST_DELIM);
					if(strcmp(tkb2, "0") == 0){
						i++;
						continue;
					}
					else{
						users[i].quantidade[0] = strtol(tkb2, NULL, 0);
					}

					while(tkb2 != NULL || strlen(tkb2) >= 1){
						tkb2 = strtok(NULL, BUYLIST_DELIM);
						if(tkb2 != NULL){
							int val = strtol(tkb2, NULL, 0);
							users[i].quantidade[z] = val;
							z++;
						}
						else{
							break;
						}
					}

					z = 1;
					char *tkb = strtok(tk_list, BUYLIST_DELIM);
					if(strcmp(tkb, "0") == 0){
						i++;
						continue;
					}
					else{
						users[i].buylist[0] = strtol(tkb, NULL, 0);
					}

					while(tkb != NULL || strlen(tkb) >= 1){
						tkb = strtok(NULL, BUYLIST_DELIM);
						if(tkb != NULL){
							int val = strtol(tkb, NULL, 0);
							users[i].buylist[z] = val;
							z++;
						}
						else{
							break;
						}
					}
					i++;
				}
			}
			fclose(f);
		}
	}

	numUsers = i;

	i++;
	for(; i < 256; i++){
		users[i].valid = false;
	}
}

int getLastUserId(){
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

bool deleteUser(int id){
	parseUsers();
	if(id < 0){
		printErr("ID negativo\n");
		return(false);
	}

	int size = numUsers;
	int pos  = getUserPosition(id);
	users[pos].valid = false;

	writeUsers();
	parseUsers();

	if(size != numUsers){
		return(true);
	}
	else{
		return(false);
	}
}

int createUser(char name[], char pw[], bool isadmin){
	int size   = numUsers;
	int next   = size + 1;
	int nextId = getLastUserId() + 1;

	users[next].uid     = nextId;
	users[next].valid   = true;
	users[next].admin   = isadmin;
	users[next].balance = 0.00;

	unsigned int out        = crc32b(pw);
	char         outstr[32] = "";
	sprintf(outstr, "%x", out);

	strcpy(users[next].username, name);
	strcpy(users[next].password, outstr);

	writeUsers();
	parseUsers();

	if(getLastUserId() == nextId){
		return(nextId);
	}
	else{
		return(-1);
	}
}

bool validatePassword(const int userid, char *pw){
	parseUsers();
	unsigned int out        = crc32b(pw);
	char         outstr[32] = "";
	sprintf(outstr, "%x", out);


	if(strcmp(users[getUserPosition(userid)].password, outstr) == 0){
		return(true);
	}

	return(false);
}

int getIdByUsername(char user[]){
	int i = 0;

	for(; i < numUsers; i++){
		if(users[i].valid == true){
			if(strcmp(users[i].username, user) == 0){
				return(users[i].uid);
			}
		}
	}

	return(-1);
}

void getUsernameById(const int id, char out[]){
	parseUsers();
	int pos = getUserPosition(id);

	strcpy(out, users[pos].username);
}

int getUserPosition(const int id){
	int i = 0;

	for(; i < numUsers; i++){
		if(users[i].valid == true){
			if(users[i].uid == id){
				return(i);
			}
		}
	}

	return(-1);
}

float getBalance(const int id){
	const int pos = getUserPosition(id);

	return(users[pos].balance);
}

bool isAdmin(const int id){
	const int pos = getUserPosition(id);

	return(users[pos].admin);
}

bool isValid(const int id){
	const int pos = getUserPosition(id);

	return(users[pos].valid);
}

int getQuantidade(const int id, const int buylist_index){
	const int pos = getUserPosition(id);

	return(users[pos].quantidade[buylist_index]);
}

int getBuyListItemId(const int id, const int buylist_index){
	const int pos = getUserPosition(id);

	return(users[pos].buylist[buylist_index]);
}

int getTotalQuant(const int id){
	const int pos = getUserPosition(id);
	int       sum = 0;
	int       i   = 0;

	for(i = 0; i < 127; i++){
		if(users[pos].quantidade[i] > 0){
			sum += users[pos].quantidade[i];
		}
	}

	return(sum);
}

void removeBalance(const int id, float b){
	const int pos = getUserPosition(id);

	users[pos].balance -= b;
}

void addBalance(const int id, float b){
	const int pos = getUserPosition(id);

	users[pos].balance += b;
}

int getLastBuylistIndex(const int id){
	const int pos_user = getUserPosition(id);
	int       i        = 0;
	int       index    = -1;

	for(i = 0; i < 127; i++){
		if(users[pos_user].buylist[i] > 0){
			index = i;
		}
	}

	return(index);
}

void addItem(const int id, const int itemid, const int quant){
	const int pos_user = getUserPosition(id);
	bool      exists   = false;
	int       arr      = -1;
	int       i        = 0;
	const int size     = sizeof(users[pos_user].buylist);

	for(i = 0; i < size; i++){
		if(users[pos_user].buylist[i] == itemid){
			exists = true;
			arr    = i;
			break;
		}
	}

	if(exists == true){
		users[pos_user].quantidade[arr] += quant;
	}
	else{
		int lastindex = getLastBuylistIndex(id);
		users[pos_user].buylist[lastindex + 1]     = itemid;
		users[pos_user].quantidade[lastindex + 1] += quant;
	}
}

void removeItem(const int id, const int itemid, const int quant){
	const int pos_user = getUserPosition(id);
	bool      exists   = false;
	int       arr      = -1;
	int       i        = 0;
	const int size     = sizeof(users[pos_user].buylist);

	for(i = 0; i < size; i++){
		if(users[pos_user].buylist[i] == itemid){
			exists = true;
			arr    = i;
			break;
		}
	}

	if(exists == true){
		users[pos_user].quantidade[arr] -= quant;
	}
}

void removeAllItems(const int id, const int itemid){
	const int pos_user = getUserPosition(id);
	bool      exists   = false;
	int       arr      = -1;
	int       i        = 0;
	const int size     = sizeof(users[pos_user].buylist);

	for(i = 0; i < size; i++){
		if(users[pos_user].buylist[i] == itemid){
			exists = true;
			arr    = i;
			break;
		}
	}

	if(exists == true){
		users[pos_user].quantidade[arr] = 0;
		users[pos_user].buylist[arr]    = 0;
	}
}

int getUserId(const int index){
	return(users[index].uid);
}

void getAllBuylistItems(const int id, char out[]){
	const int pos       = getUserPosition(id);
	char      list[256] = "";
	int       k         = 0;

	for(k = 0; k < 127; k++){
		if(users[pos].buylist[k] > 0){
			if(k != 0){
				sprintf(list, "%s;%d", list, users[pos].buylist[k]);
			}
			else{
				sprintf(list, "%d", users[pos].buylist[k]);
			}
		}
	}

	strcpy(out, list);
}

void getAllQuantidade(const int id, char out[]){
	const int pos       = getUserPosition(id);
	char      list[256] = "";
	int       k         = 0;

	for(k = 0; k < 127; k++){
		if(users[pos].quantidade[k] > 0){
			if(k != 0){
				sprintf(list, "%s;%d", list, users[pos].quantidade[k]);
			}
			else{
				sprintf(list, "%d", users[pos].quantidade[k]);
			}
		}
	}

	strcpy(out, list);
}

int getIndexFromBuylist(const int id, const int itemid){
	const int pos = getUserPosition(id);
	int       i   = 0;

	for(i = 0; i < 127; i++){
		if(users[pos].buylist[i] > 0){
			if(users[pos].buylist[i] == itemid){
				return(i);
			}
		}
	}

	return(-1);
}
