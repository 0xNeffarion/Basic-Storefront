int login();

int login(){
	char usr[30];
	//char pwd[128];
	int  id;
	bool val;

	clearScreen();
	ePrint(COLOR_GREEN "***Login***" COLOR_RESET "\n");
	printf("Username: ");
	scanf("%s", usr);
	id = getIdByUsername(usr);
	if(id == -1){
		printErr("O Utilizador que inseriu não foi encontrado! Tente novamente!\n");
		usleep(1000 * 1500);
		login();
	}
	else{
		char *pwd = getpass("Password: ");
		val = validatePassword(id, pwd);
		if(val == true){
			return(getPosition(id));
		}
		else if(val == false){
			printErr("Password incorreta! Tente novamente!\n");
			usleep(1000 * 1500);
			login();
		}
	}
}
