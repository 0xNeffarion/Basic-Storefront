void sair();

void sair(){
	clearScreen();
	printf("Fechando servidor");
	int i = 0;
	for(i = 0; i < 5; i++){
		fflush(stdout);
		printf(".");
		usleep(1000 * 250);
	}
	printf("\n\n");
	exit(0);
}
