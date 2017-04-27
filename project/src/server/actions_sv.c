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
		break;
	}

	case 3: {
		break;
	}

	case 4: {
		break;
	}

	case 5: {
		break;
	}

	case 6: {
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
			if(inputstocks == 6){
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
