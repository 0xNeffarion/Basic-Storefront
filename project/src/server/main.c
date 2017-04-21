#include "../lib.c"

void sair();
void novoUser();
void listarUsers();
void menu();
void startupActions();
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
  char ad;
  printf("Criar administrador ou utilizador? (a/u): \n");
  if(scanf(" %c", &ad) <= 0){
    printErr("Erro a inserir tipo de user!\n\n");
    return;
  }
  if(ad != 'a' && ad != 'u'){
    printErr("Insira 'a' para administrador ou 'u' para utilizador\n");
    return;
  }
  clearScreen();
  printf("Insira o nome de utilizador [Max. 30 caracteres]: \n");
  if(scanf("%s", &usr[0]) <= 0){
    printErr("Erro a inserir utilizador!\n\n");
    return;
  }
  char *str = getpass("Insira a password [Max. 128 caracteres]:\n");
  strcpy(pw,str);
  bool admin = false;
  if(ad == 'a'){
    admin = true;
  }
  int suc = createUser(usr,pw,admin);
  if(suc==-1){
    printErr("Erro a criar user!\n\n");
    return;
  }
}

void listarUsers(){
  int i = 0, size = numUsers;
  parseUsers();
  if(size >= 1){
    printf("Administradores: Cor verde\n");
    printf("Utilizadores: Cor branca\n\n");
    printf("ID - Username - Balance\n");
  }else{
    printf("Nao existem utilizadores registados!\n");
    return;
  }
  for(; i < size; i++){
    if(users[i].valid == true){
      if(users[i].admin == true){
        printf(COLOR_GREEN "[%d] - %s - %.2f€\n" COLOR_RESET, users[i].uid, users[i].username, users[i].balance);
      }else{
        printf("[%d] - %s - %.2f€\n", users[i].uid, users[i].username, users[i].balance);
      }
    }
  }

  printf("\n\n");


}

void menu(){
  ePrint(COLOR_YELLOW "** Menu **" COLOR_RESET "\n");
  ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar novo utilizador\n");
  ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir stocks\n");
  ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver estatisticas\n");
  ePrint(COLOR_CYAN "4)" COLOR_RESET " Listar utilizadores\n");
  ePrint(COLOR_CYAN "5)" COLOR_RESET " Sair\n");
  ePrint("Insira a opcao desejada (1-5):\n\n");
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
      printErr("Opção invalida! Escolha valores de 1 a 5\n");
      int n = 0;
      if(scanf("%d",&n) >= 1){
        actions(n);
      }
      break;
    }
  }
}

void startupActions(){
  clearScreen();
  setlocale(LC_ALL, "en_US.UTF-8");
  char fp[512];
  getUsersFilePath(fp);
  char dr[512];
  getDataDirectory(dr);
  if(!dirExists(&dr[0])){
    if(!createDir(&dr[0])){
      printErr("Nao foi possivel criar diretorio de registo\n");
      exit(1);
      return;
    }
  }
  if(!fileExists(&fp[0])){
    if(!create(&fp[0])){
      printErr("Nao foi possivel criar ficheiro de registo\n");
      exit(1);
      return;
    }
  }
}

int main() {
  startupActions();
  int input=1;
  parseUsers();
  do{
    menu();
    if(scanf("%d",&input) >= 1){
      clearScreen();
      actions(input);
    }

  }while(1);

  return 0;
}
