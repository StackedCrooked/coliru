// Para que o arquivo seja executado de maneira correta, copie as pastas "Teste" e "RI" para o caminho C: de seu computador.


#include <iostream>
#include <fstream>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

class busca
{
    private: struct arquivoPalavra
             {
                  int posAtual; //variavel que arruma a posicao na funcao.
                  char nomeArquivo[30]; //arquivo que contem a palavra.
                  int frequencia; // Quantidade de vezes que a palavra aparece.
                  arquivoPalavra *prox;
             };

             struct listaInvertidaPalavra
             {
                  char Palavra[30]; //palavra do arquivo.
                  listaInvertidaPalavra *proxPalavra;
                  arquivoPalavra *proxArqPalavra, *fimArqPalavra;
             };

             listaInvertidaPalavra *inicioLI, *fimLI;

    public:  busca();
             ~busca();
             void selecionarPasta();
             void gerarIndice();
             void inserirListaInv(char palavra[30], char nomeArquivo[30]);
             void pesquisar();
             void mostrar_Tudo_LI();
};

busca:: busca()
{
    inicioLI = fimLI = NULL;
}

busca:: ~busca()
{
    //destrutora.
}

void busca:: selecionarPasta()
{
    char caminhoPasta[30];
    cout <<"\nA busca esta sendo feita na pasta: c:\\Teste"<<endl;

    system("dir c:\\Teste\\*.txt /b > c:\\RI\\arquivoDeTexto.txt"); // Arquivos de  texto.
    system("dir c:\\Teste\\*.jpg /b > c:\\RI\\arquivoDeImagem.txt"); // Arquivos do tipo imagem.
    system("dir c:\\Teste\\*.gif /b > c:\\RI\\arquivoDeImagem.txt"); // Arquivos do tipo imagem.

    gerarIndice();
}

void busca:: gerarIndice() // Gerar a Lista Invertida.
{
    fstream arq; // Abrir o arquivo a ser lido.
    fstream arq1; // Abri o arquivo para armazenar informações de texto.
    fstream arq2; // Abri o arquivo para armazenar informações de imagem.
    char palavra[30] = {0};
    char endereco[50] = {0};
    char diretorio[200], linha2[200], linha3[200];
    int i=0, j=0, k=0;

    arq.open("c:\\RI\\arquivoDeTexto.txt", ios::in); //abrir arquivo como leitura
    arq.seekg(0, ios::beg); //ponteiro de leitura aponta para o inicio.

    while(arq.getline(diretorio, 100, '\n')) // Pega o nome do arquivo.
    {
        strcpy(endereco, "c:\\teste\\");
        strcat(endereco, diretorio);
        arq1.open(endereco, ios::in);
        arq1.seekg(0, ios::beg); //ponteiro de leitura aponta para o inicio.

        while(arq1.getline(linha2, 100, '\n')) // Loop para ir pegando as linhas de texto do arquivo.
        {
            i = 0; // Variável para percorrer a linha2.
            j = 0; // Variável para percorrer a palavra.

            while((linha2[i] != 0) && (i <= strlen(linha2))) // Loop para pegar os caracteres até o final da linha2.
            {
                if (linha2[i] != ' ') // Se linha2[i] for diferente de espaço, pega o caractere e adiciona na palavra.
                {
                    palavra[j] = linha2[i];
                    j++;
                }
                if((linha2[i] == ' ') || (i == (strlen(linha2) - 1))) // Se linha2[i] for igual a espaço ou chegar no final da linha, adiciona a palavra na lista invertida
                {
                    inserirListaInv(palavra, diretorio); // Inserir a palavra na lista invertida com o seu reespectivo diretório.
                    for(int p=0; p<30; p++) //apagar palavra
                    {
                        palavra[p] = '\0';
                    }
                    j = 0;
                }
                i++; //andar pelas letras na linha2
            }
            for (int p=0; p<30; p++) //apagar palavra
            {
                palavra[p] = '\0';
            }
        }
        arq1.close(); // Fecha o arquivo
    }
    arq.close(); // Fecha o arquivo
    arq1.close(); // Fecha o arquivo

    arq2.open("c:\\RI\\arquivoDeImagem.txt", ios::in); //abrir arquivo como leitura
    arq2.seekg(0, ios::beg); //ponteiro de leitura aponta para o inicio.

    while(arq2.getline(linha3, 100, '\n')) // Pega o nome da imagem.
    {
        for (int p=0; p<30; p++) //apagar palavra
        {
            palavra[p] = '\0';
        }
        i = 0; // percorrer a linha3.
        j = 0; // percorrer a palavra.

        while (linha3[i] != '.')
        {
            if (linha3[i] != ' ') // Se a linha3[i] for diferente de espaço.
            {
                palavra[j] = linha3[i];
                j++;
            }
            if((linha3[i] == ' ') || (linha3[i+1] == '.') || (i == (strlen(linha2) - 1)))
            {
                inserirListaInv(palavra, linha3);
                for(int p=0; p<30; p++) //apagar palavra
                {
                    palavra[p] = '\0';
                }
                j = 0;
            }
            i++; //andar pelas letras na linha3
        }
    }
    arq2.close();
    cout << endl;
}

// Inserção na Lista Invertida.
void busca:: inserirListaInv(char palavra[30], char nomeArquivo[30])
{
    if (inicioLI == NULL)
    {   //inserir primeira palavra.
        inicioLI = new(listaInvertidaPalavra);
        fimLI = inicioLI;
        fimLI->proxPalavra = NULL;
        strcpy(fimLI->Palavra, palavra);

    //
        arquivoPalavra *novoAP = new (arquivoPalavra);
        novoAP->prox = NULL;
        strcpy(novoAP->nomeArquivo, nomeArquivo);
        novoAP->frequencia = 1;

        fimLI->proxArqPalavra = novoAP;
        fimLI->fimArqPalavra = novoAP;
    }
    else
    {
        if (strcmpi(palavra, fimLI->Palavra) >= 0)
        { //inserir ou atualizar ultima posicao.
            if (strcmpi(palavra, fimLI->Palavra) == 0)
            { //so atualiza
                arquivoPalavra *percorrer = fimLI->proxArqPalavra;
                while (percorrer != NULL)
                {
                    if (strcmpi(percorrer->nomeArquivo, nomeArquivo) == 0)
                    {
                        percorrer->frequencia = percorrer->frequencia + 1;
                        break;
                    }
                    percorrer = percorrer->prox;
                }
                if (percorrer == NULL)
                {
                    arquivoPalavra *novoAP = new (arquivoPalavra);
                    novoAP->prox = NULL;
                    strcpy(novoAP->nomeArquivo, nomeArquivo);
                    novoAP->frequencia = 1;

                    fimLI->fimArqPalavra = novoAP;
                }
            }
            else
            { //inserir
                listaInvertidaPalavra *novoLIP = new (listaInvertidaPalavra);
                fimLI->proxPalavra = novoLIP;
                fimLI = novoLIP;

                fimLI->proxPalavra = NULL;
                strcpy(fimLI->Palavra, palavra);

                arquivoPalavra *novoAP = new (arquivoPalavra);
                novoAP->prox = NULL;
                strcpy(novoAP->nomeArquivo, nomeArquivo);
                novoAP->frequencia = 1;

                fimLI->proxArqPalavra = novoAP;
                fimLI->fimArqPalavra = novoAP;
            }
        }
        else
        {
            if (strcmpi(palavra, inicioLI->Palavra) <= 0)
            { //inserir ou atualizar primeira posicao.
                if (strcmpi(palavra, inicioLI->Palavra) == 0)
                { //so atualiza
                    arquivoPalavra *percorrer = inicioLI->proxArqPalavra;
                    while (percorrer != NULL)
                    {
                        if (strcmpi(percorrer->nomeArquivo, nomeArquivo) == 0)
                        {
                            percorrer->frequencia = percorrer->frequencia + 1;
                            break;
                        }
                        percorrer = percorrer->prox;
                    }

                    if (percorrer == NULL)
                    {
                        arquivoPalavra *novoAP = new (arquivoPalavra);
                        novoAP->prox = NULL;
                        strcpy(novoAP->nomeArquivo, nomeArquivo);
                        novoAP->frequencia = 1;

                        inicioLI->fimArqPalavra = novoAP;
                    }
                }
                else
                { //inserir
                    listaInvertidaPalavra *novoLIP = new (listaInvertidaPalavra);
                    novoLIP->proxPalavra = inicioLI;
                    strcpy(novoLIP->Palavra, palavra);

                    inicioLI = novoLIP;

                    arquivoPalavra *novoAP = new (arquivoPalavra);
                    novoAP->prox = NULL;
                    strcpy(novoAP->nomeArquivo, nomeArquivo);
                    novoAP->frequencia = 1;

                    inicioLI->proxArqPalavra = novoAP;
                    inicioLI->fimArqPalavra = novoAP;
                }
            }
            else
            { //inserir no meio.
                listaInvertidaPalavra *aux1, *aux2;
                aux1 = inicioLI;
                aux2 = inicioLI->proxPalavra;

                while(aux1 != NULL)
                {
                    if (strcmpi(palavra, aux1->Palavra) == 0)
                    { //atualizar

                        arquivoPalavra *percorrer = aux1->proxArqPalavra;

                        while(percorrer != NULL)
                        {
                            if (strcmpi(percorrer->nomeArquivo, nomeArquivo) == 0)
                            {
                                percorrer->frequencia = percorrer->frequencia + 1;
                                break;
                            }
                            percorrer = percorrer->prox;
                        }

                        if (percorrer == NULL)
                        {
                            arquivoPalavra *novoAP = new (arquivoPalavra);

                            novoAP->prox = NULL;
                            strcpy(novoAP->nomeArquivo, nomeArquivo);
                            novoAP->frequencia = 1;

                            aux1->fimArqPalavra->prox = novoAP;
                            aux1->fimArqPalavra = novoAP;
                        }

                        break;
                    }

                    if(strcmpi(palavra, aux2->Palavra) < 0)
                    { //inserir
                        listaInvertidaPalavra *novoLIP = new (listaInvertidaPalavra);
                        strcpy(novoLIP->Palavra, palavra);
                        novoLIP->proxPalavra = aux2;

                        arquivoPalavra *novoAP = new (arquivoPalavra);
                        novoAP->prox = NULL;
                        strcpy(novoAP->nomeArquivo, nomeArquivo);
                        novoAP->frequencia = 1;

                        novoLIP->proxArqPalavra = novoAP;
                        novoLIP->fimArqPalavra = novoAP;

                        aux1->proxPalavra = novoLIP;
                        break;
                    }

                    aux1 = aux1->proxPalavra;
                    aux2 = aux2->proxPalavra;
                }

                aux1 = aux2 = NULL;
                delete(aux1);
                delete(aux2);
            }
        }
    }
}

void busca:: pesquisar()
{
    char procuraPalavra[30];
    bool encontrei = false;

    cout <<"Digite a palavra ou imagem que deseja pesquisar: ";
    fflush(stdin);
    gets(procuraPalavra);
    cout <<endl;

    listaInvertidaPalavra *aux1;
    arquivoPalavra *aux2;
    aux1 = inicioLI;

    //andar na LI
    while (aux1 != NULL)
    {
        if(strcmpi(procuraPalavra, aux1->Palavra) == 0)
        {
            aux2 = aux1->proxArqPalavra;
            while (aux2 != NULL)
            {
                cout << "Palavra presente no arquivo "<< aux2->nomeArquivo;
                if(aux2->frequencia > 1)
                {
                    cout << " " << aux2->frequencia << " vezes. " <<endl;
                }
                else
                {
                    cout << " " << aux2->frequencia << " vez. " <<endl;
                }
                aux2 = aux2->prox;
            }
            encontrei = true;
        }
        aux1 = aux1->proxPalavra;
    }

    if(encontrei==false)
    {
        cout << "Nao foram encontradas palavras com o nome >> " << procuraPalavra << " <<"<<endl;
    }
}

void busca::mostrar_Tudo_LI()
{
    cout << "\n\t\t\tMOSTRAR TUDO LI";
    listaInvertidaPalavra *auxMostrar = inicioLI;

    while (auxMostrar != NULL)
    {
        cout << "\n\n Palavra: " << auxMostrar->Palavra;
        auxMostrar = auxMostrar->proxPalavra;
    }
    cout <<endl<<endl;
    system("PAUSE");
}

main()
{
    busca obj;

    int opcao=0;

    cout <<"\n ---------------------------------------------------------------------------";
    cout <<"\n|                              Nome?                                        |";
    cout <<"\n|                                                                           |";
    cout <<"\n| Disciplina: Recuperacao da Informacao                                     |";
    cout <<"\n| Professor: Alisson                                                        |";
    cout <<"\n|                                                                           |";
    cout <<"\n|                                                                           |";
    cout <<"\n| Participantes: Emerson, Ronaldo, Diego e Fernanda                         |";
    cout <<"\n ---------------------------------------------------------------------------";
    cout <<"\n\nTecle ENTER para continuar...";
    getch();

    do
    {
        system("cls");

        cout <<"\t\t>>> RECUPERANDO INFORMACOES <<<"<<endl;

        cout <<"\n1  -  Selecionar pasta para busca";
        cout <<"\n2  -  Pesquisar arquivos";
        cout <<"\n3  -  Mostrar todos";
        cout <<"\n4  -  Sair\n"<<endl;

        cout <<"\nDigite a opcao desejada: ";
        cin >>opcao;

        system("cls");

        switch(opcao)
        {
            case 1: cout<<"\t\tSELECIONAR PASTA PARA BUSCA\n\n";
                    obj.selecionarPasta();
                    cout<<"\nBusca executada com sucesso!";
                    getch();
                    break;

            case 2: cout <<"\t\tPESQUISAR ARQUIVOS\n\n";
                    obj.pesquisar();
                    getch();
                    break;

            case 3: cout <<"\t\tMOSTRAR TODAS PALAVRAS\n\n";
                    obj.mostrar_Tudo_LI();
                    getch();
                    break;

            default:cout <<"\nDigite uma opcao valida!";
                    getch();
        }
    } while(opcao!=4);
}
