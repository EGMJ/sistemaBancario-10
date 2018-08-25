#include "base.h"
#include <stdbool.h>	//Para Usar bool vars;
#define TUSERS 3

	//-- Estrutura de dados	
	typedef struct user{
		int chave;
		int senha;
		char nome[50];
		double saldo;
		struct user *suc; //Var que recebe estrutura
	}conta; //no

	//-- Var's
	conta *listausers[TUSERS], *ap, *apaux, *aptransf;
	
	bool find;
	bool IsLogged = false;
	
	//-- Var temporarias
	int i, endpri, chave, keysize;
	char  schave[6];
	char m, temppass1, temppass2[20];
	
	//-- Prot's
	char menu(void);
	int hash(int);
	void UserMenu(conta *ap);
	char UserLogMenu(void);
	int stringcount(char *);
	void transAni(void);

main(){
	srand(time(NULL));
	local();
	for(;;){
		keysize = 0;
				//----------- MENU PRINCIPAL -------------------
		switch(menu()){
			case '1': //----------- CRIANDO CONTA -------------------
				clear;
				//---
				while(keysize < 4){//Repete enquanto o tamanho da chave for inválido
					printf("Número da Conta: ");
					flush;
					gets(schave);
					keysize = stringcount(schave);
					if(keysize < 4 && keysize < 6){ // vereficando nº da conta
						printf("O número da conta está Inválido...\n");		
					}
				}
				endpri = hash(chave);
				if(listausers[endpri] == NULL){
					listausers[endpri] = (conta *)malloc(1*sizeof(conta));
					ap = listausers[endpri];
					int temp;
					printf("Titular: ");
					flush;
					gets(ap->nome);
					printf("Senha: ");
					for(i=0;i<10;i++){
						temppass1 = _getch();
						if(temppass1 == 13){
							ap->senha = atoi(temppass2);
							break;
						}
						putchar('*');
						temppass2[i] = temppass1;
					}					
					temp = rand()%1000;
					ap->saldo = (float)temp; //
					puts("\nConta criada com sucesso..\n");
				}
	 			else{
					ap = (conta *)malloc(1*sizeof(conta));
					(*apaux).suc = ap;
				}
				(*ap).chave = chave;
				(*ap).suc = NULL;				

				//---
				getch();
				clear;
				break;
			case '2'://----------- CONSULTANDO CONTA -------------------				
				clear;
				//---
					printf("Digite o Numero da conta: ");
					flush;
					gets(schave);
					keysize = stringcount(schave);
					if(keysize < 4 && keysize > 6){
						printf("O número da conta está Inválido...\n");		
					}
					endpri = hash(chave);
					find = false;
					ap = listausers[endpri];
					if(ap != NULL){
						while((!find) && (ap != NULL)){
							if((*ap).chave == chave){
								find = true;
							}
							else{
								apaux = ap;
								ap = (*ap).suc;
							}
						}
					}
					if(find == true){
						printf("\n\n ===> Usuário Encontrado\n");
						UserMenu(ap);
					}
					else{
						printf("\nConta Indisponível.. \n\n");
					}
				//--
				getch();
				clear;
				break;
			case '0':
				puts("Saindo...");
				exit(1);
				break;
			default:
				printf("Opção inválida...");
				//---
				getch();
				clear;
				break;
		}
	}
	/* Reexibir
	for(;;){
		clear;
		system ("color 0F"); //fundo preto e letras brancas
		for(i = 0; i < TUSERS; i++){
			ap = listausers[i];
			printf("\nListade Users[%i]: ",(i + 1));
			while (ap != NULL){
				printf(" %i -->", (*ap).chave);
				ap = (*ap).suc;
			}
		}
		puts("\n");

	}
	*/
}

int stringcount(char *x){//Valida o Código digitado...
	keysize = 0;
	char temp[6];
	for(i=0;i<6;i++){
		if(x[i] == '\0'){
			break;
		}
		temp[i] = x[i];
		keysize+=1;
	}
	chave = atoi(temp);
	return keysize;
}

void UserMenu(conta *ap){
	clear;
	int _pass;
	double _value;
	printf("Senha: ");
	
	for(i=0;i<10;i++){
		temppass1 = _getch();
		if(temppass1 == 13){
			_pass = atoi(temppass2);
		break;
		}
		putchar('*');
		temppass2[i] = temppass1;
	}
	IsLogged = true;
	double value;
	clear;
	if(_pass != ap->senha){
		IsLogged = false;
		printf("Senha Inválida!\n");
		//printf("\nRetornando para o menu principal\n");
	}
	while(IsLogged == true){                   
		printf("Número da Conta: %i\n", ap->chave);
		printf("Titular: %s\n", ap->nome);
		printf("Saldo: R$ %.2lf", ap->saldo);
		switch(UserLogMenu()){				//----------------------------------------  MENU SEGUNDARIO ------------
			case '1':		// -------  Saque
				clear;
				printf("Valor para sacar R$: ");
				scanf("%lf", &value);
				if(value>ap->saldo){
					printf("\n\nSaldo em conta insuficiente para esse saque...\n");
				}
				else{
					ap->saldo -= value;
					printf("\nFoi sacado R$ %.2lf da sua conta.\nSeu saldo atual é de R$ %.2lf\n", value, ap->saldo);
				}
				getch();
				clear;
				break;
			case '2':	// ------  Depositos
				clear;
					printf("Valor do Depósito R$: ");
					scanf("%lf", &value);
					ap->saldo += value;
					printf("\nFoi depositado R$ %.2lf na sua conta.\nSeu saldo atual é de R$ %.2lf", value, ap->saldo);
				clear;
				break;
			case '3':   // ------------   Transferencias
				clear;
				printf("Saldo em conta: %.2lf\n", ap->saldo);
				printf("Conta para transferir: ");
				//-- Buscar Conta
				flush;
				gets(schave);
				keysize = stringcount(schave);
				if(keysize < 4 && keysize > 6){ // -------
					printf("O número da conta está Inválido...\n\n");		
				}
				else{
					endpri = hash(chave);
					aptransf = listausers[endpri];
					if(aptransf != NULL){
						if((*aptransf).chave == chave){
							printf("Valor: R$ ");
							scanf("%lf", &_value);
							if(_value > ap->saldo){
								printf("\nOpaa!! Seu saldo é Insuficientes para realizar está transferência.. \n");
							}
							else{
								aptransf->saldo += _value;
								ap->saldo -= _value;
								transAni();
								printf("\nTransferência realizada com sucesso\n");
								//printf("\nFoi transferido R$ %.2lf da sua conta.\nSeu saldo atual é de R$ %.2lf", _value, ap->saldo);
							}
						}
						else{
							printf("Ops!! Conta não encontrada..\n");
						}
					}
				}
				//--  End;
				
				getch();
				clear;
				break;
			case '0':
				clear;
				IsLogged = false;
				break;
			default:
				printf("Opção Inválida.\n");
				getch();
				clear;
				break;
		}
	}
	printf("Encerrando..\n");
}

char menu(){ // ---------------  APRESENTAÇÃO DO MENU PRINCIPAL 
    puts("\n\n\t1 - Abrir Conta");
    puts("\t2 - Consultar Conta");
    puts("\t0 - Sair");
    printf("\n\tOpção: ");
    m = getch();
    return m;
}

char UserLogMenu(){		// ---------------  APRESENTAÇÃO DO MENU SEGUNDARIO
    puts("\n\n");
    puts("\t1 - Saque");
    puts("\t2 - Déposito");
    puts("\t3 - Transferências");
    puts("\t0 - Sair");
    printf("\nOpção: ");
    m = getch();
    return m;
}


void transAni(){
	for(i=0;i<5;i++){
		printf("=");
		//sleep(1);
	}
	printf(">");	
}
// ---------------- ** ESTRUTURA HASHING ** -----------------
int hash(int chave){
	return(chave %TUSERS);
}

