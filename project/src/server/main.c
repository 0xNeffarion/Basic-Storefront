#include "../lib.c"

typedef struct{
  char nome[30];
  char contato[9];
  char user[30];
  char password[20];
} userdb;

void menu();
int novo(userdb utilizador[], int n);
//void erro(int input);
void cria_string(char s[], int max);
void flag(userdb utilizador[], int n);

int main() {
  userdb utilizador[100];
  int input, n=0;
  menu();
  scanf("%d",&input);
  while (input!=5) {
    switch(input) {
    case 1:{
      n=novo(utilizador,n);
      break;
    }
    case 2:
      break;
    case 3:
      break;
    case 4:
      {flag(utilizador,n);}
      break;
    }
    menu();
    scanf("%d",&input);
  }
  return 0;
}

void menu(){
  printf("**Menu**\n");
  printf("1) Criar Novo Utilizador\n");
  printf("2) Gerir Stocks\n");
  printf("3) Ver Estatisticas\n");
  printf("5) Logout\n");
  printf("4) Flag\n");
}

int novo(userdb utilizador[], int n){
  printf("Nome: \n");
  fflush(stdout);
  cria_string(utilizador[n].nome,30);
  printf("Password: \n");
  cria_string(utilizador[n].password,20);
  return n+1;
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
    printf("User:%29s| Password:%19s\n",utilizador[j].nome,utilizador[j].password);
}
