#include "../lib.c"
#include "libclient.h"

int main(){
	startupActions();
	parseUsers();
	parseStock();
	parseClientStats();
	int opt = 0, log = -1;
	log = login();
	if(log > -1){
		ePrint("Login efetuado com sucesso! Seja bem-vindo ");
		printf("%s!\n",users[log].username);
		usleep(1000 * 1000);
		do {
			clearScreen();
			menu(log);
			if(scanf("%d", &opt) > 0){
				actions(opt, log);
			}
		} while(1);
	}
	return(0);
}
