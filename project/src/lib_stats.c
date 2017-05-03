typedef struct {
	int uid;
	int userid;
	int itemid;
	int quant;
} statsdb;

// FILE LAYOUT: ID[#]USERID[#]ITEMID[#]QUANT

statsdb stats[1024];
int     numStats = 0;

void resetStats();
void parseStats();
void writeStats();
int getStatPosition(const int id);

void resetStats(){
	memset(stats, 0, sizeof(stats));
}

void parseStats(){
}

void writeStats(){
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
