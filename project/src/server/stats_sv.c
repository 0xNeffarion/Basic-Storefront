void printToday();
void printWeek();
void printMonth();
void choosePrint();

void printWeek(){
}

void printMonth(){
}

void printToday(){
	parseStats();
	if(getLastStatId() < 0){
		printf("Nao existem estatisticas!\n\n");
		return;
	}
	statsdb tdstats[512];
	int     i   = 0;
	int     z   = 0;
	int     num = 0;
	for(i = 0; i < numStats; i++){
		if(stats[i].valid == true){
			if(isDateToday(stats[i].date)){
				tdstats[z] = stats[i];
				z++;
				num++;
			}
		}
	}


	printf("Compras feitas hoje:\n\n");
	printf("|-%-4s-|-%-25s-|-%-25s-|-%-5s-|-%-8s-|\n", "----", "-------------------------", "-------------------------", "-----", "--------");
	printf("| " COLOR_YELLOW "%-4s" COLOR_RESET " | " COLOR_YELLOW "%-25s " COLOR_RESET "| " COLOR_YELLOW "%-25s " COLOR_RESET "| " COLOR_YELLOW "%-5s" COLOR_RESET "| " COLOR_YELLOW "%-8s" COLOR_RESET " |\n", "ID", "USERNAME", "ITEM", "QUANTIDADE", "QUANTIA RECEBIDA (€)");
	printf("|-%-4s-|-%-25s-|-%-25s-|-%-8s-|\n", "----", "------------------------------", "-------------------------", "--------");
	for(i = 0; i < num; i++){
		int  id = tdstats[i].uid;
		char user[30];
		getUsernameById(tdstats[i].userid, user);
		char item[64];
		getItemById(tdstats[i].itemid, item);
		int qt       = tdstats[i].quant;
		int dinheiro = (tdstats[i].preco) * qt;

		if(tdstats[i].valid == true){
			printf("| %-4d | %-25s | %-25s | %-5d | %-7.2f€ |\n",
				   id,
				   user,
				   item,
				   qt,
				   dinheiro
				   );
		}
	}
	printf("|-%-4s-|-%-25s-|-%-25s-|-%-5s-|-%-8s-|\n", "----", "-------------------------", "-------------------------", "-----", "--------");
	printf("\n\n");
	enterPrompt();
	clearScreen();
}
