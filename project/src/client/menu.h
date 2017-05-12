void menu(const int log);

void menu(const int log){
        printf(COLOR_YELLOW "Bem-vindo %s! " COLOR_RESET "\n\n", users[log].username);
        ePrint(COLOR_YELLOW " +++ Menu Principal +++ " COLOR_RESET "\n");
	ePrint(COLOR_CYAN "[1] ‣" COLOR_RESET " Gerir Saldo\n");
	ePrint(COLOR_CYAN "[2] ‣" COLOR_RESET " Gerir Lista de Compras\n");
	ePrint(COLOR_CYAN "[3] ‣" COLOR_RESET " Ver Estatísticas\n\n");
	ePrint(COLOR_MAGENTA "[4] ‣" COLOR_RESET " Sobre\n\n");
	ePrint(COLOR_RED "[5] ‣" COLOR_RESET " Logout [⇲]\n\n");
	ePrint("Insira a opção desejada(1-5): ");
}
