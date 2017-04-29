void estatisticas();
void actionsestatisticas(const int opt);

void estatisticas(){
	int opt = 0;

	clearScreen();
	ePrint(COLOR_YELLOW "** Estatísticas **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Quantidade total de produtos comprados.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Quantidade comprada de um determinado produto.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Valor total gasto num determinado produto.\n");
	//adicionar mais estatisticas?
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-4):\n");
	if(scanf("%d", &opt) > 0){
		actionsestatisticas(opt);
	}
}

void actionsestatisticas(const int opt){
	switch(opt){
	case 1: {
		//Falta criar um contador associado ao user
		clearScreen();
		ePrint("Comprou (teste) produtos.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 2: {
		int prod;
		clearScreen();
		ePrint("Insira o código do produto!\n");
		scanf("%d", &prod);
		//aceder a um contador?
		ePrint("Comprou (teste) quantidade do produto.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 3: {
		int prod;
		clearScreen();
		ePrint("Insira o código do produto!\n");
		scanf("%d", &prod);
		//contador*preço
		ePrint("Gastou (teste) euros no produto.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 4: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 4!\n");
		int opt = 0;
		if(scanf("%d", &opt) > 0){
			actionsestatisticas(opt);
		}
		break;
	}
	}
}
