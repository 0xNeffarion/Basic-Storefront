int compra(const int log, const int items);
int StatsID(const int id);
int viid(const int sid, const int cod); //verifica se o produto já se encontra nas stats

int compra(const int log, const int items){
  float total=0;
  char decision[2];
  int sid=0;
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
	int cod=users[log].buylist[i];
	int id=getItemPosition(cod);
	if (id==-1) {
	    clearScreen();
	    printErr("Houve um erro a processar a sua compra! Por favor verifique a sua lista!\n");
	    enterPrompt();
	    return 0;
	}
	else if (stocks[id].quantidade-users[log].quantidade[i]<0) {
	  clearScreen();
	  printErr("Houve um erro a processar a compra do produto "); printf("%d!\n",cod);
	  ePrint("Por favor altere a quantidade do mesmo!\n");
	  enterPrompt();
	  return 0;
	}
      }
      for(int i=0;i<items;i++) {
	int q=users[log].quantidade[i];
	int cod=users[log].buylist[i];
	int id=getItemPosition(cod);
	int j = viid(sid,cod);
	float gasto=0;
	sid=StatsID(getUserId(log));
	stocks[id].quantidade-=q;
        gasto=q*getPreco(cod);
	users[log].buylist[i]=0;
	clientstats[sid].quant[j]+=q;
	clientstats[sid].totalp+=q;
	users[log].quantidade[i]=0;
	clientstats[sid].gasto[j]+=gasto;
	if (i+1==items) {
	  users[log].balance -= total;
	  clientstats[sid].total+=total;
	}
	writeUsers();
	writeStock();
	writeClientStats();
      }
      parseUsers();
      parseStock();
      //parseClientStats();
      return 1;
    }
  }
  else {
    clearScreen();
    printErr("Tem que digitar 'sim' ou 'nao'\n");
    enterPrompt();
    compra(log,items);
  }
}

int StatsID(const int id) {
  for (int i=0; i<512; i++) {
    if (clientstats[i].userid == id) {
      return i;
    }
  }
}

int viid(const int sid, const int cod) {
  bool isval;
  for (int i=0; i<128; i++) {
    if (clientstats[sid].itemid[i] == cod) {
      isval=true;
      return i;
    }
    else {
      isval=false;
    }
  }
  if (isval == false) {
    for (int i=0; i<128; i++) {
      if(clientstats[sid].itemid[i] <= 0) {
	clientstats[sid].itemid[i]=cod;
	isval=true;
	return i;
      }
    }
  }
}
