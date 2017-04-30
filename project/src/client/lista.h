//Prototype para a lista de compras, falta guardar lista no ficheiro.

void lista(const int log);
void actionslista(const int opt, const int log);
void addprod(const int items, const int log);
void remprod(const int items, const int log);
void mod(const int log);
int existe(const int log, const int add);
int vp(const int add);
int vq(const int id, const int q);

void lista(const int log){
	int opt = 0;
	
	clearScreen();
	ePrint(COLOR_YELLOW "** Lista **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Lista de Compras.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Consultar Lista de Compras.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Adicionar produtos à Lista de Compras.\n");
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Alterar Lista de Compras.\n");
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
		  enterPrompt();
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
		        enterPrompt();
			lista(log);
		}
		else{
		  printf("Lista de Compras:\n\n");
		  printf("|-%-6s-|-%-10s-|\n", "------", "----------");
		  printf("| " COLOR_GREEN "%-6s" COLOR_RESET " | " COLOR_GREEN "%-10s " COLOR_RESET "|\n", "Código", "Quantidade");
		  printf("|-%-6s-|-%-10s-|\n", "------", "----------");

		  for(int i = 0; i < items; i++){
		    printf("| %-6d | %-10d |\n", users[log].buylist[i], users[log].quant[i]);
		  }
		  printf("|-%-6s-|-%-10s-|\n", "------", "----------");
		  printf("\n\n");
		  enterPrompt();
		  lista(log);
		}
		break;
	}

	case 3: {
		clearScreen();
		if (items==0) {
		  printErr("Não possui uma lista! Utilize a opção nº1 para criar uma!\n");
		  enterPrompt();
		  lista(log);
		}
		else {
		  addprod(items,log);
		}
		break;
	}

	case 4: {
	        clearScreen();
		int o=0;
		ePrint(COLOR_CYAN "1)" COLOR_RESET " Modificar quantidade de um produto.\n");
		ePrint(COLOR_CYAN "2)" COLOR_RESET " Remover produto.\n");
		ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu anterior.\n");
		scanf("%d",&o);
	        while (o!=1 && o!=2 && o!=3) {
		  printErr("Opção inválida! Escolha entre a opção 1 a 3!\n");
		  scanf("%d",&o);
		}
		if (o==1) {
		  mod(log);
		}
		else if(o==2) {
		  remprod(items, log);
		}
		else {
		  lista(log);
		}
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
  int add, q, e=0, fp=0, fq=0;
        int j = items;
	ePrint("Pressine '0' quando terminar de adicionar produtos à sua lista!\n");
        ePrint("Adicione o código do produto à sua lista: ");
        scanf("%d",&add);
	if (add < 0) {
	  clearScreen();
	  printErr("Tem que selecionar um código de produto maior do que 0!\n");
	  addprod(items,log);
	}
        while(add > 0) {
	  e=existe(log,add);
	  if (e>0) {
	    clearScreen();
	    printErr("O produto já se encontra na sua lista!\n");
	    ePrint("Para alterar a quantidade do mesmo, por favor selecione a opção nº4!\n");
	    enterPrompt();
	    break;
	  }
	  fp=vp(add);
	  if (fp > 0) {
	    users[log].buylist[j] = add;
	    printf("%d disponiveis.\n",stocks[fp].quantidade);
	    ePrint("Selecione a quantidade prentendida: ");
	    scanf("%d",&q);
	    while(q <= 0){
	      clearScreen();
	      printErr("Selecionou uma quantidade igual ou inferior a 0!\n");
	      ePrint("Selecione a quantidade prentendida: ");
	      scanf("%d",&q);
	    }
	    fq=vq(fp,q);
	    while(fq==-1){
	      clearScreen();
	      printErr("Selecionou uma quantidade superior ao stock existente!\n");
	      ePrint("Selecione a quantidade pretendida: ");
	      scanf("%d",&q);
	      fq=vq(fp,q);
	    }
	    if(fq==1){
	      users[log].quant[j]=q;
	      j++;
	      clearScreen();
	      ePrint("Produto adicionado com sucesso à sua lista!\n");
	      enterPrompt();
	    }
	  }
	  else {
	    clearScreen();
	    printErr("Produto não encontrado! Tente novamente!\n");
	    addprod(items,log);
	  }
	  clearScreen();
	  ePrint("Pressine '0' quando terminar de adicionar produtos à sua lista!\n");
	  ePrint("Adicione o código do produto à sua lista: ");
	  scanf("%d",&add);
	}
	lista(log);
}

void remprod(const int items, const int log){
      //protótipo remover produtos
      clearScreen();
      int rem, q, rf, flag=0;
      ePrint("Selecione o código do produto a remover da sua lista: ");
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
	    users[log].quant[i]=users[log].quant[i+1];
          }
          ePrint("Produto removido com sucesso!\n");
	  enterPrompt();
	  lista(log);
        }
      else if (flag == 0 && rem>0) {
	printErr("Produto não encontrado, tente novamente!\n");
	enterPrompt();
	remprod(items,log);
      }
      else {
	lista(log);
      }
}

void mod(const int log) {
  int m=0, e=0, nq=0, fq=0, fp=0;
  ePrint("Selecione o produto a modificar a quantidade: ");
  scanf("%d",&m);
  e=existe(log,m);
  while(e<0) {
    clearScreen();
    printErr("O produto não se encontra na sua lista! Tente novamente!\n");
    enterPrompt();
    clearScreen();
    ePrint("Selecione o produto a modificar a quantidade: ");
    scanf("%d",&m);
    e=existe(log,m);
  }
  if (e>=0){
    fp=vp(m);
    printf("%d disponiveis.\n",stocks[fp].quantidade);
    ePrint("Selecione a nova quantidade pretendida: ");
    scanf("%d",&nq);
    while(nq<=0) {
      clearScreen();
      printErr("Selecionou uma quantidade igual ou inferior a 0!\n");
      enterPrompt();
      clearScreen();
      printf("%d disponiveis.\n",stocks[fp].quantidade);
      ePrint("Selecione a quantidade prentendida: ");
      scanf("%d",&nq);
    }
    fq=vq(fp,nq);
    while(fq==-1){
      clearScreen();
      printErr("Selecionou uma quantidade superior ao stock existente!\n");
      enterPrompt();
      clearScreen();
      printf("%d disponiveis.\n",stocks[fp].quantidade);
      ePrint("Selecione a nova quantidade pretendida: ");
      scanf("%d",&nq);
      fq=vq(fp,nq);
    }
    if(fq==1){
      users[log].quant[e]=nq;
      clearScreen();
      ePrint("Quantidade modificada com sucesso!\n");
      enterPrompt();
    }
  }
  lista(log);
}

int existe(const int log, const int add){
  for(int i=0; i<128; i++) {
    if(users[log].buylist[i]==add) {
      return i;
    }
  }
  return -1;
}

int vp(const int add) {
  for (int i=0; i<512; i++) {
      if(stocks[i].uid==add)
	return i;
  }
  return -1;
}

int vq(const int id, const int q) {
  if(q<=stocks[id].quantidade){
    return 1;
  }
  return -1;
}
