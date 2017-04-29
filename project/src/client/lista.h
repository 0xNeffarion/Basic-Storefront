//Prototype para a lista de compras, falta verificar se o produto encontra-se em stock e implementar a quantidade na lista.

void lista(const int log);
void actionslista(const int opt, const int log);
void addprod(const int items, const int log);
void remprod(const int items, const int log);

void lista(const int log){
	int opt = 0;
	
	clearScreen();
	ePrint(COLOR_YELLOW "** Lista **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Lista de Compras.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Consultar Lista de Compras.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Adicionar produtos à Lista de Compras.\n");
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Remover produtos da Lista de Compras.\n");
	ePrint(COLOR_CYAN "5)" COLOR_RESET " Comprar produtos da lista.\n");
	ePrint(COLOR_CYAN "6)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-6):\n");
	if(scanf("%d", &opt) > 0){
		actionslista(opt, log);
	}
}

void actionslista(const int opt, const int log){
       int items = 0;	
                for(int i = 0; i < 128; i++){
		  if(users[log].buylist[i]>0) {
		    items++;
		  }
		}
		
        switch(opt){

	case 1: {
		clearScreen();
		if (items > 0) {
		  printErr("Já possui uma lista! Por favor selecione a opção nº3!\n");
		  usleep(1000*2000);
		  lista(log);
		}
		else 
		  addprod(items,log);
		break;
	}

	case 2: {
		clearScreen();
		if(items == 0){
		        printErr("Não tem produtos na sua lista!\n");
			usleep(1000*1500);
		}
		else{
			ePrint("A sua lista é composta pelos seguintes produtos:\n");
			for(int i = 0; i < items; i++){
			  printf("%d\n", users[log].buylist[i]);
			  usleep(1000 * 2000);
			}
		}
		usleep(1000 * 2000);
		lista(log);
		break;
	}

	case 3: {
		clearScreen();
		if (items==0) {
		  printErr("Não possui uma lista! Use a opção nº1 para criar uma!\n");
		  usleep(1000*2500);
		  lista(log);
		}
		else {
		  addprod(items,log);
		}
		break;
	}

	case 4: {
	        clearScreen();
                remprod(items, log);
		break;
	}
		  
	case 5: {
		clearScreen();
		//falta completar
		ePrint("Total a pagar: (teste) \n"); //fazer soma do valor de todos os produtos da lista
		ePrint("Acabou de comprar os produtos que estão na sua lista!\n");
		usleep(1000 * 2000);
		lista(log);
		break;
	}

	case 6: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 6!\n");
		int opt = 0;
		if(scanf("%d", &opt) > 0){
			actionslista(opt, log);
		}
		break;
	}
	}
}

void addprod(const int items, const int log){
        int add;
        int j = items;
        ePrint("Adicione os códigos dos produtos à sua lista:\n");
        ePrint("Pressine 0 quando terminar de adicionar produtos à sua lista!\n");
        scanf("%d",&add);
        while(add > 0) {
          users[log].buylist[j] = add;
          j++;
          scanf("%d",&add);
        }
        lista(log);
}

void remprod(const int items, const int log){
      //protótipo para remover produtos
      clearScreen();
      int rem, rf, flag=0;
      ePrint("Selecione o código do produto a remover da sua lista:\n");
      scanf("%d",&rem);
      if (rem > 0) {
          for (int i = 0; i < items; i++) {
            if (users[log].buylist[i] == rem) {
	      rf=i;
	      flag=1;
            }
          }
          for (int i = rf; users[log].buylist[i]>0; i++) {
            users[log].buylist[i]=users[log].buylist[i+1];
          }
          ePrint("Produto removido com sucesso!\n");
          usleep(1000*1500);
        }
        if (flag == 0 && rem>0) {
          printErr("Produto não encontrado, tente novamente!\n");
          remprod(items,log);
        }
        else
          lista(log);
}
