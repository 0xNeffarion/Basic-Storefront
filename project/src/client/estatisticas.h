void estatisticas(const int id);
void actionsestatisticas(const int opt, const int id);
int getIdStats(const int id);
int getItemPos(const int sid, const int prod);

void estatisticas(const int id){
	int opt = 0;

	clearScreen();
	ePrint(COLOR_YELLOW "** Estatísticas **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Quantidade total de produtos comprados.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Quantidade comprada de um determinado produto.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Valor total gasto num determinado produto.\n");
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Valor total gasto.\n");
	ePrint(COLOR_CYAN "5)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-5): ");
	scanf("%d", &opt);
	actionsestatisticas(opt,id);
}

void actionsestatisticas(const int opt, const int id){
        int sid = getIdStats(id);

        switch(opt){
	case 1: {
		clearScreen();
		if (clientstats[sid].totalp>0) {
		  printf("Comprou %d produtos.\n",clientstats[sid].totalp);
		}
		else
		  printErr("Não comprou produtos na nossa loja!\n");
		enterPrompt();
		estatisticas(id);
		break;
	}

	case 2: {
	        int prod=0, pos=-1;
		clearScreen();
		ePrint("Insira o código do produto: ");
		scanf("%d", &prod);
	        pos=getItemPos(sid,prod);
		clearScreen();
		if (pos >= 0) {
		  printf("Comprou %d vezes o produto %d.\n",clientstats[sid].quant[pos],prod);
		}
		else
		  printErr("Nunca comprou este produto!\n");
		enterPrompt();
		estatisticas(id);
		break;
	}

	case 3: {
	        int prod=0, pos=-1;
		clearScreen();
		ePrint("Insira o código do produto: ");
		scanf("%d", &prod);
		pos=getItemPos(sid,prod);
		clearScreen();
		if (pos >= 0) {
		  printf("Gastou %.2f€ no produto %d.\n",clientstats[sid].gasto[pos],prod);
		}
		else
		  printErr("Nunca comprou este produto!\n");
	        enterPrompt();
		estatisticas(id);
		break;
	}

	case 4: {
	        clearScreen();
		if(clientstats[sid].total > 0) {
		  printf("Total gasto: %.2f€\n",clientstats[sid].total);
		}
		else
		  printf("Ainda não gastou dinheiro na nossa loja!\n");
		enterPrompt();
		estatisticas(id);
	        break;
	}

	case 5: {
		break;
	}

	default: {
	        clearScreen();
		printErr("Opção inválida! Escolha entre a opção 1 a 5!\n");
		enterPrompt();
	        estatisticas(id);
		break;
	}
	}
}

int getIdStats(const int id) {
  for (int i=0; i<512; i++) {
    if (clientstats[i].userid == id) {
      return i;
    }
  }
  return 0;
}

int getItemPos(const int sid, const int prod) {
  for(int i=0; i<128; i++) {
    if(clientstats[sid].itemid[i] == prod) {
      return i;
    }
  }
  return -1;
}
