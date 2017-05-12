void printAll();
void printProduto();
void printLucro();
void printCliente();

void printAll(){
	clearScreen();
	parseClientStats();
	int i   = 0;
	int sum = 0;
	for(i = 0; i < numClientStats; i++){
		if(clientstats[i].valid == true){
			int z = 0;
			for(z = 0; z < 128; z++){
				if(clientstats[i].quant[z] > 0){
					sum = sum + clientstats[i].quant[z];
				}
			}
		}
	}
	printf("Total de produtos vendidos: %d\n", sum);
}

void printProduto(){
	clearScreen();
	parseClientStats();
	int item = 0;
	printf("Insira o id do item que quer ver a quantidade vendida:\n");
	if(scanf("%d", &item) <= 0){
		printErr("Erro a ler valor\n");
		return;
	}
	clearScreen();
	int i   = 0;
	int sum = 0;

	for(i = 0; i < numClientStats; i++){
		if(clientstats[i].valid == true){
			int z = 0;
			for(z = 0; z < 128; z++){
				if(clientstats[i].itemid[z] == item){
					sum += clientstats[i].quant[z];
				}
			}
		}
	}
	printf("Total vendido do item [%d]: %d\n", item, sum);
}

void printLucro(){
	clearScreen();
	parseClientStats();
	int item = 0;
	printf("Insira o id do item que quer ver o lucro:\n");
	if(scanf("%d", &item) <= 0){
		printErr("Erro a ler valor\n");
		return;
	}
	clearScreen();
	int   i   = 0;
	float sum = 0;

	for(i = 0; i < numClientStats; i++){
		if(clientstats[i].valid == true){
			int z = 0;
			for(z = 0; z < 128; z++){
				if(clientstats[i].itemid[z] == item){
					sum += clientstats[i].gasto[z];
				}
			}
		}
	}
	printf("Total lucro do item [%d]: %.2f\n", item, sum);
}

void printCliente(){
	clearScreen();
	parseClientStats();
	int id = 0;
	printf("Insira o id do cliente:\n");
	if(scanf("%d", &id) <= 0){
		printErr("Erro a ler valor\n");
		return;
	}
	clearScreen();
	int pos = getClientStatUserPosition(id);
	if(clientstats[pos].valid == true){
		printf("Total produtos comprados: %d\n", clientstats[pos].totalp);
		printf("Total dinheiro gasto: %.2f\n", clientstats[pos].total);
		int i = 0;
		printf("Items comprados: \n");
		for(i = 0; i < 128; i++){
			if(clientstats[pos].itemid[i] > 0){
				char n[100] = "";
				getItemById(clientstats[pos].itemid[i], n);
				printf("%s - comprado %d vezes\n", n, clientstats[pos].quant[i]);
			}
		}
		enterPrompt();
		clearScreen();
	}
}
