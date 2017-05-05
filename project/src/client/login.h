int login();

int login(){
	char usr[30];
	//char pwd[128];
	int  id;
	bool val;

	parseUsers();
	clearScreen();
	ePrint(COLOR_GREEN "***Login***" COLOR_RESET "\n");
	printf("Username: ");
	scanf("%s", usr);
	id = getIdByUsername(usr);
	if(id == -1){
	        clearScreen();
		printErr("O Utilizador que inseriu não foi encontrado! Tente novamente!\n");
	        enterPrompt();
		login();
	}
	else{
		char *pwd = getpass("Password: ");
		val = validatePassword(id, pwd);
		if(val == true){
			return(getUserPosition(id));
		}
		else if(val == false){
		        clearScreen();
			printErr("Password incorreta! Tente novamente!\n");
			enterPrompt();
			login();
		}
	}
}
