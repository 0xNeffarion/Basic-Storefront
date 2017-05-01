void actionsStocks(const int val);
void actions(const int val);
void startupActions();

void startupActions(){
	clearScreen();
	setlocale(LC_ALL, "en_US.UTF-8");
	char fp[512];
	getUsersFilePath(fp);
	char st[512];
	getStocksFilePath(st);
	char dr[512];
	getDataDirectory(dr);
	if(!dirExists(&dr[0])){
		if(!createDir(&dr[0])){
			printErr("Nao foi possivel criar diretorio de registo\n");
			exit(1);
			return;
		}
	}
	if(!fileExists(&fp[0])){
		if(!create(&fp[0])){
			printErr("Nao foi possivel criar ficheiro de registo (users)\n");
			exit(1);
			return;
		}
		else{
			char *ca = "1[#]gestor[#]admin[#]1[#]0.00[#]0[#]-1\n";
			if(append(&fp[0], ca)){
				printf("Nao foi encontrado utilizadores! Utilizador gestor criado!\n");
			}
			else{
				exit(1);
			}
		}
	}
	if(!fileExists(&st[0])){
		if(!create(&st[0])){
			printErr("Nao foi possivel criar ficheiro de registo (stocks)\n");
			exit(1);
			return;
		}
	}
}

void actionsStocks(const int val){
	switch(val){
	case 1: {
		listarStock();
		break;
	}

	case 2: {
		criarItem();
		break;
	}

	case 3: {
		editarPreco();
		break;
	}

	case 4: {
		editarQuantidade();
		break;
	}

	case 5: {
		editarNome();
		break;
	}

	case 6: {
		eliminarItem();
		break;
	}

	case 7: {
		break;
	}

	case 8: {
		sair();
		return;

		break;
	}

	default: {
		printErr("Opção invalida! Escolha valores de 1 a 8\n\n");
		int n = 0;
		menuStocks();
		if(scanf("%d", &n) >= 1){
			actionsStocks(n);
		}
		break;
	}
	}
}

void actions(const int val){
	switch(val){
	case 1: {
		novoUser();
		break;
	}

	case 2: {
		do {
			menuStocks();
			int inputstocks = 0;
			if(scanf("%d", &inputstocks) >= 1){
				clearScreen();
				actionsStocks(inputstocks);
			}
			if(inputstocks == 7){
				clearScreen();
				break;
			}
		} while(1);
		break;
	}

	case 3: {
		break;
	}

	case 4: {
		listarUsers();
		break;
	}

	case 5: {
		sair();
		return;

		break;
	}

	default: {
		printErr("Opção invalida! Escolha valores de 1 a 5\n\n");
		int n = 0;
		menu();
		if(scanf("%d", &n) >= 1){
			actions(n);
		}
		break;
	}
	}
}
