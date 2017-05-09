void actionsStocks(const int val);
void actions(const int val);
void actionsStats(const int val);
void startupActions();

int lock = 0;

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
			char *ca = "1[#]gestor[#]880e0d76[#]1[#]0.00[#]0[#]-1\n";  //pw: admin
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

void actionsStats(const int val){
	switch(val){
	case 1: {
		printToday();
		break;
	}

	case 2: {
		printWeek();
		break;
	}

	case 3: {
		printMonth();
		break;
	}

	case 4: {
		break;
	}

	case 5: {
		sair();
		break;
	}

	default: {
		if(lock == 0){
			printErr("Opção invalida! Escolha valores de 1 a 8\n\n");
			int n = 0;
			menuStats();
			lock = 1;
			if(scanf("%1d", &n) >= 1){
				lock = 0;
				actionsStats(n);
			}
		}
		break;
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
		if(lock == 0){
			printErr("Opção invalida! Escolha valores de 1 a 8\n\n");
			int n = 0;
			menuStocks();
			lock = 1;
			if(scanf("%1d", &n) >= 1){
				lock = 0;
				actionsStocks(n);
			}
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
			if(lock == 0){
				menuStocks();
				lock = 1;
				int inputstocks = 0;
				if(scanf("%1d", &inputstocks) >= 1){
					lock = 0;
					clearScreen();
					actionsStocks(inputstocks);
				}
				if(inputstocks == 7){
					clearScreen();
					break;
				}
			}
		} while(1);
		break;
	}

	case 3: {
		do {
			if(lock == 0){
				menuStats();
				lock = 1;
				int inputstats = 0;
				if(scanf("%1d", &inputstats) >= 1){
					lock = 0;
					clearScreen();
					actionsStats(inputstats);
				}
				if(inputstats == 4){
					clearScreen();
					break;
				}
			}
		} while(1);
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
