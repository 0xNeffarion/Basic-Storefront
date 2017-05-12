void startupActions();
void sair();
void actions(const int opt, const int log);
void getStats(const int log); //cria entrada no ficheiro stats para cada utilizador
int vstats(const int vsid); //verifica se já existe stats para o utilizador

void startupActions(){
	clearScreen();
	setlocale(LC_ALL, "en_US.UTF-8");
	char cvstats[512];
	getClientStatsFilePath(cvstats);
	char dr[512];
	getDataDirectory(dr);
	if(!dirExists(&dr[0])){
		if(!createDir(&dr[0])){
			printErr("Nao foi possivel criar diretorio de registo\n");
			exit(1);
			return;
		}
	}
	if(!fileExists(&cvstats[0])){
		if(!create(&cvstats[0])){
			printErr("Nao foi possivel criar ficheiro de estatisticas\n");
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
	        getStats(log);
		lista(log);
		break;
	}

	case 3: {
	        getStats(log);
		estatisticas(getUserId(log));
		break;
	}


	case 4: {
	        printSobre();
		break;
	}
	  
	case 5: {
		sair();
		return;

		break;
	}

	default: {
	        clearScreen();
		printErr("Opção inválida! Escolha entre a opção 1 a 5!\n");
		enterPrompt();
		break;
	}
	}
}

void getStats(const int log){
  int vsid=getUserId(log);
  int flag=0;
  flag=vstats(vsid);
  if (flag == -1) {
    for (int i=0; i<512; i++) {
      if(clientstats[i].userid <= 0) {
	createClientStats(vsid);
	break;
      }
    }
  }
}

int vstats(const int vsid) {
  for (int i=0;i<512;i++) {
    if(clientstats[i].userid == vsid) {
      return 1;
    }
  }
  return -1;
}
