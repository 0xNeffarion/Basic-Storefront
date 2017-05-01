void saldo(const int log);
void actionsaldo(const int opt, const int log);

void saldo(const int log){
	int opt;

	clearScreen();
	ePrint(COLOR_YELLOW "** Saldo **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Consultar Saldo.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Adicionar Saldo.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-3): ");
	if(scanf("%d", &opt) > 0){
		actionsaldo(opt, log);
	}
}

void actionsaldo(const int opt, const int log){
	float add;

	switch(opt){
	case 1: {
		clearScreen();
		ePrint("O seu saldo atual é:");
		printf(" %.2f€\n", users[log].balance);
	        enterPrompt();
		saldo(log);
		break;
	}

	case 2: {
		clearScreen();
		ePrint("Insira a quantia a adicionar ao seu saldo (em euros): ");
		scanf("%f", &add);
		if(add > 0){
			users[log].balance += add;
			clearScreen();
			ePrint("Saldo adicionado com sucesso!\n");
		        enterPrompt();
		}
		else{
			clearScreen();
			printErr("Tem que adicionar um valor superior a 0 ao seu saldo!\n");
			enterPrompt();
			actionsaldo(2,log);
		}
		saldo(log);
		break;
	}

	case 3: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 3!\n");
		enterPrompt();
		saldo(log);
		break;
	}
	}
}

