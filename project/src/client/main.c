#include "../lib.c"

void sair();
void menu();
void actions(const int opt);
void saldo();
void actionsaldo(const int opt);
void lista();
void actionslista(const int opt);
void estatisticas();
void actionsestatisticas(const int opt);

void sair(){
  clearScreen();
  printf("Saindo... Volte sempre!\n");
  usleep(1000*1500); //1,5s
  exit(0);
}

void menu(){
  ePrint(COLOR_YELLOW "** Menu **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Gerir Saldo\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir Lista de Compras\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver Estatísticas\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Logout\n");
  ePrint("Insira a opção desejada(1-4):\n");
}

void actions(const int opt){
  switch(opt) {
    case 1:{
      saldo();
      break;
    }
    case 2:{
      lista();
      break;
    }
    case 3:{
      estatisticas();
      break;
    }
    case 4:{
      sair();
      return;
      break;
    }
    default:{
      ePrint(COLOR_RED "ERRO!" COLOR_RESET " Opção inválida! Escolha entre a opção 1 a 4!\n");
      int opt = 0;
      if(scanf("%d",&opt) >= 1){
        actions(opt);
      }
      break;
    }
  }
}

void saldo(){
  //Criar variável na struct
  int opt=0;
  clearScreen();
  ePrint(COLOR_YELLOW "** Saldo **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Consultar Saldo.\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Adicionar Saldo.\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu inicial.\n");
  ePrint("Insira a opção desejada(1-3):\n");
  if(scanf("%d",&opt)>0){
    actionsaldo(opt);
  }
}

void actionsaldo(const int opt) {
  int add;
  switch(opt){
  case 1:{
    //Falta aceder à struct para obter o saldo do user
    clearScreen();
    ePrint("O seu saldo atual é: teste euros\n");
    usleep(1000*2000);
    saldo();
    break;
  }
  case 2:{
    clearScreen();
    ePrint("Insira a quantia a adicionar ao seu saldo (em euros)!\n");
    if(scanf("%d",&add) > 0){
      int s = 0;

      saldo();
    }
    break;
  }
  case 3:{
    break;
  }
  default:{
    ePrint(COLOR_RED "ERRO!" COLOR_RESET " Opção inválida! Escolha entre a opção 1 a 3!\n");
    int opt = 0;
    if(scanf("%d",&opt) > 0){
      actionsaldo(opt);
    }
    break;
  }
  }
}

void lista(){
  //Criar variável na struct
  int opt=0;
  clearScreen();
  ePrint(COLOR_YELLOW "** Lista **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Lista de Compras.\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Consultar Lista de Compras.\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Adicionar produtos à Lista de Compras.\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Comprar produtos da lista.\n");
  ePrint(COLOR_CYAN "5)" COLOR_RESET " Voltar ao menu inicial.\n"); 
  ePrint("Insira a opção desejada(1-5):\n");
  if(scanf("%d",&opt) > 0){
    actionslista(opt);
  }
}

void actionslista(const int opt){
  switch(opt){
  case 1:{
    //aceder à lista na struct
    clearScreen();
    ePrint("Adicione os códigos dos produtos à sua lista:\n");
    ePrint("Pressine 0 quando terminar de adicionar produtos à sua lista!\n");
    int items=1;
    for(int i=0;i<items;i++) {
      int flag;
      scanf("%d",&flag);
      if(flag!=0) {
	//adicionar na struct
      }
      else
	break;
      items++;
    }
    lista();
    break;
  }
  case 2:{
    //aceder à lista na struct
    clearScreen();
    ePrint("A sua lista é composta pelos seguintes produtos:");
    //ler produtos da struct lista do utilizador
    printf("\n");
    usleep(1000*2000);
    lista();
    break;
  }
  case 3:{
    clearScreen();
    actionslista(1);
    break;
  }
  case 4:{
    clearScreen();
    ePrint("Total a pagar: (teste) \n"); //fazer soma do valor de todos os produtos da lista
    ePrint("Acabou de comprar os produtos que estão na sua lista!\n");
    usleep(1000*2000);
    lista();
    break;
  }
  case 5:{
    break;
  }
  default:{
    printErr("Opção inválida! Escolha entre a opção 1 a 5!\n");
    int opt = 0;
    if(scanf("%d",&opt) > 0){
      actionslista(opt);
    }
    break;
  }
  }
}

void estatisticas() {
  int opt=0;
  clearScreen();
  ePrint(COLOR_YELLOW "** Estatísticas **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Quantidade total de produtos comprados.\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Quantidade comprada de um determinado produto.\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Valor total gasto num determinado produto.\n");
  //adicionar mais estatisticas?
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Voltar ao menu inicial.\n"); 
  ePrint("Insira a opção desejada(1-4):\n");
  if(scanf("%d",&opt) > 0){
    actionsestatisticas(opt);
  }
}

void actionsestatisticas(const int opt){
  switch(opt){
  case 1:{
    //Falta criar um contador associado ao user
    clearScreen();
    ePrint("Comprou (teste) produtos.\n");
    usleep(1000*2000);
    estatisticas();
    break;
  }
  case 2:{
    int prod;
    clearScreen();
    ePrint("Insira o código do produto!\n");
    scanf("%d",&prod);
    //aceder a um contador?
    ePrint("Comprou (teste) quantidade do produto.\n");
    usleep(1000*2000);
    estatisticas();
    break;
  }
  case 3:{
    int prod;
    clearScreen();
    ePrint("Insira o código do produto!\n");
    scanf("%d",&prod);
    //contador*preço
    ePrint("Gastou (teste) euros no produto.\n");
    usleep(1000*2000);
    estatisticas();
    break;
  }
  case 4:{
    break;
  }
  default:{
    ePrint(COLOR_RED "ERRO!" COLOR_RESET " Opção inválida! Escolha entre a opção 1 a 4!\n");
    int opt = 0;
    if(scanf("%d",&opt) > 0){
      actionsestatisticas(opt);
    }
    break;
  }
  }
}

int main(){
  int opt=1;
  //parseUsers();
  do{
    clearScreen();
    menu();
    if(scanf("%d",&opt) > 0) {
      actions(opt);
    }
  }while(1);
    return 0;
}
