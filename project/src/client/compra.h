int compra(const int log, const int items);

int compra(const int log, const int items){
  float total=0;
  char decision[2];
  clearScreen();
  if (items==0) {
    printErr("Não possui uma lista, por favor crie uma!\n");
    enterPrompt();
    return 0;
  }
  for(int i=0;i < items;i++) {
    int q=users[log].quantidade[i];
    int cod=users[log].buylist[i];
    total+=q*getPreco(cod);
  }
  ePrint(COLOR_YELLOW "** Comprar produtos da sua Lista de Compras **" COLOR_RESET "\n");
  printf("Total: %.2f€\n",total);
  ePrint("Prosseguir com a compra? (sim/nao)\n");
  scanf("%s", decision);
  if (strcmp(decision,"nao") == 0) {
    return 0;
  }
  else if(strcmp(decision,"sim")==0 && items>0){
    parseStock();
    if (users[log].balance < total) {
      clearScreen();
      printErr("O seu saldo é inferior ao preço total da sua compra, por favor altere o seu saldo ou remova produtos da sua lista!\n");
      enterPrompt();
      return 0;
    }
    else {
      for(int i=0;i<items;i++) {
	printf("Ciclo: %d\nItems: %d\n",i,items);
	int cod=users[log].buylist[i];
	int id=-1;
	for(int j=0;j<512;j++) {
	  if(stocks[j].uid==cod) {
	    id=j;
	  }
	}
	if (id==-1) {
	    clearScreen();
	    printErr("Houve um erro a processar a sua compra! Por favor verifique a sua lista!\n");
	    enterPrompt();
	    return 0;
	}
	if (stocks[id].quantidade-users[log].quantidade[i]<0) {
	  clearScreen();
	  printErr("Houve um erro a processar a compra do produto "); printf("%d!\n",cod);
	  ePrint("Por favor altere a quantidade do mesmo!\n");
	  enterPrompt();
	  return 0;
	}
	else {
	  users[log].balance -= total;
	  users[log].buylist[i]=0;
	  stocks[id].quantidade -= users[log].quantidade[i];
	}
      writeUsers();
      writeStock();
      parseStock();
      return 1;
      }
    }
  }
  else {
    clearScreen();
    printErr("Tem que digitar 'sim' ou 'nao'\n");
    enterPrompt();
    compra(log,items);
  }
}
