void menu();
void menuStocks();

void menu(){
	printf(COLOR_YELLOW "Loggado como: %s " COLOR_RESET "\n\n", myusr);
	ePrint(COLOR_YELLOW " +++ Menu Principal +++ " COLOR_RESET "\n");
	ePrint(COLOR_CYAN "[1] ‣" COLOR_RESET " Criar novo utilizador\n");
	ePrint(COLOR_CYAN "[2] ‣" COLOR_RESET " Gerir stocks\n");
	ePrint(COLOR_CYAN "[3] ‣" COLOR_RESET " Ver estatisticas\n");
	ePrint(COLOR_CYAN "[4] ‣" COLOR_RESET " Listar utilizadores\n\n");
	ePrint(COLOR_MAGENTA "[5] ‣" COLOR_RESET " Sobre\n\n");
	ePrint(COLOR_RED "[6] ‣" COLOR_RESET " Sair [⇲]\n\n");
	ePrint("Insira a opcao desejada (1-6):\n");
}

void menuStocks(){
	ePrint(COLOR_YELLOW " +++ Menu Stocks +++ " COLOR_RESET "\n");
	ePrint(COLOR_CYAN "[1] ‣" COLOR_RESET " Listar todos os items\n");
	ePrint(COLOR_CYAN "[2] ‣" COLOR_RESET " Criar um novo item\n");
	ePrint(COLOR_CYAN "[3] ‣" COLOR_RESET " Editar preco de um item\n");
	ePrint(COLOR_CYAN "[4] ‣" COLOR_RESET " Editar quantidade de um item\n");
	ePrint(COLOR_CYAN "[5] ‣" COLOR_RESET " Editar nome de um item\n");
	ePrint(COLOR_CYAN "[6] ‣" COLOR_RESET " Eliminar item\n");
	ePrint(COLOR_MAGENTA "[7] ‣" COLOR_RESET " Voltar para menu principal\n\n");
	ePrint(COLOR_RED "[8] ‣" COLOR_RESET " Sair servidor [⇲]\n\n");
	ePrint("Insira a opcao desejada (1-8):\n");
}

void menuStats(){
	ePrint(COLOR_YELLOW " +++ Menu Estatisticas +++ " COLOR_RESET "\n");
	ePrint(COLOR_CYAN "[1] ‣" COLOR_RESET " Quantidade de produtos vendidos no total\n");
	ePrint(COLOR_CYAN "[2] ‣" COLOR_RESET " Quantidade vendida de um determinado produto\n");
	ePrint(COLOR_CYAN "[3] ‣" COLOR_RESET " Lucro de um determinado produto\n");
	ePrint(COLOR_CYAN "[4] ‣" COLOR_RESET " Analisar os produtos comprados por um determinado cliente\n");
	ePrint(COLOR_MAGENTA "[5] ‣" COLOR_RESET " Voltar para menu principal\n\n");
	ePrint(COLOR_RED "[6] ‣" COLOR_RESET " Sair servidor [⇲]\n\n");
	ePrint("Insira a opcao desejada (1-6):\n");
}
