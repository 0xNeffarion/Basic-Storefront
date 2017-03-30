#include "../lib.c"

typedef struct{
   int uid;
  char username[30];
  char password[128];
} userdb;

userdb users[256];
int nextId = 0;

void sair(){
    clearScreen();
    printf("Fechando servidor...\n");
    usleep(1000*1500); // 1.5s
    exit(0);
}

void menu(){
  ePrint("** Menu **\n");
  ePrint("1) Criar Novo Utilizador\n");
  ePrint("2) Gerir Stocks\n");
  ePrint("3) Ver Estatisticas\n");
  ePrint("4) Flag\n");
  ePrint("5) Sair\n");
  ePrint("Insira a opção desejada:\n\n");
}

void actionTree(const int val){
  switch(val) {
    case 1:{
      novo();
      break;
    }
    case 2:{
      break;
    }
    case 3:{
      break;
    }
    case 4:{
      flag();
      break;
    }
    case 5:{
      sair();
      return 0;
      break;
    }
    default:{
      printf("[ERRO] Opção invalida! Escolha valores de 1 a 5\n");
      int n = 0;
      scanf("%d",&n);
      actionTree(n);
      break;
    }
  }
}

void novo(){
  clearScreen();
  char usr[30];
  char pw[128];
  
  printf("Insira o nome de utilizador [Max. 30 caracteres]: \n");
  scanf("%s", &usr);
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

void flag(){
  int j;
  int n = sizeof(users);
  for(j=0;j<n;j++)
  if(users[j].username != NULL && users[j].password != NULL){
    printf("User:%128s| Password:%128s\n", users[j].username, users[j].password);
  }
}

int main() {
  int input=1;
  do{
    clearScreen();
    menu();
    scanf("%d",&input);
    actionTree(input);
  }while (1);
  
  return 0;
}


