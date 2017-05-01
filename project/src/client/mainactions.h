void startupActions();
void sair();
void actions(const int opt, const int log);

void startupActions(){
	clearScreen();
	setlocale(LC_ALL, "en_US.UTF-8");
	char fp[512];
	getUsersFilePath(fp);
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
			printErr("Nao foi possivel criar ficheiro de registo\n");
			exit(1);
			return;
		}
	}
}

void sair(){
	clearScreen();
	ePrint("Saindo... Volte sempre!\n");
	usleep(1000 * 1500); //1,5s
	exit(0);
}

void actions(const int opt, const int log){
	switch(opt){
	case 1: {
		saldo(log);
		break;
	}

	case 2: {
		lista(log);
		break;
	}

	case 3: {
		estatisticas();
		break;
	}

	case 4: {
		sair();
		return;

		break;
	}

	default: {
	        clearScreen();
		printErr("Opção inválida! Escolha entre a opção 1 a 4!\n");
		enterPrompt();
		break;
	}
	}
}
