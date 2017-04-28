void listarStock();
void editarPreco();
void editarQuantidade();
void editarNome();
void eliminarItem();
void criarItem();

void editarNome(){
	if(getLastStockId() < 0){
		printf("Nao existem items em stock!\n\n");
		return;
	}
	int  id = -1;
	char novonome[60];

	clearScreen();
	printf("Insira o id do item a editar (-1 para voltar para o menu):\n");
	if(scanf(" %d", &id) < 0){
		printErr("Nao foi possivel ler id!\n");
		return;
	}

	if(id < -1){
		printErr("id nao pode ser negativo\n");
		return;
	}

	if(id == -1){
		clearScreen();
		return;
	}

	clearScreen();
	printf("Insira o novo nome:\n");
	if(scanf("%s", &novonome[0]) < 0){
		printErr("Nao foi possivel ler nome!\n");
		return;
	}

	if(strlen(novonome) < 3){
		printErr("nome e muito pequeno\n");
		return;
	}

	clearScreen();
	bool res = changeItemName(id, novonome);
	if(res){
		printf("Item %d editado com sucesso\n", id);
		printf("\n");
		enterPrompt();
		clearScreen();
	}
	else{
		printErr("Nao existe item com o id %d!\n", id);
		printf("\n");
		enterPrompt();
		editarPreco();
	}
}

void editarPreco(){
	if(getLastStockId() < 0){
		printf("Nao existem items em stock!\n\n");
		return;
	}
	int   id    = -1;
	float price = 0.00;

	clearScreen();
	printf("Insira o id do item a editar (-1 para voltar para o menu):\n");
	if(scanf(" %d", &id) < 0){
		printErr("Nao foi possivel ler id!\n");
		return;
	}

	if(id < -1){
		printErr("id nao pode ser negativo\n");
		return;
	}

	if(id == -1){
		clearScreen();
		return;
	}

	clearScreen();
	printf("Insira o novo preco:\n");
	if(scanf(" %f", &price) < 0){
		printErr("Nao foi possivel ler preco!\n");
		return;
	}

	if(price <= 0){
		printErr("preco nao pode ser negativo ou zero\n");
		return;
	}

	clearScreen();
	bool res = changeItemPrice(id, price);
	if(res){
		printf("Item %d editado com sucesso\n", id);
		printf("\n");
		enterPrompt();
		clearScreen();
	}
	else{
		printErr("Nao existe item com o id %d!\n", id);
		printf("\n");
		enterPrompt();
		editarPreco();
	}
}

void editarQuantidade(){
	if(getLastStockId() < 0){
		printf("Nao existem items em stock!\n\n");
		return;
	}
	int id    = -1;
	int quant = 0;

	clearScreen();
	printf("Insira o id do item a editar (-1 para voltar para o menu):\n");
	if(scanf(" %d", &id) < 0){
		printErr("Nao foi possivel ler id!\n");
		return;
	}

	if(id < -1){
		printErr("id nao pode ser negativo\n");
		return;
	}

	if(id == -1){
		clearScreen();
		return;
	}

	clearScreen();
	printf("Insira a nova quantia:\n");
	if(scanf(" %d", &quant) < 0){
		printErr("Nao foi possivel ler quantia!\n");
		return;
	}

	if(quant <= 0){
		printErr("quantia nao pode ser negativa\n");
		return;
	}

	clearScreen();
	bool res = changeItemQuant(id, quant);
	if(res){
		printf("Item %d editado com sucesso\n", id);
		printf("\n");
		enterPrompt();
		clearScreen();
	}
	else{
		printErr("Nao existe item com o id %d!\n", id);
		printf("\n");
		enterPrompt();
		editarQuantidade();
	}
}

void eliminarItem(){
	if(getLastStockId() < 0){
		printf("Nao existem items em stock!\n\n");
		return;
	}
	int id = -1;

	clearScreen();
	printf("Insira o id do item a eliminar (-1 para voltar para o menu):\n");
	if(scanf(" %d", &id) < 0){
		printErr("Nao foi possivel ler id!\n");
		return;
	}

	if(id < -1){
		printErr("id nao pode ser negativo\n");
		return;
	}

	if(id == -1){
		clearScreen();
		return;
	}

	clearScreen();
	bool res = deleteStockItem(id);
	if(res){
		printf("Item %d eliminado com sucesso\n", id);
		printf("\n");
		enterPrompt();
		clearScreen();
	}
	else{
		printErr("Nao existe item com o id %d!\n", id);
		printf("\n");
		enterPrompt();
		eliminarItem();
	}
}

void listarStock(){
	parseStock();
	int i = 0;
	if(getLastStockId() < 0){
		printf("Nao existem items em stock!\n\n");
		return;
	}
	printf("Tabela do stock:\n\n");
	printf("|-%-4s-|-%-30s-|-%-13s-|-%-8s-|\n", "----", "------------------------------", "-------------", "--------");
	printf("| " COLOR_YELLOW "%-4s" COLOR_RESET " | " COLOR_YELLOW "%-30s " COLOR_RESET "| " COLOR_YELLOW "%-13s " COLOR_RESET "| " COLOR_YELLOW "%-8s" COLOR_RESET " |\n", "ID", "NOME", "QUANTIDADE", "PRECO");
	printf("|-%-4s-|-%-30s-|-%-13s-|-%-8s-|\n", "----", "------------------------------", "-------------", "--------");

	for(i = 0; i < numItems; i++){
		if(stocks[i].valid == true){
			printf("| %-4d | %-30s | %-13d | %-7.2f€ |\n", stocks[i].uid, stocks[i].nome, stocks[i].quantidade, stocks[i].preco);
		}
	}
	printf("|-%-4s-|-%-30s-|-%-13s-|-%-8s-|\n", "----", "------------------------------", "-------------", "--------");
	printf("\n\n");
	enterPrompt();
	clearScreen();
}

void criarItem(){
	clearScreen();
	char  nome[60];
	float preco = 0.00;
	int   quant = 0;
	printf("Insira o nome do item [Max. 60 caracteres]: \n");
	if(scanf("%s", &nome[0]) <= 0){
		printErr("Erro a inserir item!\n\n");
		return;
	}
	if(strlen(nome) > 59 || strlen(nome) < 3){
		printErr("Erro a inserir item! (tamanho do nome)\n\n");
		return;
	}
	clearScreen();
	printf("Insira o preco [Ex: 7.50]:\n");
	if(scanf("%f", &preco) <= 0){
		printErr("Erro a inserir item!\n\n");
		return;
	}
	if(preco <= 0){
		printErr("Erro a inserir item! (preco)\n\n");
		return;
	}
	clearScreen();
	printf("Insira a quantidade em stock:\n");
	if(scanf("%d", &quant) <= 0){
		printErr("Erro a inserir item!\n\n");
		return;
	}
	if(quant <= 0){
		printErr("Erro a inserir item! (quantidade)\n\n");
		return;
	}
	clearScreen();
	int suc = createItem(nome, quant, preco);
	if(suc == -1){
		printErr("Erro a criar item!\n\n");
	}
	else{
		printf("Item [%s] registado em stock com sucesso! Id: %d\n\n", nome, suc);
	}
}
