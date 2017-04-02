#include "../lib.c"

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
  ePrint("Insira a opção desejada:\n\n");
}

//void saldo(){}

void actions(const int val){
  switch(val) {
    case 1:{
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
      printf("[ERRO] Opção invalida! Escolha valores de 1 a 5\n");
      int n = 0;
      if(scanf("%d",&n) >= 1){
        actions(n);
      }
      break;
    }
  }
}

int main(){
  int input=1;
  do{
    clearScreen();
    menu();
    if(scanf("%d",&input) >= 1) {
      actions(input);
    }
  }while(1);
    return 0;
}
