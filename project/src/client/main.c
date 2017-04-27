#include "../lib.c"

void startupActions();
int login();
void sair();
void menu();
void actions(const int opt, const int log);
void saldo(const int log);
void actionsaldo(const int opt, const int log);
void lista(const int log);
void actionslista(const int opt, const int log);
void estatisticas();
void actionsestatisticas(const int opt);

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

void sair(){
	clearScreen();
	ePrint("Saindo... Volte sempre!\n");
	usleep(1000 * 1500); //1,5s
	exit(0);
}

void menu(){
	ePrint(COLOR_YELLOW "** Menu **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Gerir Saldo\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Gerir Lista de Compras\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Ver Estatísticas\n");
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Logout\n");
	ePrint("Insira a opção desejada(1-4):\n");
}

void actions(const int opt, const int log){
	switch(opt){
	case 1: {
		saldo(log);
		break;
	}

	case 2: {
		lista(log);
		break;
	}

	case 3: {
		estatisticas();
		break;
	}

	case 4: {
		sair();
		return;

		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 4!\n");
		int opt = 0;
		if(scanf("%d", &opt) >= 1){
			actions(opt, log);
		}
		break;
	}
	}
}

void saldo(const int log){
	int opt;

	clearScreen();
	ePrint(COLOR_YELLOW "** Saldo **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Consultar Saldo.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Adicionar Saldo.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-3):\n");
	scanf("%d", &opt);
	if(opt >= 1 && opt <= 3){
		actionsaldo(opt, log);
	}
	else{
		clearScreen();
		printErr("Escolha entre a opção 1 a 3!\n");
		usleep(1000 * 1500);
		saldo(log);
	}
}

void actionsaldo(const int opt, const int log){
	float add;

	switch(opt){
	case 1: {
		clearScreen();
		ePrint("O seu saldo atual é:");
		printf(" %.2f euros\n", users[log].balance);
		usleep(1000 * 2000);
		saldo(log);
		break;
	}

	case 2: {
		clearScreen();
		ePrint("Insira a quantia a adicionar ao seu saldo (em euros)!\n");
		scanf("%f", &add);
		if(add > 0){
			users[log].balance += add;
			clearScreen();
			ePrint("Saldo adicionado com sucesso!\n");
			usleep(1000 * 1500);
		}
		else{
			clearScreen();
			printErr("Tem que adicionar um valor superior a 0 ao seu saldo!\n");
			usleep(1000 * 2500);
		}
		saldo(log);
		break;
	}

	case 3: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 3!\n");
		int opt = 0;
		if(scanf("%d", &opt) > 0){
			actionsaldo(opt, log);
		}
		break;
	}
	}
}

void lista(const int log){
	//Criar variável na struct
	int opt = 0;

	clearScreen();
	ePrint(COLOR_YELLOW "** Lista **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Lista de Compras.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Consultar Lista de Compras.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Adicionar produtos à Lista de Compras.\n");
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Comprar produtos da lista.\n");
	ePrint(COLOR_CYAN "5)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-5):\n");
	if(scanf("%d", &opt) > 0){
		actionslista(opt, log);
	}
}

void actionslista(const int opt, const int log){
	switch(opt){
	case 1: {
		//aceder à lista na struct
		clearScreen();
		ePrint("Adicione os códigos dos produtos à sua lista:\n");
		ePrint("Pressine 0 quando terminar de adicionar produtos à sua lista!\n");
		int items = 1;
		for(int i = 0; i < items; i++){
			int flag;
			scanf("%d", &flag);
			if(flag != 0){
				//adicionar na struct
			}
			else{
				break;
			}
			items++;
		}
		lista(log);
		break;
	}

	case 2: {
		clearScreen();
		int size = sizeof(users[log].buylist);
		if(size == 0){
			ePrint("Não tem produtos na sua lista!");
		}
		else{
			ePrint("A sua lista é composta pelos seguintes produtos:\n");
			int i = 0;
			for(i = 0; i < size; i++){
				printf("%d\n", users[log].buylist[i]);
			}
		}
		usleep(1000 * 2000);
		lista(log);
		break;
	}

	case 3: {
		clearScreen();
		actionslista(1, log);
		break;
	}

	case 4: {
		clearScreen();
		ePrint("Total a pagar: (teste) \n"); //fazer soma do valor de todos os produtos da lista
		ePrint("Acabou de comprar os produtos que estão na sua lista!\n");
		usleep(1000 * 2000);
		lista(log);
		break;
	}

	case 5: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 5!\n");
		int opt = 0;
		if(scanf("%d", &opt) > 0){
			actionslista(opt, log);
		}
		break;
	}
	}
}

void estatisticas(){
	int opt = 0;

	clearScreen();
	ePrint(COLOR_YELLOW "** Estatísticas **" COLOR_RESET "\n");
	ePrint(COLOR_CYAN "1)" COLOR_RESET " Quantidade total de produtos comprados.\n");
	ePrint(COLOR_CYAN "2)" COLOR_RESET " Quantidade comprada de um determinado produto.\n");
	ePrint(COLOR_CYAN "3)" COLOR_RESET " Valor total gasto num determinado produto.\n");
	//adicionar mais estatisticas?
	ePrint(COLOR_CYAN "4)" COLOR_RESET " Voltar ao menu inicial.\n");
	ePrint("Insira a opção desejada(1-4):\n");
	if(scanf("%d", &opt) > 0){
		actionsestatisticas(opt);
	}
}

void actionsestatisticas(const int opt){
	switch(opt){
	case 1: {
		//Falta criar um contador associado ao user
		clearScreen();
		ePrint("Comprou (teste) produtos.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 2: {
		int prod;
		clearScreen();
		ePrint("Insira o código do produto!\n");
		scanf("%d", &prod);
		//aceder a um contador?
		ePrint("Comprou (teste) quantidade do produto.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 3: {
		int prod;
		clearScreen();
		ePrint("Insira o código do produto!\n");
		scanf("%d", &prod);
		//contador*preço
		ePrint("Gastou (teste) euros no produto.\n");
		usleep(1000 * 2000);
		estatisticas();
		break;
	}

	case 4: {
		break;
	}

	default: {
		printErr("Opção inválida! Escolha entre a opção 1 a 4!\n");
		int opt = 0;
		if(scanf("%d", &opt) > 0){
			actionsestatisticas(opt);
		}
		break;
	}
	}
}

int main(){
	startupActions();
	parseUsers();
	int opt = 0, log = -1;
	log = login();
	if(log > -1){
		ePrint("Login efetuado com sucesso! Bem-vindo!\n");
		usleep(1000 * 1000);
		do {
			clearScreen();
			menu();
			if(scanf("%d", &opt) > 0){
				actions(opt, log);
			}
		} while(1);
	}
	return(0);
}
