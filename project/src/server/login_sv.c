int login();

int login(){
	char usr[30];
	int  id;
	bool val;

	clearScreen();
	printf(COLOR_GREEN "+++ Login +++" COLOR_RESET "\n");
	printf("Username: ");
	if(scanf("%s", usr) <= 0){
		printErr("Tem que inserir um utilizador!\n");
		usleep(1000 * 2500);
		login();
	}
	id = getIdByUsername(usr);
	if(id == -1){
		printErr("O Utilizador que inseriu não foi encontrado! Tente novamente!\n");
		usleep(1000 * 2500);
		login();
	}
	else{
		if(users[getUserPosition(id)].admin == false){
			printErr("O Utilizador que inseriu não e administrador!\n");
			usleep(1000 * 2500);
			login();
		}
		else{
			clearScreen();
			int fail = 0;
			printf(COLOR_GREEN "+++ Login +++" COLOR_RESET "\n");
			while(1){
				if(fail > 3){
					printErr("Demasiadas tentativas de login.\n");
					usleep(1000 * 2500);
					sair();
				}
				char *pwd = getpass("Password: ");
				val = validatePassword(id, pwd);
				if(val == true){
					strcpy(myusr, usr);
					clearScreen();
					return(getUserPosition(id));
				}
				else if(val == false){
					fail++;
					printErr("Password incorreta! Tente novamente! (%d)\n\n", fail);
				}
			}
		}
	}

	return(-1);
}
