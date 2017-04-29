#include "../lib.c"
#include "libclient.h"

int main(){
	startupActions();
	parseUsers();
	parseStock();
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
