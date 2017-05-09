void startupActions();
void sair();
void actions(const int opt, const int log);
void getStats(const int log);

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

void getStats(const int log){
  int id=getUserId(log);
  bool val;
  for (int i=0; i<512; i++) {
    if(clientstats[i].userid == id) {
      val==true;
      break;
    }
    else {
      val==false;
    }
  }
  if (val==false) {
    for (int i=0; i<512; i++) {
      if(clientstats[i].userid <= 0) {
	clientstats[i].userid=id;
	break;
      }
    }
  }
}
