int login();

int login(){
        char usr[30];
        //char pwd[128];
        int id;
        bool val;

        parseUsers();
        clearScreen();
        ePrint(COLOR_GREEN "***Login***" COLOR_RESET "\n");
        printf("Username: ");
        if(scanf("%s", usr) <= 0) {
                printErr("Erro a ler valor\n");
                return -1;
        }
        id = getIdByUsername(usr);
        if(id == -1) {
                clearScreen();
                printErr("O Utilizador que inseriu não foi encontrado! Tente novamente!\n");
                enterPrompt();
                login();
        }
        else{
                char *pwd = getpass("Password: ");
                val = validatePassword(id, pwd);
                if(val == true) {
                        return(getUserPosition(id));
                }
                else{
                        clearScreen();
                        printErr("Password incorreta! Tente novamente!\n");
                        enterPrompt();
                        return login();
                }
        }
	return login();
}
