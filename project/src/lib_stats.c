typedef struct {
	int   uid;
	int   userid;
	int   itemid;
	int   quant;
	float preco;
	bool  valid;
	char  date[100];
} statsdb;

// FILE LAYOUT: ID[#]USERID[#]ITEMID[#]QUANT[#]PRECO[#]DATE

statsdb stats[1024];
int     numStats = 0;

void resetStats();
void parseStats();
void writeStats();
int getStatPosition(const int id);
int getLastStatId();

void resetStats(){
	memset(stats, 0, 1024);
}

void parseStats(){
	char fp[512];

	getStatsFilePath(fp);
	resetStats();
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
					char *tk_id     = strtok(line, FILE_DELIM);
					char *tk_userid = strtok(NULL, FILE_DELIM);
					char *tk_itemid = strtok(NULL, FILE_DELIM);
					char *tk_quant  = strtok(NULL, FILE_DELIM);
					char *tk_preco  = strtok(NULL, FILE_DELIM);
					char *tk_date   = strtok(NULL, FILE_DELIM);
					strcpy(stats[i].date, tk_date);
					stats[i].uid    = atoi(tk_id);
					stats[i].userid = atoi(tk_userid);
					stats[i].itemid = atoi(tk_itemid);
					stats[i].quant  = atoi(tk_quant);
					stats[i].preco  = atof(tk_preco);
					stats[i].valid  = true;
					i++;
				}
			}
			fclose(f);
			numStats = i + 1;

			i++;
			for(; i < 1024; i++){
				stats[i].valid = false;
			}
		}
		else{
			printErr("Impossivel ler ficheiro de stats!\n");
		}
	}
	else{
		printErr("Ficheiro de stats nao existe!\n");
	}
}

void writeStats(){
	char fp[512];
	char fp_temp[512];

	getStatsFilePath(fp);
	getStatsTempFilePath(fp_temp);
	FILE *fw = fopen(&fp_temp[0], "w");
	if(fw != NULL){
		int i = 0;
		for(i = 0; i < 1024; i++){
			if(stats[i].valid == true){
				fprintf(fw, "%d[#]%d[#]%d[#]%d[#]%.2f[#]%s\n", stats[i].uid, stats[i].userid, stats[i].itemid, stats[i].quant, stats[i].preco, stats[i].date);
			}
		}

		fclose(fw);
		remove(fp);
		rename(fp_temp, fp);
	}
}

int getStatPosition(const int id){
	int i = 0;

	for(; i < numStats; i++){
		if(stats[i].uid == id){
			return(i);
		}
	}

	return(-1);
}

int getLastStatId(){
	char fp[512];
	char line[256];

	getStatsFilePath(fp);
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

void registarStat(int userid, int itemid, int quantia){
	int next      = numStats;
	int nextId    = getLastStatId() + 1;
	int itemprice = stocks[getItemPosition(itemid)].preco;

	stats[next].uid    = nextId;
	stats[next].userid = userid;
	stats[next].itemid = itemid;
	stats[next].quant  = quantia;
	stats[next].preco  = itemprice;
	char today[100];
	getDate(today);
	strcpy(stats[next].date, today);
	stats[next].valid = true;
	numStats++;
	writeStats();
	parseStats();
}
