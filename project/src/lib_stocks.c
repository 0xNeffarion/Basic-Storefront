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

void resetStruct();
void parseStock();
void writeStock();
void getNome(int id, char out[]);
float getPreco(int id);
int getItemPosition(int id);
int getLastStockId();
int createItem(char name[], int quant, float price);
int getQuant(int id);
bool deleteStockItem(int id);
bool changeItemPrice(int id, float newprice);
bool changeItemQuant(int id, int newquant);
bool changeItemName(int id, char newname[]);

void resetStruct(){
	memset(stocks, 0, sizeof(stocks));
}

void parseStock(){
	char fp[512];

	getStocksFilePath(fp);
	resetStruct();
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
			numItems = i + 1;

			i++;
			for(; i < 256; i++){
				stocks[i].valid = false;
			}
		}
		else{
			printErr("Impossivel ler ficheiro de stocks!\n");
		}
	}
	else{
		printErr("Ficheiro de stocks nao existe!\n");
	}
}

void writeStock(){
	char fp[512];
	char fp_temp[512];

	getStocksFilePath(fp);
	getStocksTempFilePath(fp_temp);
	FILE *fw = fopen(&fp_temp[0], "w");
	if(fw != NULL){
		int i = 0;
		for(i = 0; i < 512; i++){
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
	int  i   = 0;
	if(fr != NULL){
		while(fgets(line, sizeof(line), fr) != NULL){
			if(strcmp(line, "\n") == 0){
				continue;
			}
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

int getItemPosition(int id){
	int i = 0, size = numItems;

	for(i = 0; i < size; i++){
		if(stocks[i].valid == true){
			if(stocks[i].uid == id){
				return(i);
			}
		}
	}

	return(-1);
}

int getQuant(int id){
	const int mid = getItemPosition(id);

	if(mid < 0){
		return(-1);
	}

	if(stocks[mid].valid == false){
		return(-1);
	}

	return(stocks[mid].quantidade);
}

float getPreco(int id){
	const int mid = getItemPosition(id);

	if(mid < 0){
		return(-1);
	}

	if(stocks[mid].valid == false){
		return(-1);
	}

	return(stocks[mid].preco);
}

void getNome(int id, char out[]){
	const int mid = getItemPosition(id);

	if(mid < 0){
		return;
	}

	if(stocks[mid].valid == false){
		return;
	}

	strcpy(out, stocks[mid].nome);
}

bool deleteStockItem(int id){
	int size = numItems;
	int pos  = getItemPosition(id);

	stocks[pos].valid = false;
	writeStock();
	parseStock();

	if(size != numItems){
		return(true);
	}
	else{
		return(false);
	}
}

int createItem(char name[], int quant, float price){
	int size   = numItems;
	int next   = size + 1;
	int nextId = getLastStockId() + 1;

	stocks[next].valid      = true;
	stocks[next].quantidade = quant;
	stocks[next].preco      = price;
	stocks[next].uid        = nextId;
	strcpy(stocks[next].nome, name);
	writeStock();
	parseStock();

	if(getLastStockId() == nextId){
		return(nextId);
	}
	else{
		return(-1);
	}
}

bool changeItemPrice(int id, float newprice){
	const int size = numItems;
	const int pos  = getItemPosition(id);

	if(pos == -1 || id < 0 || size < 0){
		return(false);
	}

	if(stocks[pos].valid == true){
		stocks[pos].preco = newprice;
	}

	writeStock();
	parseStock();

	if(stocks[pos].preco == newprice){
		return(true);
	}
	else{
		return(false);
	}
}

bool changeItemQuant(int id, int newquant){
	const int size = numItems;
	const int pos  = getItemPosition(id);

	if(pos == -1 || id < 0 || size < 0){
		return(false);
	}

	if(stocks[pos].valid == true){
		stocks[pos].quantidade = newquant;
	}

	writeStock();
	parseStock();

	if(stocks[pos].quantidade == newquant){
		return(true);
	}
	else{
		return(false);
	}
}

bool changeItemName(int id, char newname[]){
	const int size = numItems;
	const int pos  = getItemPosition(id);

	if(pos == -1 || id < 0 || size < 0){
		return(false);
	}

	if(stocks[pos].valid == true){
		strcpy(stocks[pos].nome, newname);
	}

	writeStock();
	parseStock();

	if(strcmp(stocks[pos].nome, newname) == 0){
		return(true);
	}
	else{
		return(false);
	}
}
