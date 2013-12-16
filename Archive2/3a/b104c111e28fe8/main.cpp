/*trabalho final de LPG
 */
#include <stdio.h>
//#include <conio.h>
#include <string.h>
#include <ctype.h>
//#include <windows.h>
#include <locale.h>
#include <time.h>

struct loginStruct{
    char usuario[10];
	char senha[20];
} login;

struct produtos{
	int cod_produto;
	char descricao[10];
	float preco;
	int quantidade;
} produto;

struct clientes{
    char cod_cliente[15];
    char nome[26];
    char endereco[21];
    char fone[9];
    char email[31];
	//cliente;
	//fornecedor;
} cliente, auxcliente;

struct notas{
    int cod_nota;
	char cod_cliente[15];
    int cod_produto;
    int quantidade;
	float preco_total;
    char data[12];
	char hora[9];
    //char estorno;
    //int tipo;
} nota, auxnota;

//funções
void consultar();
void listar();
void incluir(int);
void alterar(int);
void excluir();
void importar(int);
int cadCliente();
int getNextCod();
float calcPreco();

void inicial();
int validaOpcao(int);
void tela(int); //primeiro parametro identifica qual a tela, segundo o tipo de usuario. esta funcao conterá todas as telas do programa
int loginForm(); //Formulario de login
void cabecalhoUsu(); //funcao que mostra o usuario conectado (em cada tela irá mostrar)
void controle(int); //parametro que contém a opção do usuario. esta funcao irá direcionar o programa
void voltaInicio();
int consCliente();

int nUsu = 0;
int nLocal = 0;

int main(){
	nUsu = loginForm();

	inicial();

	printf("\n");
	return 0;
}

void inicial(){
	int nOp = 0;

	tela(1);
	printf("| Opcao: ");

	do {
		scanf("%d",&nOp);
	} while ( validaOpcao(nOp) == 1 );

	if (nOp != 5){
		controle(nOp);
	}
}

void controle(int nOp){
	int nOpcao = 0;
	char dataDe[10];
	char dataAte[10];

	switch (nOp){
		case 1:
			tela(2); //Inicio > Consultar
			printf("| Opcao: ");

			do {
				scanf("%d",&nOpcao);
			} while ( validaOpcao(nOpcao) == 1 );
			printf("| \n");

			switch (nOpcao){
				case 1:
                     tela(3);//Inicio > Consultar > Nota
					consultar(1);
					break;
				case 2:
                    tela(4);//Inicio > Consultar > Cliente
					consultar(2);
                    break;
				case 3:
					tela(5); //Inicio > Consultar > Produto
					consultar(3);
					break;

				case 4:
					inicial();
					break;
            }
        break;

		case 2:
			tela(15); //Inicio > Listar
			printf("| Opcao: ");

			do {
				scanf("%d",&nOpcao);
			} while ( validaOpcao(nOpcao) == 1 );
			printf("| \n");

			switch (nOpcao){
				case 1:
					tela(16); //Inicio > Listar > Nota
					printf("| Opcao: ");

					do {
						scanf("%d",&nOpcao);
					} while ( validaOpcao(nOpcao) == 1 );
					printf("| \n");

					if (nOpcao == 1){
						printf("| Periodo De: ");
						scanf("%s",dataDe);
						printf("| Periodo Ate: ");
						scanf("%s",dataAte);

						listar(1);
					} else {
						listar(2);
					}
					break;

				case 2:
					tela(17); //Inicio > Listar > Cliente
					listar(3);
					break;

				case 3:
					tela(18); //Inicio > Listar > Produto
					printf("| Opcao: ");

					do {
						scanf("%d",&nOpcao);
					} while ( validaOpcao(nOpcao) == 1 );
					printf("| \n");

					if (nOpcao == 1){
						listar(4);
					} else {
						listar(5);
					}
					break;

				case 4:
					inicial();
					break;
			}
			break;

		case 3:
			tela(6); //Inicio > Incluir
			printf("| Opcao: ");

			do {
				scanf("%d",&nOpcao);
			} while ( validaOpcao(nOpcao) == 1 );
			printf("| \n");

			switch (nOpcao){
				case 1:
					incluir(1);
					break;
				case 2:
					incluir(2);
					break;

				case 3:
					incluir(3);
					break;

				case 4:
					incluir(4);
					break;

				case 5:
					inicial();
					break;
				}
			break;

		case 4:
			//A função excluir() será chamada dentro de alterar(), para aproveitarmos o registro escolhido.
			tela(10); //Inicio > Alterar/Excluir
			printf("| Opcao: ");

			do {
				scanf("%d",&nOpcao);
			} while ( validaOpcao(nOpcao) == 1 );
			printf("| \n");

			switch (nOpcao){
				case 1:
					alterar(1);
					break;

				case 2:
					alterar(2);
					break;

				case 3:
					alterar(3);
					break;

				case 4:
					inicial();
					break;
				}
			break;

		case 6:
			tela(19);
			printf("| Opcao: ");

			do {
				scanf("%d",&nOpcao);
			} while ( validaOpcao(nOpcao) == 1 );
			printf("| \n");

			switch (nOpcao){
				case 1:
					importar(1);
					break;

				case 2:
					importar(2);
					break;

				case 3:
					importar(3);
					break;

				case 4:
					inicial();
					break;
			}

	}
}

void cabecalhoUsu(){
	printf("+---------------------------------------------------------------------------- \n");
	printf("| Usuario conectado: %s \n",login.usuario);
	printf("| %s  %s\n",__DATE__,__TIME__);
	printf("+---------------------------------------------------------------------------- \n");
}

int loginForm(){
	int nTipoUsu = 0;

	printf("+---------------------------------------------------------------------------- \n");
	printf("| Usuario: ");
	scanf("%s",login.usuario);

	printf("| Senha: ");
	scanf("%s",login.senha);

	//Usuário administrador = "admin"
	//Temporário até criarmos o arquivo de usuários
	if ( strcmp(login.usuario,"admin") == 0){
		nTipoUsu = 0;
	} else {
		nTipoUsu = 1;
	}

	return nTipoUsu;
}

int validaOpcao(int nOpVal){
	int nRet = 0;

	switch (nLocal){
		case 1:
			if (nUsu == 0){
				if (nOpVal != 1 && nOpVal != 2 && nOpVal != 3 && nOpVal != 4 && nOpVal != 5 && nOpVal != 6){
					nRet = 1;
				}
			} else {
				if (nOpVal != 1 && nOpVal != 2 && nOpVal != 3 && nOpVal != 5) {
					nRet = 1;
				}
			}
			break;

		case 6:
			if (nUsu == 0){
				if (nOpVal != 1 && nOpVal != 2 && nOpVal != 3 && nOpVal != 4 && nOpVal != 5){
					nRet = 1;
				}
			} else {
				if (nOpVal != 1 && nOpVal != 5){
					nRet = 1;
				}
			}
			break;

		case 19:
			if (nOpVal != 1 && nOpVal != 2 && nOpVal != 3 && nOpVal != 4){
				nRet = 1;
			}

		default:
			if (nLocal == 16 || nLocal == 18){
				if (nOpVal != 1 && nOpVal != 2){
					nRet = 1;
				}
			} else {
				if (nOpVal != 1 && nOpVal != 2 && nOpVal != 3 && nOpVal != 4){
					nRet = 1;
				}
			}
			break;

	}
	return (nRet);
}

void tela(int nTipo){

	cabecalhoUsu();
	nLocal = nTipo;

	switch (nTipo){
		case 1:
			//nLocal = 1;

			printf("| Inicio \n");
			printf("| \n");
			printf("| 1 - CONSULTAR 3 - INCLUIR");
			if (nUsu == 0){
				printf(" 4 - ALTERAR/EXCLUIR 6 - IMPORTAR \n");
			} else {
				printf("   \n");
			}
			printf("| 2 - LISTAR 5 - SAIR\n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 2:
			//nLocal = 2;

			printf("| Inicio > Consultar \n");
			printf("| \n");
			printf("| 1 - NOTA 2 - CLIENTE 3 - PRODUTO 4 - INICIO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 3:
			printf("| Inicio > Consultar > Nota \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

        case 4:
            printf("| Inicio > Consultar > Cliente \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

        case 5:
            printf("| Inicio > Consultar > Produto \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 6:
			//nLocal = 6;

			printf("| Inicio > Incluir \n");
			printf("| \n");
			printf("| 1 - NOTA ");
			if (nUsu == 0){
				printf(" 2 - USUARIO 3 - CLIENTE 4 - PRODUTO ");
			}
			printf(" 5 - INICIO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 7:
			printf("| Inicio > Incluir > Nota \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 8:
			printf("| Inicio > Incluir > Usuario \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 9:
			printf("| Inicio > Incluir > Cliente \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 10:
			//nLocal = 10;

			printf("| Inicio > Alterar/Excluir \n");
			printf("| \n");
			printf("| 1 - USUARIO 2 - PRODUTO 3 - CLIENTE 4 - INICIO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 11:
			printf("| Inicio > Alterar/Excluir > Usuario \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 12:
			printf("| Inicio > Alterar/Excluir > Produto \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 13:
			printf("| Inicio > Alterar/Excluir > Cliente \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 14:
			printf("| Inicio > Incluir > Produto \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 15:
			//nLocal = 15;

			printf("| Inicio > Listar \n");
			printf("| \n");
			printf("| 1 - NOTA 2 - CLIENTE 3 - PRODUTO 4 - INICIO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 16:
			//nLocal = 16;

			printf("| Inicio > Listar > Nota \n");
			printf("| \n");
			printf("| 1 - PERIODO 2 - TUDO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 17:
			printf("| Inicio > Listar > Cliente \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 18:
			//nLocal = 18;

			printf("| Inicio > Listar > Produto \n");
			printf("| \n");
			printf("| 1 - PRECO 2 - QUANTIDADE \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 19:
			//nLocal = 19;

			printf("| Inicio > Importar \n");
			printf("| \n");
			printf("| 1 - NOTA 2 - CLIENTE 3 - PRODUTO 4 - INICIO \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 20:
			//nLocal = 20;

			printf("| Inicio > Alterar/Excluir > Cliente \n");
			printf("| \n");
			printf("| 1 - ALTERAR 2 - EXCLUIR 3 - INICIO\n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 21:
			printf("| Inicio > Importar > Nota \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 22:
			printf("| Inicio > Importar > Cliente \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

		case 23:
			printf("| Inicio > Importar > Produto \n");
			printf("| \n");
			printf("+---------------------------------------------------------------------------- \n");
			break;

	}
}

void incluir(int nOp){
	int nCod = 0;
	int i=0;
	char mes[4], dia[3], ano[5];

	strcpy(mes, "");
	strcpy(dia, "");
	strcpy(ano, "");
	strncat(mes, __DATE__ , 3);
	strncat(dia, __DATE__ +4, 2);
	strncat(ano, __DATE__ +7, 4);

	switch (nOp){
		case 1:
			tela(7); //Inicio > Incluir > Nota

			nota.cod_nota = getNextCod();
			printf("| Codigo: %d \n",nota.cod_nota);

			printf("| Codigo Cliente: ");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(nota.cod_cliente);

			printf("| Codigo Produto: ");
			scanf("%d",&nota.cod_produto);

			printf("| Quantidade: ");
			scanf("%d",&nota.quantidade);

			printf("| Preco Total: %f \n",calcPreco());

			strcpy(mes, "");
			strcpy(dia, "");
			strcpy(ano, "");
			strncat(mes, __DATE__   , 3);
			strncat(dia, __DATE__ +4, 2);
			strncat(ano, __DATE__ +7, 4);

			printf("| Data: %s/%s/%s \n",dia,mes,ano);
			strcpy(nota.data,__DATE__);

			printf("| Hora: %s \n",__TIME__);
			strcpy(nota.hora,__TIME__);

			if (cadNota()){
				printf("teste");
			}

			voltaInicio();
			break;

		case 2:
			tela(8); //Inicio > Incluir > Usuario
			printf("| Codigo Usuario: ");
			scanf("%s",login.usuario);
			printf("| Codigo Senha: ");
			scanf("%s",login.senha);

			voltaInicio();

			break;

		case 3:
			tela(9); //Inicio > Incluir > Cliente
			printf("| Codigo do Cliente(14): ");
			strcpy(cliente.cod_cliente, "");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(cliente.cod_cliente);

			printf("| Nome do Cliente(25): ");
			strcpy(cliente.nome, "");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(cliente.nome);

			printf("| Endereco(20): ");
			strcpy(cliente.endereco, "");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(cliente.endereco);

			printf("| Telefone(8): ");
			strcpy(cliente.fone, "");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(cliente.fone);

			printf("| Email(30): ");
			strcpy(cliente.email, "");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
			gets(cliente.email);

			cadCliente();

			voltaInicio();
            break;

		case 4:
			tela(14); //Inicio > Incluir > Produto
			printf("| Codigo do Produto: ");
			scanf("%d",&produto.cod_produto);
			printf("| Descrição do Produto: ");
			scanf("%s",produto.descricao);
            printf("| Preco: ");
			scanf("%f",&produto.preco);
            printf("| Quantidade: ");
			scanf("%d",&produto.quantidade);

			voltaInicio();

			break;
        }
}

int getNextCod(){
	FILE * fp;
	int nCod = 0;

	#ifdef WIN32
	if ( (fp = fopen("../Dados/nota.db","rb") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#else
	if ( (fp = fopen("nota.db","rb") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#endif

	while (!feof(fp)) {
		fread(&auxnota,sizeof(struct notas),1,fp);
		printf("%d \n",auxnota.cod_nota);
	}
	fclose(fp);

	nCod = auxnota.cod_nota + 1;

	return nCod;
}

float calcPreco(){
	return (40.0);
}

int cadCliente(){
	FILE *fpCli;

	#ifdef WIN32
	if ( (fpCli = fopen("../Dados/cliente.db","ab") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#else
	if ( (fpCli = fopen("cliente.db","rb") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#endif

	fwrite(cliente.cod_cliente,sizeof(char)*15 ,1,fpCli);
	fwrite(cliente.nome,       sizeof(char)*26 ,1,fpCli);
	fwrite(cliente.endereco,   sizeof(char)*21 ,1,fpCli);
	fwrite(cliente.fone,       sizeof(char)*9  ,1,fpCli);
	fwrite(cliente.email,      sizeof(char)*31 ,1,fpCli);
	//fwrite("\n",               sizeof(char)    ,1,fpCli);
	fclose(fpCli);
	return 0;
}

int cadNota(){
	FILE *fp;

	#ifdef WIN32
	if ( (fp = fopen("../Dados/nota.db","ab") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#else
	if ( (fp = fopen("nota.db","ab") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#endif

	fwrite(&nota.cod_nota,    sizeof(int)     ,1,fp);
	fwrite(nota.cod_cliente,  sizeof(char)*15 ,1,fp);
	fwrite(&nota.cod_produto, sizeof(int)     ,1,fp);
	fwrite(&nota.quantidade,  sizeof(int)     ,1,fp);
	fwrite(&nota.preco_total, sizeof(float)   ,1,fp);
	fwrite(nota.data,         sizeof(char)*12 ,1,fp);
	fwrite(nota.hora,         sizeof(char)*9  ,1,fp);
	fclose(fp);

	return 0;
}

void alterar(int nOp){
	int nOpcao = 0;

	switch (nOp){
		case 1:
			tela(11); //Inicio > Alterar/Excluir > Usuario
			break;

		case 2:
			tela(12); //Inicio > Alterar/Excluir > Produto
			break;

		case 3:
			tela(13); //Inicio > Alterar/Excluir > Cliente
            printf("| Escreva o Codigo do Cliente: ");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
            gets(cliente.cod_cliente);

			if (!consCliente()){
				voltaInicio();
			} else {

				tela(20);
				printf("| \n");
				printf("| Codigo do Cliente(CPF/CNPJ): %s \n",cliente.cod_cliente);
				printf("| Nome do Cliente: %s \n",cliente.nome);
				printf("| Endereco: %s \n",cliente.endereco);
				printf("| Telefone: %s \n",cliente.fone);
				printf("| Email: %s \n",cliente.email);
				printf("| \n");
				printf("| Opcao: ");

				do {
					scanf("%d",&nOpcao);
				} while ( validaOpcao(nOpcao) == 1 );
				printf("| \n");

				switch (nOpcao){
					case 1:
						printf("ALTERAR");
						break;

					case 2:
						printf("EXCLUIR");

					case 3:
						inicial();
						break;
				}
			}
			break;
	}
}

void consultar(int codigo){
    int op =0;
    char opcao[15];

	switch (codigo){
	    case 1:
            printf("| Escreva o número da nota: ");
            scanf("%d",&op);

			printf("| \n");

            printf("| cod_nota \n");
            printf("| cod_produto \n");
            printf("| cod_cliente[15] \n");
            printf("| data[10] \n");
            printf("| hora[6] \n");
            printf("| quantidade \n");
            printf("| preco_total \n");
            printf("| estorno \n");
            printf("| tipo \n");

			voltaInicio();

            break;
        case 2:
            printf("| Escreva o Codigo do Cliente: ");
			#ifdef WIN32
			fflush(stdin);
			#else
			getchar();
			#endif
            gets(cliente.cod_cliente);

			printf("| \n");
			if (!consCliente()){
				voltaInicio();
			} else {

				printf("| Codigo do Cliente(CPF/CNPJ): %s \n",cliente.cod_cliente);
				printf("| Nome do Cliente: %s \n",cliente.nome);
				printf("| Endereco: %s \n",cliente.endereco);
				printf("| Telefone: %s \n",cliente.fone);
				printf("| Email: %s \n",cliente.email);

				voltaInicio();
			}
            break;

      case 3:
			printf("| Escreva o codigo do produto: ");
			scanf("%d",&op);

			printf("| \n");
            printf("| cod_produto \n");
            printf("| descricao[10]\n");
            printf("| Preco:\n");
            printf("| Quantidade: \n");

			voltaInicio();

			break;
        }
}

void listar(int nOp){
	FILE *fpList;
	int tam = 0;
	int i = 0;

	switch (nOp){
		case 1://Nota por periodo
			printf("| \n");
			printf("+----+----------+-------------------------+----------+-----+----+-----------+ \n");
			printf("|NOTA|PRODUTO   |CLIENTE                  |DATA      |HORA |QTD |PRECO TOTAL| \n");
			printf("+----+----------+-------------------------+----------+-----+----+-----------+ \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");

			voltaInicio();

			break;

		case 2: //Nota total
			printf("| \n");
			printf("+----+----------+-------------------------+----------+-----+----+-----------+ \n");
			printf("|NOTA|PRODUTO   |CLIENTE                  |DATA      |HORA |QTD |PRECO TOTAL| \n");
			printf("+----+----------+-------------------------+----------+-----+----+-----------+ \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");
			printf("|1234|PARAFUSO  |CARINE                   |11/11/2013|21:22|   3|      45,00| \n");

			voltaInicio();

			break;

		case 3://Cliente
			printf("| \n");
			printf("+---------------+--------------------------+---------+ \n");
			printf("|CODIGO         |CLIENTE                   |TELEFONE | \n");
			printf("+---------------+--------------------------+---------+ \n");

			#ifdef WIN32
			if ( (fpList = fopen("../Dados/cliente.db","rb") ) == NULL ){
				printf("arquivo não pode ser aberto \n");
				break;
			}
			#else
			if ( (fpList = fopen("cliente.db","rb") ) == NULL ){
				printf("arquivo não pode ser aberto \n");
				break;
			}
			#endif

			 do {
				strcpy(auxcliente.cod_cliente, "");
				strcpy(auxcliente.nome, "");
				strcpy(auxcliente.fone, "");

				fread(&auxcliente,sizeof(struct clientes),1,fpList);

				tam = strlen(auxcliente.cod_cliente);
				if (tam != 0){
					printf("|%s ",auxcliente.cod_cliente);

					if (tam < 14){
						tam = 14 - tam;

						for (i=0;i<tam;i++){
							printf(" ");
						}
					}
				}

				tam = strlen(auxcliente.nome);
				if (tam != 0){
					printf("|%s ",auxcliente.nome);

					if (tam < 25){
						tam = 25 - tam;

						for (i=0;i<tam;i++){
							printf(" ");
						}
					}
				}

				tam = strlen(auxcliente.fone);
				if (tam != 0){
					printf("|%s ",auxcliente.fone);

					if (tam < 8){
						tam = 8 - tam;

						for (i=0;i<tam;i++){
							printf(" ");
						}
					}
					printf("| \n");
				}

			} while (!feof(fpList));
			printf("+---------------+--------------------------+---------+ \n");
			printf("| \n");

			fclose(fpList);

			voltaInicio();

			break;

		case 4:
			printf("| \n");
			printf("+----+----------+--------+----+ \n");
			printf("|COD |DESCRICAO |PRECO   |QTD |\n");
			printf("+----+----------+--------+----+ \n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");

			voltaInicio();

			break;

		case 5:
			printf("| \n");
			printf("+----+----------+--------+----+ \n");
			printf("|COD |DESCRICAO |PRECO   |QTD |\n");
			printf("+----+----------+--------+----+ \n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");
			printf("|1234|CARINE    |   45,00|    |\n");

			voltaInicio();

			break;
	}
}

void excluir(){
	printf("EXCLUIR");

}

void voltaInicio(){
	char voltar;

	printf("Precione V para voltar ao inicio: ");

	do {
		scanf("%c",&voltar);
	} while (voltar != 'v');

	inicial();
}

int consCliente(){
	FILE * fp;
	int flag = 0;
	int i=0;

	#ifdef WIN32
	if ( (fp = fopen("../Dados/cliente.db","rb") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#else
	if ( (fp = fopen("cliente.db","rb") ) == NULL ){
		printf("arquivo não pode ser aberto \n");
	}
	#endif

	while (flag == 0 ) {

		fread(&auxcliente,sizeof(struct clientes),1,fp);

		if ( strcmp(auxcliente.cod_cliente,cliente.cod_cliente) == 0 ){
			flag = 1;
			cliente = auxcliente;
		}

		if (feof(fp)){
			printf("| Cliente nao encontrado! \n");
			flag = 1;
			return 0;
		}
	}

	return 1;
	fclose(fp);
}

void importar(int nOpcao){
	char dir[50];
	FILE * fp;
	struct notas impNota;
	struct clientes impCliente;
	struct produtos impProduto;
	char * cont;
	int tam = 0;
	char cha;
	int i = 0;

	printf("| Informe o diretorio do arquivo: ");
	fflush(stdin);
	gets(dir);

	if ( (fp = fopen(dir,"r") ) == NULL ){
		printf("| Arquivo nao encontrado \n");
		printf("| \n");

		voltaInicio();
	}

	while (!feof(fp)){

		switch (nOpcao){
			case 1:
				//fread(&impNota,sizeof(struct notas)+5,1,fp);
				break;

			case 2:

				cont = (char*) malloc(30 * sizeof(char));

				for (i=0;i<5;i++){
					strcpy(cont, "");

					do {
						fgets(&cha,2,fp);

						if (cha != '|'){
							strcat(cont,&cha);
						}

					} while(  cha != '|');

					switch (i){
						case 0:
							strcpy(cliente.cod_cliente,cont);
							break;
						case 1:
							strcpy(cliente.nome,cont);
							break;
						case 2:
							strcpy(cliente.endereco,cont);
							break;
						case 3:
							strcpy(cliente.fone,cont);
							break;
						case 4:
							strcpy(cliente.email,cont);
							break;
					}
				}

				cadCliente();
				break;

			case 3:
				//fread(&impProduto,sizeof(struct produtos),1,fp);
				break;
		}
	}

	printf("| Arquivo importado com sucesso! \n");
	printf("| \n");
	voltaInicio();
}