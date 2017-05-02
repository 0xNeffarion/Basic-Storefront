int compra(const int log, const int items);

int compra(const int log, const int items){
  float total=0;
  char decision[2];
  clearScreen();
  ePrint("Prosseguir com a compra? (sim/nao)\n");
  scanf("%s", decision);
  if (items==0) {
    printErr("Não possui uma lista, por favor crie uma!\n");
    enterPrompt();
    return 0;
  }
  else if (strcmp(decision,"nao") == 0) {
    return 0;
  }
  else if(strcmp(decision,"sim")==0 && items>0){
    for(int i=0;i < items;i++) {
      int q=users[log].quantidade[i];
      int cod=users[log].buylist[i];
      total+=q*getPreco(cod);
    }
    clearScreen();
    printf("Total: %.2f€\n",total);
    enterPrompt();
    return 1;
  }
  else {
    clearScreen();
    printf("%s\n",decision);
    printErr("Tem que digitar 'sim' ou 'nao'\n");
    enterPrompt();
    compra(log,items);
  }
}
