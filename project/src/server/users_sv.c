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
	if(iduser != -1){
		printErr("Erro a inserir utilizador! (ja existe utilizador com mesmo nome)\n\n");
		return;
	}
	char *str = getpass("Insira a password [Max. 128 caracteres]:\n");
	strcpy(pw, str);
	if(strlen(pw) > 127 || strlen(pw) < 3){
		printErr("Erro a inserir utilizador! (tamanho da password)\n\n");
		return;
	}
	bool admin = false;
	if(ad == 'a'){
		admin = true;
	}
	int suc = createUser(usr, pw, admin);
	if(suc == -1){
		printErr("Erro a criar user!\n\n");
		return;
	}
}

void listarUsers(){
	parseUsers();
	int i = 0;
	if(getLastUserId() < 0){
		printf("Nao existem utilizadores registados!\n\n");
		return;
	}
	printf("Tabela de utilizadores:\n\n");
	printf("|-%-4s-|-%-30s-|-%-25s-|-%-8s-|\n", "----", "------------------------------", "-------------------------", "--------");
	printf("| " COLOR_YELLOW "%-4s" COLOR_RESET " | " COLOR_YELLOW "%-30s " COLOR_RESET "| " COLOR_YELLOW "%-25s " COLOR_RESET "| " COLOR_YELLOW "%-8s" COLOR_RESET " |\n", "ID", "NOME", "PASSWORD", "SALDO");
	printf("|-%-4s-|-%-30s-|-%-25s-|-%-8s-|\n", "----", "------------------------------", "-------------------------", "--------");
	for(i = 0; i < numUsers; i++){
		if(users[i].valid == true){
			if(users[i].admin == true){
				printf("| %-4d | "COLOR_GREEN "%-30s"COLOR_RESET " | %-25s | %-7.2f€ |\n", users[i].uid, users[i].username, users[i].password, users[i].balance);
			}
			else{
				printf("| %-4d | %-30s | %-25s | %-7.2f€ |\n", users[i].uid, users[i].username, users[i].password, users[i].balance);
			}
		}
	}
	printf("|-%-4s-|-%-30s-|-%-25s-|-%-8s-|\n", "----", "------------------------------", "-------------------------", "--------");
	printf("\n\n");
	enterPrompt();
	clearScreen();
}
