# ProjLabc
Conteúdo deste Readme:
*Introdução
*Requerimentos
*Instalação
*Execução
*Documentação extra

- Introdução:
Este projeto foi criado por André Moreira Pacheco (up201505089@fc.up.pt) e Vasco Serrano (up201503010@fc.up.pt) no âmbito da unidade curricular de Laboratório de Computadores. O mesmo consiste no desenvolvimento de um sistema de controlo de um supermercado e tem por base 2 programas, o Servidor (Supermercado) e Cliente.

- Requerimentos:
Para executar os 2 programas (Servidor e Cliente) é necessário o acesso a um terminal do Linux.

- Instalação:
Para instalar os 2 programas basta copiar a pasta “project” para um diretório à sua escolha.

- Execução:
Para executar tanto o Servidor como o Cliente, deverá aceder à pasta “project” que copiou para o diretório à sua escolha. Posto isto, o executável do Servidor (SUPServidor) encontra-se na pasta “project/src/server” e do Cliente (SUPCliente) encontra-se na pasta “project/src/client”.

- Documentação extra:
O código comum ao Servidor e Cliente encontra-se na pasta “src”, o código apenas do Servidor, poderá ser encontrado na pasta “project/src/server” e o do Cliente na pasta “project/src/client”. 
Os ficheiros que servirão para guardar os dados de ambos os programas, terão a extensão .data e poderão ser encontrados no seu diretório “Home/labc_sm_data”.
Para efetuar o login como gestor no Servidor, deverá usar como username “gestor” e password “admin”.
Só conseguirá fazer login no Cliente, após criar um utilizador no Servidor e caso execute o Cliente antes de criar o utilizador, irá ser apresentado um erro no login.
Para efetuar a compra da lista do utilizador que efetuou o login, será necessário colocar como input “sim”, quando for apresentada a mensagem “Prosseguir com a compra?”. Caso haja duas ou mais compras ao mesmo tempo do mesmo produto e o stock não seja suficiente, será apresentado um erro ao(s) utilizador(es) que não conseguiram efetuar a compra e o(s) mesmo(s) terão que alterar a sua lista de compras. 
Na Lista de Compras serão apresentados todos os itens adicionados à mesma (pela ordem que foram adicionados), bem como a sua quantidade e se estes encontram-se em stock. Caso haja uma compra de um dos produtos adicionados à lista e rutura de stock, o utilizador poderá remover esse produto da sua lista ou caso haja uma compra de algumas unidades de um desses produtos e o stock existente é menor ao da lista, o utilizador poderá modificar a quantidade do produto da sua lista.
