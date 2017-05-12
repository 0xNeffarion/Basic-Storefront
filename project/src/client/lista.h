void lista(const int log);
void actionslista(const int opt, const int log);
void addprod(const int items, const int log); //adiciona produto
void remprod(const int items, const int log); //remove produto
void mod(const int log); //modifica lista
int existe(const int log, const int add); //verifica se produto existe na lista
int vp(const int add); //verifica produto em stock
int vq(const int id, const int q); //verifica quantidade do produto em stock

void lista(const int log){
        int opt = 0;
        parseStock();

        clearScreen();
        ePrint(COLOR_YELLOW "** Lista **" COLOR_RESET "\n");
        ePrint(COLOR_CYAN "1)" COLOR_RESET " Criar Lista de Compras.\n");
        ePrint(COLOR_CYAN "2)" COLOR_RESET " Consultar Lista de Compras.\n");
        ePrint(COLOR_CYAN "3)" COLOR_RESET " Adicionar produtos à Lista de Compras.\n");
        ePrint(COLOR_CYAN "4)" COLOR_RESET " Alterar Lista de Compras.\n");
        ePrint(COLOR_CYAN "5)" COLOR_RESET " Comprar produtos da lista.\n");
        ePrint(COLOR_CYAN "6)" COLOR_RESET " Voltar ao menu inicial.\n");
        ePrint("Insira a opção desejada(1-6): ");
        scanf("%d",&opt);
        actionslista(opt, log);
}

void actionslista(const int opt, const int log){
        int items = 0;
        for(int i = 0; i < 128; i++) {
                if(users[log].buylist[i]>0) {
                        items++;
                }
        }

        switch(opt) {

        case 1: {
                clearScreen();
                if (items > 0) {
                        clearScreen();
                        printErr("Já possui uma lista! Por favor selecione a opção nº3!\n");
                        enterPrompt();
                        lista(log);
                }
                else {
                        addprod(items,log);
                }
                break;
        }

        case 2: {
                clearScreen();
                if(items == 0) {
                        clearScreen();
                        printErr("Não tem produtos na sua lista!\n");
                        enterPrompt();
                        lista(log);
                }
                else{
                        printf("Lista de Compras:\n\n");
                        printf("|-%-6s-|-%-10s-|-%-5s-|\n", "------", "----------", "-----");
                        printf("| " COLOR_GREEN "%-6s" COLOR_RESET " | " COLOR_GREEN "%-10s " COLOR_RESET "| " COLOR_GREEN "%-5s " COLOR_RESET "|\n", "Código", "Quantidade", "Stock");
                        printf("|-%-6s-|-%-10s-|-%-5s-|\n", "------", "----------", "-----");

                        for(int i = 0; i < items; i++) {
                                int pid=vp(users[log].buylist[i]); //id do produto
                                char q[2];
                                if (pid>=0) {strcpy(q,"Sim");}
                                else if (pid==-2) {strcpy(q,"Nao");}
                                printf("| %-6d | %-10d | %-5s |\n", users[log].buylist[i], users[log].quantidade[i], q);
                        }
                        printf("|-%-6s-|-%-10s-|-%-5s-|\n", "------", "----------", "-----");
                        printf("\n\n");
                        enterPrompt();
                        lista(log);
                }
                break;
        }

        case 3: {
                clearScreen();
                if (items==0) {
                        clearScreen();
                        printErr("Não possui uma lista! Utilize a opção nº1 para criar uma!\n");
                        enterPrompt();
                        lista(log);
                }
                else {
                        addprod(items,log);
                }
                break;
        }

        case 4: {
                clearScreen();
                int o=0;
                ePrint(COLOR_YELLOW "** Alterar Lista de Compras **" COLOR_RESET "\n");
                ePrint(COLOR_CYAN "1)" COLOR_RESET " Modificar quantidade de um produto.\n");
                ePrint(COLOR_CYAN "2)" COLOR_RESET " Remover produto.\n");
                ePrint(COLOR_CYAN "3)" COLOR_RESET " Voltar ao menu anterior.\n");
                ePrint("Insira a opção desejada(1-3): ");
                scanf("%d",&o);
                if (o!=1 && o!=2 && o!=3) {
                        clearScreen();
                        printErr("Opção inválida! Escolha entre a opção 1 a 3!\n");
                        enterPrompt();
                        actionslista(4,log);
                }
                else if (o!=3 && items==0) {
                        clearScreen();
                        printErr("Não tem produtos na sua lista!\n");
                        enterPrompt();
                        lista(log);
                }
                else if (o==1 && items!=0) {
                        clearScreen();
                        mod(log);
                }
                else if(o==2 && items!=0) {
                        clearScreen();
                        remprod(items, log);
                }
                else {
                        lista(log);
                }
                break;
        }

        case 5: {
                int fc=0;
                clearScreen();
                fc=compra(log, items);
                if (fc==0) {
                        lista(log);
                }
                else if(fc==1) {
                        clearScreen();
                        ePrint("Compra efetuada com sucesso!\n");
                        enterPrompt();
                        lista(log);
                }
                break;
        }

        case 6: {
                break;
        }

        default: {
                clearScreen();
                printErr("Opção inválida! Escolha entre a opção 1 a 6!\n");
                enterPrompt();
                lista(log);
                break;
        }
        }
}

void addprod(const int items, const int log){
        parseStock();
        int add=0, q=0, e=0, fp=0, fq=0;
        int j = items;
        clearScreen();
        ePrint(COLOR_YELLOW "** Adicione um produto à sua lista **" COLOR_RESET "\n");
        ePrint("Pressine '0' quando terminar de adicionar produtos à sua lista!\n");
        ePrint("Adicione o código do produto à sua lista: ");
        scanf("%d",&add);
        if(add==0) {
                lista(log);
        }
        e=existe(log,add);
        if (add < 0) {
                clearScreen();
                printErr("Tem que selecionar um código de produto maior do que 0!\n");
                enterPrompt();
                addprod(items,log);
        }
        else if (add > 0 && e>=0) {
                clearScreen();
                printErr("O produto já se encontra na sua lista!\n");
                printf("Para alterar a quantidade do mesmo, por favor selecione a opção nº4!\n");
                enterPrompt();
                addprod(items,log);
        }
        else if (add > 0 && e<0) {
                fp=vp(add);
                if (fp==-2) {
                        clearScreen();
                        printErr("O produto de momento não se encontra em stock!\n");
                        enterPrompt();
                        addprod(items,log);
                }
                else if (fp >= 0) {
                        parseStock();
                        users[log].buylist[j] = add;
                        clearScreen();
                        ePrint(COLOR_YELLOW "** Adicione um produto à sua lista **" COLOR_RESET "\n");
                        printf("Código do produto: %d\n",add);
                        printf("%d disponiveis.\n",stocks[fp].quantidade);
                        ePrint("Selecione a quantidade prentendida: ");
                        scanf("%d",&q);
                        while(q <= 0) {
                                parseStock();
                                clearScreen();
                                printErr("Selecionou uma quantidade igual ou inferior a 0!\n");
                                enterPrompt();
                                clearScreen();
                                ePrint(COLOR_YELLOW "** Adicione um produto à sua lista **" COLOR_RESET "\n");
                                printf("Código do produto: %d\n",add);
                                printf("%d disponiveis.\n",stocks[fp].quantidade);
                                ePrint("Selecione a quantidade prentendida: ");
                                scanf("%d",&q);
                        }
                        fq=vq(fp,q);
                        while(fq==-1) {
                                parseStock();
                                clearScreen();
                                printErr("Selecionou uma quantidade superior ao stock existente!\n");
                                enterPrompt();
                                clearScreen();
                                ePrint(COLOR_YELLOW "** Adicione um produto à sua lista **" COLOR_RESET "\n");
                                printf("Código do produto: %d\n",add);
                                printf("%d disponiveis.\n",stocks[fp].quantidade);
                                ePrint("Selecione a quantidade prentendida: ");
                                scanf("%d",&q);
                                fq=vq(fp,q);
                        }
                        if(fq==1) {
                                users[log].quantidade[j]=q;
                                j++;
                                clearScreen();
                                ePrint("Produto adicionado com sucesso à sua lista!\n");
                                writeUsers();
                                parseUsers();
                                enterPrompt();
                                addprod(j,log);
                        }
                }
                else {
                        clearScreen();
                        printErr("Produto não encontrado! Tente novamente!\n");
                        enterPrompt();
                        addprod(items,log);
                }
        }
}

void remprod(const int items, const int log){
        parseStock();
        clearScreen();
        int rem, rf=0, flag=0;
        ePrint(COLOR_YELLOW "** Remova um produto da sua lista **" COLOR_RESET "\n");
        ePrint("Selecione o código do produto a remover da sua lista: ");
        scanf("%d",&rem);
        if (rem > 0) {
                for (int i = 0; i < items; i++) {
                        if (users[log].buylist[i] == rem) {
                                rf=i;
                                flag=1;
                        }
                }
                if (flag == 0) {
                        clearScreen();
                        printErr("Produto não encontrado na sua lista, tente novamente!\n");
                        enterPrompt();
                        actionslista(4,log);
                }
                else if(flag==1) {
                        for (int i = rf; users[log].buylist[i]>0; i++) {
                                users[log].buylist[i]=users[log].buylist[i+1];
                                users[log].quantidade[i]=users[log].quantidade[i+1];
                        }
                        clearScreen();
                        ePrint("Produto removido com sucesso!\n");
                        writeUsers();
                        parseUsers();
                        enterPrompt();
                        actionslista(4,log);
                }
        }
        else {
                clearScreen();
                printErr("Por favor selecione um código superior a 0!\n");
                enterPrompt();
                actionslista(4,log);
        }
}

void mod(const int log) {
        parseStock();
        int m=0, e=0, nq=0, fq=0, fp=0;
        clearScreen();
        ePrint(COLOR_YELLOW "** Altere a quantidade de um produto da sua lista **" COLOR_RESET "\n");
        ePrint("Selecione o produto a modificar a quantidade: ");
        scanf("%d",&m);
        e=existe(log,m);
        if(e<0) {
                clearScreen();
                printErr("O produto não se encontra na sua lista! Tente novamente!\n");
                enterPrompt();
                actionslista(4,log);
        }
        if (e>=0) {
                fp=vp(m);
                if (fp==-2) {
                        clearScreen();
                        printErr("O produto de momento não se encontra em stock! Para efetuar a compra da sua lista, necessita de remover este produto!\n");
                        enterPrompt();
                        actionslista(4,log);
                }
                else {
                        parseStock();
                        clearScreen();
                        ePrint(COLOR_YELLOW "** Altere a quantidade de um produto da sua lista **" COLOR_RESET "\n");
                        printf("Código do produto: %d\n",m);
                        printf("%d disponiveis.\n",stocks[fp].quantidade);
                        ePrint("Selecione a quantidade prentendida: ");
                        scanf("%d",&nq);
                        while(nq<=0) {
                                parseStock();
                                clearScreen();
                                printErr("Selecionou uma quantidade igual ou inferior a 0!\n");
                                enterPrompt();
                                clearScreen();
                                ePrint(COLOR_YELLOW "** Altere a quantidade de um produto da sua lista **" COLOR_RESET "\n");
                                printf("Código do produto: %d\n",m);
                                printf("%d disponiveis.\n",stocks[fp].quantidade);
                                ePrint("Selecione a quantidade prentendida: ");
                                scanf("%d",&nq);
                        }
                        fq=vq(fp,nq);
                        while(fq==-1) {
                                parseStock();
                                clearScreen();
                                printErr("Selecionou uma quantidade superior ao stock existente!\n");
                                enterPrompt();
                                clearScreen();
                                ePrint(COLOR_YELLOW "** Altere a quantidade de um produto da sua lista **" COLOR_RESET "\n");
                                printf("Código do produto: %d\n",m);
                                printf("%d disponiveis.\n",stocks[fp].quantidade);
                                ePrint("Selecione a quantidade prentendida: ");
                                scanf("%d",&nq);
                                fq=vq(fp,nq);
                        }
                        if(fq==1) {
                                users[log].quantidade[e]=nq;
                                clearScreen();
                                ePrint("Quantidade modificada com sucesso!\n");
                                writeUsers();
                                parseUsers();
                                enterPrompt();
                                actionslista(4,log);
                        }
                }
        }
}

int existe(const int log, const int add){
        for(int i=0; i<128; i++) {
                if(users[log].buylist[i]==add) {
                        return i;
                }
        }
        return -1;
}

int vp(const int add) {
        for (int i=0; i<512; i++) {
                if(stocks[i].uid==add && stocks[i].quantidade>0)
                        return i;
                else if(stocks[i].uid==add && stocks[i].quantidade==0)
                        return -2;
        }
        return -1;
}

int vq(const int id, const int q) {
        if(q<=stocks[id].quantidade) {
                return 1;
        }
        return -1;
}
