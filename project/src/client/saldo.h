void saldo(const int log);
void actionsaldo(const int opt, const int log);

void saldo(const int log){
        int opt;

        clearScreen();
        ePrint(COLOR_YELLOW "** Saldo **" COLOR_RESET "\n");
        ePrint(COLOR_CYAN "1)" COLOR_RESET " Consultar Saldo.\n");
        ePrint(COLOR_CYAN "2)" COLOR_RESET " Adicionar Saldo.\n");
        ePrint(COLOR_CYAN "3)" COLOR_RESET " Remover Saldo.\n");
        ePrint(COLOR_CYAN "4)" COLOR_RESET " Voltar ao menu inicial.\n");
        ePrint("Insira a opção desejada(1-4): ");
        if(scanf("%d", &opt) > 0) {
                actionsaldo(opt, log);
        }
}

void actionsaldo(const int opt, const int log){

        switch(opt) {
        case 1: {
                clearScreen();
                ePrint(COLOR_YELLOW "** Consultar Saldo **" COLOR_RESET "\n");
                ePrint("O seu saldo atual é:");
                printf(" %.2f€\n", users[log].balance);
                enterPrompt();
                saldo(log);
                break;
        }

        case 2: {
                float add;
                clearScreen();
                ePrint(COLOR_YELLOW "** Adicionar Saldo **" COLOR_RESET "\n");
                ePrint("Insira a quantia a adicionar ao seu saldo (em euros): ");
                if(scanf("%f", &add) <= 0) {
                        printErr("Erro a ler valor\n");
                        return;
                }
                if(add > 0) {
                        users[log].balance += add;
                        clearScreen();
                        ePrint("Saldo adicionado com sucesso!\n");
                        writeUsers();
                        parseUsers();
                        enterPrompt();
                        saldo(log);
                }
                else{
                        clearScreen();
                        printErr("Tem que adicionar um valor superior a 0 ao seu saldo!\n");
                        enterPrompt();
                        actionsaldo(2,log);
                }
                break;
        }

        case 3: {
                float rem;
                clearScreen();
                ePrint(COLOR_YELLOW "** Remover Saldo **" COLOR_RESET "\n");
                ePrint("Insira a quantia a remover ao seu saldo (em euros): ");
                if(scanf("%f", &rem) <= 0) {
                        printErr("Erro a ler valor\n");
                        return;
                }
                int flag = users[log].balance - rem;
                if (flag < 0) {
                        clearScreen();
                        printErr("A quantidade que está a tentar remover é superior ao seu saldo! Tente novamente!\n");
                        enterPrompt();
                        actionsaldo(3,log);
                }
                else if (rem > 0 && flag > 0) {
                        users[log].balance -= rem;
                        clearScreen();
                        ePrint("Saldo removido com sucesso!\n");
                        writeUsers();
                        parseUsers();
                        enterPrompt();
                        saldo(log);
                }
                else{
                        clearScreen();
                        printErr("Tem que inserir um valor superior a 0 para remover ao seu saldo!\n");
                        enterPrompt();
                        actionsaldo(3,log);
                }
                break;
                break;
        }

        case 4: {
                break;
        }

        default: {
                clearScreen();
                printErr("Opção inválida! Escolha entre a opção 1 a 3!\n");
                enterPrompt();
                saldo(log);
                break;
        }
        }
}
