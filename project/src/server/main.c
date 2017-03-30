#include "../lib.c"

typedef struct{
   int uid;
  char username[128];
  char password[128];
} userdb;

void menu();
int novo(userdb utilizador[], int n);
//void erro(int input);
void cria_string(char s[], int max);
void flag(userdb utilizador[], int n);

int main() {
  userdb utilizador[100];
  int input=0;
  menu();
  scanf("%d",&input);
  do{
    menu();
    scanf("%d",&input);
    actionTree(input);
    ClearScreen();
  }while (1);
  
  
  return 0;
}

void sair(){
    ClearScreen();
    printf("Fechando servidor...");
    usleep(1000*2500); // 2.5s
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

void actionTree(int val){
  switch(val) {
    case 1:{
      novo(utilizador,&n);
      break;
    }
    case 2:{
      break;
    }
    case 3:{
      break;
    }
    case 4:{
      flag(utilizador,n);
      break;
    }
    case 5:{
      sair();
      return 0;
      break;
    }   
    default:{
      printf("[ERRO] Opção invalida! Escolha valores de 1 a 5\n");
      break;
    }
  }
}

int novo(userdb utilizador[], int* n){
  printf("Username: \n");
  fflush(stdout);
  cria_string(utilizador[n].username,128);
  printf("Password: ");
  char *str = getpass("");
  strcpy(utilizador[n].password,str);
  &n = &n+1 
  return &n;
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

void flag(userdb utilizador[], int n){
  int j;
  for(j=0;j<n;j++)
    printf("User:%128s| Password:%128s\n",utilizador[j].username,utilizador[j].password);
}
