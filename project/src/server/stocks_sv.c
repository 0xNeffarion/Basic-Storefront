void listarStock();

void listarStock(){
	parseStock();
	int i = 0;
	if(numItems <= 0){
		printf("Nao existem items em stock!\n");
		return;
	}

	for(i = 0; i < numItems; i++){
		if(stocks[i].valid == true){
			printf("[%d] - %s - %d - %.2f€", stocks[i].uid, stocks[i].nome, stocks[i].quantidade, stocks[i].preco);
		}
	}

	printf("\n\n");
}
