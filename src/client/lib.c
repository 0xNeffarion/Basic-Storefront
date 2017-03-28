#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <termios.h>

// CONST
const char dataComp[12] = "03/06/2016";
const char build[4] = "0.1";
const int MaxLen = 30;
const char dataUser[] = "../data/users.dat";
const char onlineUsers[] = "../data/online.dat";
const int MaxBuffer = 1024;
const int UPS = 60;
const char delim[2] = ";";
const char delim2[4] = "[#]";
const char mainFifo1[] = "/tmp/lbFifo_ServerToClient_";
const char mainFifo2[] = "/tmp/lbFifo_ClientToServer_";
const char fifoGeralPath[] = "/tmp/lbFifo_geral";

// VAR
int ServerToClient;
int ClientToServer;
int fifoGeral;

void ePrint(char *text, float speed){
    int i = 0;
    int len = strlen(text);
    while(text[i] != '\0'){
        printf("%c", (text[i]));
        fflush(stdout);
        usleep(1000*45/speed);
        i++;
    }
}

void ClearScreen(){
    printf("\033[2J\033[1;1H");
}

int Limite(char txt[]){
    if((strlen(txt) > MaxLen))
        return 0;
    else
        return 1;
}

void FillArray(int *data, int size, int value){
    int i = 0;
    for(i = 0; i < size; i++){
        data[i] = value;
    }
}

int TotalUsers(){
    FILE *fi = fopen(dataUser, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineNumber = 0;
    while (fgets(line, line_size, fi) != NULL)  { 
         lineNumber++;
    }
    free(line);
    fclose(fi);
    return lineNumber;
}

int IsPasswordValid_User(char* user, char* password){
    FILE *fi = fopen(dataUser, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    
    int isValid = 0;
    while (fgets(line, line_size, fi) != NULL)  { 
	     char *token;
	     char *token2;
	     token = strtok(line, delim);
	     token2 = strtok(NULL, delim);
	     token2[strlen(token2)-1] = 0;
	     if(strcmp(token,user) == 0){
            if(strcmp(token2,password) == 0){
                isValid = 1;
                break;
            }
            else
            {
				isValid = 0;
                break;
            }
            
		 }    
    }
    free(line);
	fclose(fi);
    return isValid;
}

int IsPasswordValid_ID(int id, char *password){
    FILE *fi = fopen(dataUser, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineNumber = 0;
    int isValid = 0;
    while (fgets(line, line_size, fi) != NULL)  { 
	     char *token;
	     char *token2;
	     token = strtok(line, delim);
	     token2 = strtok(NULL, delim);
	     token2[strlen(token2)-1] = 0;
	     if(lineNumber == id){
            if(strcmp(token2,password) == 0){
                isValid = 1;
                break;
            }
            else
            {
				isValid = 0;
                break;
            }
            
		 }
		lineNumber++;		 
    }
    free(line);
	fclose(fi);
	
    return isValid;
}

char *GetUserNickname(int id){
    FILE *fi = fopen(dataUser, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineNumber = 0;
	char* nick = malloc(35);
    while (fgets(line, line_size, fi) != NULL)  { 
	     char *token;
	     token = strtok(line, delim);
	     if(lineNumber == id){
			 nick = token;
			 break;
		 }
	     lineNumber++;
    }
    
    free(line);
	fclose(fi);
	return nick;
}

int GetUserId(char* username){
    FILE *fi = fopen(dataUser, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int contin = 1;	
    int lineNumber = 0;
    while (fgets(line, line_size, fi) != NULL)  { 
	     char *token;
	     token = strtok(line, delim);
	     if(strcmp(token,username) == 0){
		     contin = 0;
		     break;
	     }
	     lineNumber++;
    }
    
    free(line);
	fclose(fi);
	
    if(contin == 0){
        return lineNumber;
    }else{
        return -1;
    }
}

int *GetOnlineUsers(){
	FILE *fs = fopen(onlineUsers, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineNumber = 0;

    while (fgets(line, line_size, fs) != NULL)  { 
	     lineNumber++; 
    }
	fclose(fs);
	
    int usrsOn[lineNumber+1];
    int z = 0;
    for(z = 0;z<lineNumber;z++){
        usrsOn[z] = -1;
    }
    
	FILE *fs2 = fopen(onlineUsers, "r");
	char* line2 = malloc(line_size);
	int lineNumber2 = 0;
	while (fgets(line2, line_size, fs2) != NULL)  { 
		 usrsOn[lineNumber2] = atoi(line2);
	     lineNumber2++; 
    }
	fclose(fs2);
	return usrsOn;
} 

void OnlineUsers(){
	FILE *fs = fopen(onlineUsers, "r");
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineNumber = 0;
    printf("Lista de utilizadores online:\n");
    while (fgets(line, line_size, fs) != NULL)  { 
		 char nick[35];
		 char *str = GetUserNickname(lineNumber);
		 strcpy(nick,str);
	     printf("%d - %s\n", lineNumber, nick);
	     lineNumber++;
		 free(str);
    }
	fclose(fs);
}

void CriarUser(){
    ClearScreen();
	char nome[30];
	char password[30];
	FILE *fi = fopen(dataUser, "r");
	int contin = 1;
	
	while(1){      
		printf("Insira o nome de utilizador [Max. 30 caracteres]:\n");
		scanf("%s", nome);
		char *str = getpass("Insira a password [Max. 30 caracteres]: ");
		strcpy(password,str);
		
		int usrExists = GetUserId(nome);
		
		if(usrExists != -1){
			printf("\nErro! O nome de utilizador que inseriu ja esta em uso.\n");
			continue;
			
		}else{
			FILE *fa = fopen(dataUser, "a");
			fprintf(fa,"%s;%s\n",nome,password);
			fclose(fa);
			printf("Utilizador %s registado com sucesso!\n\n", nome);
			break;
		}
	}
  
}

void ChangePassword(char myUser[]){
	ClearScreen();
	char password[30];
	char npassword[30];
	printf("Insira a password actual: ");
    char *str = getpass("");
    strcpy(password,str);
	int suc = IsPasswordValid_User(myUser, password);
	FILE *fo = fopen(dataUser, "r");
	FILE *fw = fopen("../data/users_temp.dat", "a+");
	if(suc==1){
		char *str2 = getpass("Insira a password nova: ");
		strcpy(npassword,str2);
        const size_t line_size = 300;
        char* line = malloc(line_size);

        while (fgets(line, line_size, fo) != NULL){ 
        char *token;
        char buff[65];
        strcpy(buff,line);
        token = strtok(line, delim);
            if(strcmp(token,myUser) == 0){
                fprintf(fw, "%s;%s\n",token,npassword);
            }else{
                fprintf(fw, "%s",buff);  
            }
        }
        free(line);
        fclose(fo);
		fclose(fw);
		
		unlink(dataUser);
		if(rename("../data/users_temp.dat",dataUser) == 0){
			ClearScreen();
			printf("Password foi editada com sucesso!\n");
		}
		
		
	}
	else{
		printf("Password incorreta!\n\n");
	}	
}
