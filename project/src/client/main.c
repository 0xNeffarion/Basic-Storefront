#include "../lib.c"

void sair();
void menu();
void saldo();
void actionsaldo(const int opt);
void actions(const int val);

void sair(){
  clearScreen();
  printf("Saindo do cliente...\n");
  usleep(1000*1500); //1,5s
  exit(0);
}

void menu(){
  ePrint(COLOR_YELLOW "** Menu **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Gerir Saldo\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir Lista de Compras\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver Estatisticas\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Logout\n");
  ePrint("Insira a opção desejada(1-4):\n");
}

void actions(const int val){
  switch(val) {
    case 1:{
      saldo();
      break;
    }
    case 2:{
      break;
    }
    case 3:{
      break;
    }
    case 4:{
      sair();
      return;
      break;
    }
    default:{
      ePrint(COLOR_RED "ERRO!" COLOR_RESET " Opção inválida! Escolha entre a opção 1 a 4!\n");
      int n = 0;
      if(scanf("%d",&n) >= 1){
        actions(n);
      }
      break;
    }
  }
}

void saldo(){
  int opt=0;
  clearScreen();
  ePrint(COLOR_YELLOW "** Saldo **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Consultar Saldo.\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Adicionar Saldo.\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu inicial.\n");
  ePrint("Insira a opção desejada(1-3):\n");
  scanf("%d",&opt);
  actionsaldo(opt);
}

void actionsaldo(const int opt) {
  int add;
  switch(opt){
  case 1:{
    clearScreen();
    ePrint("O seu saldo atual é: teste euros\n");
    usleep(1000*2000);
    saldo();
    break;
  }
  case 2:{
    clearScreen();
    ePrint("Insira a quantia a adicionar ao seu saldo (em euros)!\n");
    scanf("%d",&add);
    saldo();
    break;
  }
  case 3:{
    break;
  } 
  default:{
    ePrint(COLOR_RED "ERRO!" COLOR_RESET " Opção inválida! Escolha entre a opção 1 a 3!\n");
    scanf("%d",&opt);
    actionsaldo(opt);
    break;
  }
  }
}

int main(){
  int input=1;
  parseUsers();
  do{
    clearScreen();
    menu();
    if(scanf("%d",&input) >= 1) {
      actions(input);
    }
  }while(1);
    return 0;
}
