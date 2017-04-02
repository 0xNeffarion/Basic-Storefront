#include "../lib.c"

void sair();
void novoUser();
void listarUsers();
void menu();
void actions(const int val);

void sair(){
    clearScreen();
    printf("Fechando servidor...\n");
    usleep(1000*1500); // 1.5s
    exit(0);
}

void novoUser(){
  clearScreen();
  char usr[30];
  char pw[128];
  
  printf("Insira o nome de utilizador [Max. 30 caracteres]: \n");
  if(scanf("%s", &usr[0]) < 0){
    printf("Erro a inserir utilizador!\n");
    return;
  }
  char *str = getpass("Insira a password [Max. 128 caracteres]:\n");
  strcpy(pw,str);
  
  //CRIAR USER
}

void listarUsers(){
  int j;
  int n = sizeof(users);
  for(j=0;j<n;j++)
  if(users[j].username != NULL && users[j].password != NULL){
    if(strlen(users[j].username) > 1)
    printf("User:%128s| Password:%128s\n", users[j].username, users[j].password);
  }
}

void menu(){
  ePrint(COLOR_YELLOW "** Menu **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar novo utilizador\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir stocks\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver estatisticas\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Listar utilizadores\n");
  ePrint(COLOR_CYAN "5)" COLOR_RESET " Sair\n");
  ePrint("Insira a opcao desejada:\n\n");
}

void actions(const int val){
  switch(val) {
    case 1:{
      novoUser();
      break;
    }
    case 2:{
      break;
    }
    case 3:{
      break;
    }
    case 4:{
      listarUsers();
      break;
    }
    case 5:{
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

int main() {
  setlocale(LC_ALL, "en_US.UTF-8");
  int input=1;
  parseUsers();
  do{
    clearScreen();
    menu();
    if(scanf("%d",&input) >= 1){
      actions(input);  
    }
  }while(1);
  
  return 0;
}


