typedef struct {
	int   uid;
	int   userid;
        int   itemid[128]; //Código do produto
        int   quant[128]; //Quantidade comprada de um determinado produto
        float gasto[128]; // Quantidade total gasta num determinado produto
        float total; //Valor total gasto
        int   totalp; //Quantidade total de produtos comprados
	bool  valid;
} statscv;

// FILE LAYOUT: ID[#]USERID[#]QUANT[#]GASTO[#]TOTAL[#]TOTALP

statscv clientstats[512];
int     numClientStats = 0;

void resetClientStats();
void parseClientStats();
void writeClientStats();
int getClientStatPosition(const int id);
int getClientLastStatId();

void resetClientStats(){
	memset(stats, 0, 512);
}

void parseClientStats(){
	char fp[512];

	getClientStatsFilePath(fp);
	resetClientStats();
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
                                        char *tk_id            = strtok(line, FILE_DELIM);
					char *tk_uid           = strtok(NULL, FILE_DELIM);
					char *tk_iid           = strtok(NULL, FILE_DELIM);
					char *tk_qt            = strtok(NULL, FILE_DELIM);
					char *tk_gs            = strtok(NULL, FILE_DELIM);
					char *tk_tb            = strtok(NULL, FILE_DELIM);
					char *tk_tp            = strtok(NULL, FILE_DELIM);
					clientstats[i].uid     = atoi(tk_id);
					clientstats[i].userid  = atoi(tk_uid);
					clientstats[i].total   = atof(tk_tb);
					clientstats[i].totalp  = atoi(tk_tp);
				        clientstats[i].valid   = true;

					int  z     = 1;
					char *tks1 = strtok(tk_iid, BUYLIST_DELIM);
					if(strcmp(tks1, "0") == 0){
						i++;
						continue;
					}
					else{
						clientstats[i].itemid[0] = strtol(tks1, NULL, 0);
					}

					while(tks1 != NULL || strlen(tks1) >= 1){
						tks1 = strtok(NULL, BUYLIST_DELIM);
						if(tks1 != NULL){
							int val = strtol(tks1, NULL, 0);
							clientstats[i].itemid[z] = val;
							z++;
						}
						else{
							break;
						}
					}
					
					char *tks2 = strtok(tk_qt, BUYLIST_DELIM);
					if(strcmp(tks2, "0") == 0){
						i++;
						continue;
					}
					else{
						clientstats[i].quant[0] = strtol(tks2, NULL, 0);
					}

					while(tks2 != NULL || strlen(tks2) >= 1){
						tks2 = strtok(NULL, BUYLIST_DELIM);
						if(tks2 != NULL){
							int val = strtol(tks2, NULL, 0);
							clientstats[i].quant[z] = val;
							z++;
						}
						else{
							break;
						}
					}

					z = 1;
					char *tks3 = strtok(tk_gs, BUYLIST_DELIM);
					if(strcmp(tks3, "0") == 0){
						i++;
						continue;
					}
					else{
						clientstats[i].gasto[0] = strtol(tks3, NULL, 0);
					}

					while(tks3 != NULL || strlen(tks3) >= 1){
						tks3 = strtok(NULL, BUYLIST_DELIM);
						if(tks3 != NULL){
							float val = strtol(tks3, NULL, 0);
							clientstats[i].gasto[z] = val;
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
			numClientStats = i + 1;

			i++;
			for(; i < 512; i++){
				stats[i].valid = false;
			}
		}
		else{
			printErr("Impossivel ler ficheiro de clientstats!\n");
		}
	}
	else{
		printErr("Ficheiro de clientstats nao existe!\n");
	}
}

void writeClientStats(){
        char fp[512];
	char fp_temp[512];

	getClientStatsFilePath(fp);
	getClientStatsTempFilePath(fp_temp);
	FILE *fw = fopen(&fp_temp[0], "w");
	if(fw != NULL){
		int i = 0;
		for(i = 0; i < 512; i++){
			if(stats[i].valid == true){
				char iid[512];
				char qt[512];
				char gs[512];
				int  k     = 0;
				for(k = 0; k < 127; k++){
					if(k > 0){
						if(clientstats[i].itemid[k] > 0){
							sprintf(iid, "%s;%d", iid, clientstats[i].itemid[k]);
						}
					}
					else if(k == 0){
						sprintf(iid, "%d", clientstats[i].itemid[k]);
					}
				}
				for(k = 0; k < 127; k++){
					if(k > 0){
						if(clientstats[i].quant[k] > 0){
							sprintf(qt, "%s;%d", qt, clientstats[i].quant[k]);
						}
					}
					else if(k == 0){
						sprintf(qt, "%d", clientstats[i].quant[k]);
					}
				}
				for(k = 0; k < 127; k++){
				        if(k > 0){
				                if(clientstats[i].gasto[k] > 0){
				                        sprintf(gs, "%s;.2%f", gs, clientstats[i].gasto[k]);
				                }
				        }
				        else if(k == 0){
				                sprintf(gs, "%.2f", clientstats[i].gasto[k]);
				        }
				}
				fprintf(fw, "%d[#]%d[#]%s[#]%s[#]%s[#]%.2f[#]%d\n", clientstats[i].uid, clientstats[i].userid,
					iid, qt, gs, clientstats[i].total, clientstats[i].totalp);
			}
		}
		fclose(fw);
		remove(fp);
		rename(fp_temp, fp);
	}
}

int getClientStatPosition(const int id){
	int i = 0;

	for(; i < numStats; i++){
		if(clientstats[i].uid == id){
			return(i);
		}
	}

	return(-1);
}

int getClientLastStatId(){
	char fp[512];
	char line[256];

	getClientStatsFilePath(fp);
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
