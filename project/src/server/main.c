#include "../lib.c"
#include "menus_sv.c"
#include "methods_sv.c"
#include "users_sv.c"
#include "stocks_sv.c"
#include "actions_sv.c"

int main(){
	startupActions();
	int input = 1;
	parseUsers();
	parseStock();
	do {
		menu();
		if(scanf("%d", &input) >= 1){
			clearScreen();
			actions(input);
		}
	} while(1);

	return(0);
}
