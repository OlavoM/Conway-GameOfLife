/*
Jogo da vida de Conway
Olavo M
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define TAM 15

int estaVivo(int x) 
{
    if (x == 1) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Preenche a matriz com 0 (mortos)
void zerarMatriz(int matriz[][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            matriz[i][j] = 0;
        }
    }
}

// Imprime a matriz com seus indices
void imprimirMatriz(int matriz[][TAM])
{ 
    printf("  _0|_1|_2|_3|_4|_5|_6|_7|_8|_9|10|11|12|13|14|\n"); // Numeros das colunas
    for (int i=0; i<TAM; i++)
    {
        printf("%c ", (char)(i+65)); // Letras das linhas, o uso de letras ajuda a evitar confusoes
        for(int j = 0;j < TAM; j++)
        {
            if (estaVivo(matriz[i][j]))
            {
                printf("@@"); // Vivo imprime como @@ (quadrado cheio)
            }
            else
            {
                printf("__"); // Morto imprime como underline (quadrado vazio)
            }
            printf("|");
        }
        printf("\n");
    }
}
 
// Passa todos os valores da matriz original para a matriz copia
void copiarMatriz(int original[][TAM], int copia[][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            copia[i][j] = original[i][j];
        }
    }
}

void pradraoBlock(int matriz[][TAM])
{
    matriz[6][6]=1;
    matriz[6][7]=1;
    matriz[7][6]=1;
    matriz[7][7]=1;
}

void pradraoBeeHive(int matriz[][TAM])
{
    matriz[5][6]=1;
    matriz[5][7]=1;
    matriz[6][5]=1;
    matriz[6][8]=1;
    matriz[7][6]=1;
    matriz[7][7]=1;
}

void pradraoBlinker(int matriz[][TAM])
{
    matriz[5][6]=1;
    matriz[6][6]=1;
    matriz[7][6]=1;
}

void pradraoPulsar(int matriz[][TAM])
{
    matriz[1][3]=1; matriz[1][4]=1; matriz[1][5]=1;
    matriz[1][9]=1; matriz[1][10]=1; matriz[1][11]=1;
    matriz[3][1]=1; matriz[3][6]=1; matriz[3][8]=1;
    matriz[3][13]=1; matriz[4][1]=1; matriz[4][6]=1;
    matriz[4][8]=1; matriz[4][13]=1; matriz[5][1]=1;
    matriz[5][6]=1; matriz[5][8]=1; matriz[5][13]=1;
    matriz[6][3]=1; matriz[6][4]=1; matriz[6][5]=1;
    matriz[6][9]=1; matriz[6][10]=1; matriz[6][11]=1;
    matriz[8][3]=1; matriz[8][4]=1; matriz[8][5]=1;
    matriz[8][9]=1; matriz[8][10]=1; matriz[8][11]=1;
    matriz[9][1]=1; matriz[9][6]=1; matriz[9][8]=1;
    matriz[9][13]=1; matriz[10][1]=1; matriz[10][6]=1;
    matriz[10][8]=1; matriz[10][13]=1; matriz[13][3]=1;
    matriz[13][4]=1; matriz[13][5]=1; matriz[13][9]=1;
    matriz[13][10]=1; matriz[13][11]=1; matriz[11][1]=1;
    matriz[11][6]=1; matriz[11][8]=1; matriz[11][13]=1;
}

void pradraoGlider(int matriz[][TAM])
{
    matriz[1][2]=1;
    matriz[2][3]=1;
    matriz[3][1]=1;
    matriz[3][2]=1;
    matriz[3][3]=1;
}

void pradraoHeavyWeightSpaceship(int matriz[][TAM])
{
    matriz[5][2]=1; matriz[5][3]=1;
    matriz[5][4]=1; matriz[5][5]=1;
    matriz[5][6]=1; matriz[5][7]=1;
    matriz[6][1]=1; matriz[6][7]=1;
    matriz[7][7]=1; matriz[8][1]=1;
    matriz[8][6]=1; matriz[9][3]=1;
    matriz[9][4]=1;
}

int posicaoExiste(int x, int y)
{
    if ((x >= 0) && (x < TAM) && (y >= 0) && (y < TAM))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Retorna o numero de vizinhos vivos
int contarVizinhos(int matriz[][TAM], int linha, int coluna)
{
    int contador = 0;
    if (posicaoExiste(linha-1, coluna-1) && estaVivo(matriz[linha-1][coluna-1])) // Primeiro vizinho a ser verificado, canto superior esquerdo
    {
        contador++; // O indice do vizinho nao esta fora da matriz (considerado morto) e o vizinho esta vivo, logo o contador eh incrementado
    }
    if (posicaoExiste(linha-1, coluna) && estaVivo(matriz[linha-1][coluna]))
    {
        contador++;
    }
    if (posicaoExiste(linha-1, coluna+1) && estaVivo(matriz[linha-1][coluna+1]))
    {
        contador++;
    }
    if (posicaoExiste(linha, coluna-1) && estaVivo(matriz[linha][coluna-1]))
    {
        contador++;
    }
    if (posicaoExiste(linha, coluna+1) && estaVivo(matriz[linha][coluna+1]))
    {
        contador++;
    }
    if (posicaoExiste(linha+1, coluna-1) && estaVivo(matriz[linha+1][coluna-1]))
    {
        contador++;
    }
    if (posicaoExiste(linha+1, coluna) && estaVivo(matriz[linha+1][coluna]))
    {
        contador++;
    }
    if (posicaoExiste(linha+1, coluna+1) && estaVivo(matriz[linha+1][coluna+1])) // Ultimo vizinho, canto inferior direito
    {
        contador++;
    }
    return contador;
}

// Aplica as regras do jogo da vida, usando a matriz atual como base e escrevendo o proximo estado na matriz futura
void executarPasso(int atual[][TAM], int futura[][TAM])
{
    int n_vizinhos;
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            n_vizinhos = contarVizinhos(atual, i, j);
            if ( estaVivo(atual[i][j]) && (n_vizinhos == 2))
            {
                futura[i][j]=1;
            }
            else if ( estaVivo(atual[i][j]) && (n_vizinhos == 3))
            {
                futura[i][j]=1;
            }
            else if ( estaVivo(atual[i][j]) && (n_vizinhos==3))
            {
                futura[i][j]=1;
            }
            else
            {
                futura[i][j]=0;
            }
        }
    }
}

void execucaoNaTela(int matrizAtual[][TAM], int matrizFutura[][TAM])
{
    while(true)
    {
        system("cls");
        imprimirMatriz(matrizAtual);
        executarPasso(matrizAtual, matrizFutura); // Executa o passo na matriz futura
        copiarMatriz(matrizFutura,matrizAtual); // Atualiza a matriz
        printf("\n\nAperte Espaco para sair ou Enter para o executar o proximo passo");
        int tecla = getch();
        if(tecla == 32)
        {
            break;
        }
    }
}

void submenuPadraoPronto(int matrizAtual[][TAM], int matrizFutura[][TAM])
{
    while(true)
    {
        system("cls");
        imprimirMatriz(matrizAtual);
        printf("\n\n\nEscolha uma opcao:");
        printf("\n0 - Voltar para o menu principal");
        printf("\n1 - Block");
        printf("\n2 - Bee-hive");
        printf("\n3 - Blinker");
        printf("\n4 - Pulsar");
        printf("\n5 - Glider");
        printf("\n6 - Heavy-weight spaceship");
        printf("\n7 - Executar\n");
        int opcao;
        scanf("%d",&opcao);

        if(opcao == 0)
        {
            break;
        }
        else if(opcao == 1) // Preenche a matriz com o padrao escolhido, no caso o Block
        {
            pradraoBlock(matrizAtual);
        }
        else if(opcao == 2) // Bee-hive
        {
            pradraoBeeHive(matrizAtual);
        }
        else if(opcao == 3) // Blinker
        {
            pradraoBlinker(matrizAtual);
        }
        else if(opcao == 4) // Pulsar
        {
            pradraoPulsar(matrizAtual);
                }
        else if(opcao == 5) // Glider
        {
            pradraoGlider(matrizAtual);
        }
        else if(opcao == 6) // Heavy-weight spaceship
        {
            pradraoHeavyWeightSpaceship(matrizAtual);
        }
        else if(opcao == 7) // Execucao
        {
            execucaoNaTela(matrizAtual, matrizFutura);
            break;
        }
    }   
}

void submenuPreenchimentoManual(int matrizAtual[][TAM], int matrizFutura[][TAM])
{
    while(true)
    {
        system("cls");
        imprimirMatriz(matrizAtual);
        printf("\n\n\nEscolha uma opcao:");
        printf("\n0 - Voltar para o menu principal");
        printf("\n1 - Preencher uma celula");
        printf("\n2 - executar\n");
        int opcao;
        scanf("%d",&opcao);

        if(opcao == 0)
        {
            break;
        }
        else if(opcao == 1)
        {
            int posY = -1, posX = -1;
            char caracY;
            while((posY < 0) || (posY > 14)) // Verificacao de erros de entrada
            {
                printf("\n\nDigite a coordenada Y (em letra maiuscula): ");
                scanf(" %c", &caracY);
                posY = (int)(caracY-65); // Converte a letra para um indice inteiro
            }
            while((posX < 0) || (posX > 14))
            {
                printf("\n\nDigite a coordenada X: ");
                scanf("%d", &posX);
            }
            matrizAtual[posY][posX] = 1; // Preenche a celula definida com 1 (vivo)
        }
        else if(opcao == 2)
        {
            execucaoNaTela(matrizAtual, matrizFutura);
            break;
        }
    }
}


int main()
{
    int matrizAtual[TAM][TAM], matrizFutura[TAM][TAM]; // Matriz atual que sera exibida e a futura, na qual sera efetuado o proximo passo
    while(true)
    {
        zerarMatriz(matrizAtual);
        printf("Jogo da vida de Conway\n\n");
        imprimirMatriz(matrizAtual);
        printf("\n\n\nEscolha uma opcao:");
        printf("\n0 - Sair");
        printf("\n1 - Preencher manualmente a matriz");
        printf("\n2 - Usar um padrao pronto\n");
        int opc;
        scanf("%d",&opc);

        if(opc == 0){
            break;
        }

        else if (opc == 1)
        {
            submenuPreenchimentoManual(matrizAtual, matrizFutura);
        }

        else if(opc == 2)
        {
            submenuPadraoPronto(matrizAtual, matrizFutura);
        }
        system("cls");
    }
    return 0;
}
