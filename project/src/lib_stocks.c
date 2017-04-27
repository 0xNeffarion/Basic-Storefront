typedef struct {
	int   uid;
	char  nome[64];
	float preco;
	int   quantidade;
	bool  valid;
} stockdb;

// FILE LAYOUT: ID[#]NOME[#]PRECO[#]QUANTIDADE

stockdb stocks[512];
int     numItems = 0;

void parseStock();
void writeStock();
int getLastStockId();
void deleteStockItem(int id);
int createItem(char name[], int quant, float price);
void changeItemPrice(int id, float newprice);
void changeItemQuant(int id, int newquant);
void changeItemName(int id, float newprice);

// TODO (remake)

void parseStock(){
	char fp[512];

	getStocksFilePath(fp);
	int i = 0;
	if(fileExists(&fp[0]) == true){
		FILE *f = fopen(&fp[0], "r");
		if(f != NULL){
			char line[256];
			while(fgets(line, sizeof(line), f) != NULL){
				if(strlen(line) > 1){
					char *tk_id    = strtok(line, FILE_DELIM);
					char *tk_nome  = strtok(NULL, FILE_DELIM);
					char *tk_preco = strtok(NULL, FILE_DELIM);
					char *tk_quant = strtok(NULL, FILE_DELIM);
					stocks[i].uid        = atoi(tk_id);
					stocks[i].quantidade = atoi(tk_quant);
					stocks[i].preco      = atof(tk_preco);
					strcpy(stocks[i].nome, tk_nome);
					stocks[i].valid = true;
					i++;
				}
			}
			fclose(f);
		}
	}

	numItems = i + 1;

	i++;
	for(; i < 256; i++){
		stocks[i].valid = false;
	}
}

void writeStock(){
	char fp[512];
	char fp_temp[512];
	char line[256];

	getStocksFilePath(fp);
	getStocksTempFilePath(fp_temp);
	FILE *fw = fopen(&fp_temp[0], "w");
	if(fw != NULL){
		int i = 0, size = numItems;
		for(i = 0; i < size; i++){
			if(stocks[i].valid == true){
				fprintf(fw, "%d[#]%s[#]%.2f[#]%d\n", stocks[i].uid, stocks[i].nome, stocks[i].preco, stocks[i].quantidade);
			}
		}

		fclose(fw);
		remove(fp);
		rename(fp_temp, fp);
	}
}

int getLastStockId(){
	char fp[512];
	char line[256];

	getStocksFilePath(fp);
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

void deleteStockItem(int id){
	char fp_stocks[512];

	getStocksFilePath(fp_stocks);
	char fp_temp[512];
	getStocksTempFilePath(fp_temp);

	if(fileExists(&fp_stocks[0]) == false){
		printErr("Ficheiro de stocks nao existe!\n");
		return;
	}

	if(id < 0){
		printErr("ID negativo\n");
		return;
	}

	int  did = 0;
	FILE *fr = fopen(fp_stocks, "r");
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

		remove(fp_stocks);
		rename(fp_temp, fp_stocks);

		if(did == 1){
			printErr("Item '%d' nao existe\n", id);
		}
		parseStock();
	}
}

int createItem(char name[], int quant, float price){
	char fp[512];

	getStocksFilePath(fp);
	if(fileExists(&fp[0]) == true){
		FILE *fa = fopen(&fp[0], "a");
		if(fa != NULL){
			int myid = getLastStockId() + 1;
			fprintf(fa, "\n%d[#]%s[#]%.2f[#]%d", myid, name, price, quant);
			fclose(fa);
			printf("Item [%s] registado em stock com sucesso! Id: %d\n\n", name, myid);
			parseStock();
			return(myid);
		}
	}
	return(-1);
}

void changeItemPrice(int id, float newprice){
	char fp_stocks[512];

	getStocksFilePath(fp_stocks);
	char fp_temp[512];
	getStocksTempFilePath(fp_temp);

	if(fileExists(&fp_stocks[0]) == false){
		printErr("Ficheiro de stocks nao existe!\n");
		return;
	}

	if(id < 0){
		printErr("ID negativo\n");
		return;
	}

	int  did = 0;
	FILE *fr = fopen(fp_stocks, "r");
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
					char linetok[256];
					strcpy(linetok, linecp);
					char *tk_id    = strtok(linetok, FILE_DELIM);
					char *tk_nome  = strtok(NULL, FILE_DELIM);
					char *tk_preco = strtok(NULL, FILE_DELIM);
					char *tk_quant = strtok(NULL, FILE_DELIM);

					char cutnome[60];
					int  cutid = atoi(tk_id);
					strcpy(cutnome, tk_nome);
					float cutpreco = atof(tk_preco);
					int   cutqt    = atoi(tk_quant);

					fprintf(fw, "\n%d[#]%s[#]%.2f[#]%d", cutid, cutnome, newprice, cutqt);
				}
			}
		}

		fclose(fr);
		fclose(fw);

		remove(fp_stocks);
		rename(fp_temp, fp_stocks);

		if(did == 1){
			printErr("Item '%d' nao existe\n", id);
		}
		parseStock();
	}
}

void changeItemQuant(int id, int newquant){
	char fp_stocks[512];

	getStocksFilePath(fp_stocks);
	char fp_temp[512];
	getStocksTempFilePath(fp_temp);

	if(fileExists(&fp_stocks[0]) == false){
		printErr("Ficheiro de stocks nao existe!\n");
		return;
	}

	if(id < 0){
		printErr("ID negativo\n");
		return;
	}

	int  did = 0;
	FILE *fr = fopen(fp_stocks, "r");
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
					char linetok[256];
					strcpy(linetok, linecp);
					char *tk_id    = strtok(linetok, FILE_DELIM);
					char *tk_nome  = strtok(NULL, FILE_DELIM);
					char *tk_preco = strtok(NULL, FILE_DELIM);
					char *tk_quant = strtok(NULL, FILE_DELIM);

					char cutnome[60];
					int  cutid = atoi(tk_id);
					strcpy(cutnome, tk_nome);
					float cutpreco = atof(tk_preco);
					int   cutqt    = atoi(tk_quant);

					fprintf(fw, "\n%d[#]%s[#]%.2f[#]%d", cutid, cutnome, cutpreco, newquant);
				}
			}
		}

		fclose(fr);
		fclose(fw);

		remove(fp_stocks);
		rename(fp_temp, fp_stocks);

		if(did == 1){
			printErr("Item '%d' nao existe\n", id);
		}
		parseStock();
	}
}

void changeItemName(int id, float newprice){
	char fp_stocks[512];

	getStocksFilePath(fp_stocks);
	char fp_temp[512];
	getStocksTempFilePath(fp_temp);

	if(fileExists(&fp_stocks[0]) == false){
		printErr("Ficheiro de stocks nao existe!\n");
		return;
	}

	if(id < 0){
		printErr("ID negativo\n");
		return;
	}

	int  did = 0;
	FILE *fr = fopen(fp_stocks, "r");
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
					char linetok[256];
					strcpy(linetok, linecp);
					char *tk_id    = strtok(linetok, FILE_DELIM);
					char *tk_nome  = strtok(NULL, FILE_DELIM);
					char *tk_preco = strtok(NULL, FILE_DELIM);
					char *tk_quant = strtok(NULL, FILE_DELIM);

					char cutnome[60];
					int  cutid = atoi(tk_id);
					strcpy(cutnome, tk_nome);
					float cutpreco = atof(tk_preco);
					int   cutqt    = atoi(tk_quant);

					fprintf(fw, "\n%d[#]%s[#]%.2f[#]%d", cutid, cutnome, newprice, cutqt);
				}
			}
		}

		fclose(fr);
		fclose(fw);

		remove(fp_stocks);
		rename(fp_temp, fp_stocks);

		if(did == 1){
			printErr("Item '%d' nao existe\n", id);
		}
		parseStock();
	}
}
