void novoUser();
void listarUsers();

void novoUser(){
  clearScreen();
  char usr[30];
  char pw[128];
  char ad;
  printf("Criar administrador ou utilizador? (a/u): \n");
  if(scanf(" %c", &ad) != 1){
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
  if(strlen(usr) > 29 || strlen(usr) < 3){
    printErr("Erro a inserir utilizador! (tamanho do nome)\n\n");
    return;
  }
  int iduser = getIdByUsername(usr);
  if(iduser!=-1){
    printErr("Erro a inserir utilizador! (ja existe utilizador com mesmo nome)\n\n");
    return;
  }
  char *str = getpass("Insira a password [Max. 128 caracteres]:\n");
  strcpy(pw,str);
  if(strlen(pw) > 127 || strlen(pw) < 3){
    printErr("Erro a inserir utilizador! (tamanho da password)\n\n");
    return;
  }
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
