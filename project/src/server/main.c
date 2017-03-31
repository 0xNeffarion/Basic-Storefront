#include "../lib.c"
int nextId = 0;

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

void cria_string(char s[], int max){
  int i=0;
  char c;
  while(isdigit(c) || isalpha(c)) {
    c=getchar();
  }
  s[i++]=c;
  while((s[i]=getchar() != '\n') && i < max)
    i++;
  s[i]='\0';
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
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Novo Utilizador\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir Stocks\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver Estatisticas\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Flag\n");
  ePrint(COLOR_CYAN "5)" COLOR_RESET " Sair\n");
  ePrint("Insira a opção desejada:\n\n");
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
  int input=1;
  do{
    clearScreen();
    menu();
    if(scanf("%d",&input) >= 1){
      actions(input);  
    }
  }while(1);
  
  return 0;
}


