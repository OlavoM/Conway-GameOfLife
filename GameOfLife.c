/*
Jogo da vida de Conway
Olavo M
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define TAM 15

void zerarMatriz(int matriz[][TAM]){ //preenche a matriz com 0 (mortos)
    for (int i = 0; i<TAM; i++){
        for (int j = 0; j<TAM; j++){
            matriz[i][j] = 0;
        }
    }
}

void imprimirMatriz(int matriz[][TAM]){ //imprime a matriz com seus indices
    printf("  _0|_1|_2|_3|_4|_5|_6|_7|_8|_9|10|11|12|13|14|\n"); //numero da coluna
    for (int i=0;i<TAM;i++){
        printf("%c ", (char)(i+65)); //letra da linha, as letras ajudam a nao confundir o usuario
        for(int j=0;j<TAM;j++){
            if (matriz[i][j] == 0) printf("_"); //morto imprime como underline (quadrado vazio) na tela
            else printf ("@"); //vivo imprime como @ (quadrado cheio)
            printf("|");
        }
        printf("\n");
    }
}

void copiarMatriz(int original[][TAM], int copia[][TAM]){ //passa todos os valores da matriz original para a matriz copia
    for (int i = 0; i<TAM; i++){
        for (int j = 0; j<TAM; j++){
            copia[i][j] = original[i][j];
        }
    }
}

int contarVizinhos(int matriz[][TAM], int linha, int coluna){ //retorna o numero de vizinhos vivos
    int contador = 0;
    if (linha-1>=0 && linha-1<TAM && coluna-1>=0 && coluna-1<TAM && matriz[linha-1][coluna-1]==1) //primeiro vizinho, canto superior esquerdo
        contador++; //o indice do vizinho nao esta fora da matriz (considerado morto) e o vizinho esta vivo, logo o contador eh incrementado
    if (linha-1>=0 && linha-1<TAM && coluna>=0 && coluna<TAM && matriz[linha-1][coluna]==1)
        contador++;
    if (linha-1>=0 && linha-1<TAM && coluna+1>=0 && coluna+1<TAM && matriz[linha-1][coluna+1]==1)
        contador++;
    if (linha>=0 && linha<TAM && coluna-1>=0 && coluna-1<TAM && matriz[linha][coluna-1]==1)
        contador++;
    if (linha>=0 && linha<TAM && coluna+1>=0 && coluna+1<TAM && matriz[linha][coluna+1]==1)
        contador++;
    if (linha+1>=0 && linha+1<TAM && coluna-1>=0 && coluna-1<TAM && matriz[linha+1][coluna-1]==1)
        contador++;
    if (linha+1>=0 && linha+1<TAM && coluna>=0 && coluna<TAM && matriz[linha+1][coluna]==1)
        contador++;
    if (linha+1>=0 && linha+1<TAM && coluna+1>=0 && coluna+1<TAM && matriz[linha+1][coluna+1]==1)//ultimo vizinho, canto inferior direito
        contador++;
    return contador;
}

void executarPasso(int atual[][TAM], int futura[][TAM]){//aplica as regras do jogo da vida, usando a matriz atual como base e escrevendo o proximo estado na matriz futura
    int n_vizinhos;
    for (int i = 0; i<TAM; i++){
        for (int j = 0; j<TAM; j++){
            n_vizinhos = contarVizinhos(atual, i, j);
            if (atual[i][j]==1 && n_vizinhos==2)
                futura[i][j]=1;
            else if (atual[i][j]==1 && n_vizinhos==3)
                futura[i][j]=1;
            else if (atual[i][j]==0 && n_vizinhos==3)
                futura[i][j]=1;
            else
                futura[i][j]=0;
        }
    }
}

int main(){
    int matrizAtual[TAM][TAM], matrizFutura[TAM][TAM]; //cria a matriz atual que sera exibida e a futura, na qual sera efetuado o proximo passo
    while(true){//menu principal
        zerarMatriz(matrizAtual);
        printf("Jogo da vida de Conway\n\n");
        imprimirMatriz(matrizAtual);
        printf("\n\n\nEscolha uma opcao:");
        printf("\n0 - Sair");
        printf("\n1 - Preencher manualmente a matriz");
        printf("\n2 - Usar um padrao pronto\n");
        int opc;
        scanf("%d",&opc);
        if(opc==0)
            break;
        else if (opc==1){//submenu manual
            while(true){
                system("cls");
                imprimirMatriz(matrizAtual);
                printf("\n\n\nEscolha uma opcao:");
                printf("\n0 - Voltar para o menu principal");
                printf("\n1 - Preencher uma celula");
                printf("\n2 - executar\n");
                int opcManual;
                scanf("%d",&opcManual);
                if(opcManual==0)
                    break;
                else if(opcManual==1){
                    int posY=-1, posX=-1;
                    char caracY;
                    while(posY<0 || posY>14){//verificacao de erros de entrada
                        printf("\n\nDigite a coordenada Y (em letra maiuscula): ");
                        scanf(" %c",&caracY);
                        posY = (int)(caracY-65); //converte a letra para um indice inteiro
                    }
                    while(posX<0 || posX>14){
                        printf("\n\nDigite a coordenada X: ");
                        scanf("%d",&posX);
                    }
                    matrizAtual[posY][posX]=1; //preenche a celula definida com 1 (vivo)
                }
                else if(opcManual==2){
                    while (true){
                        system("cls");
                        imprimirMatriz(matrizAtual);
                        executarPasso(matrizAtual, matrizFutura); //executa o passo na matriz futura
                        copiarMatriz(matrizFutura,matrizAtual); //atualiza a matriz
                        printf("\n\nAperte Espaco para sair ou Enter para o executar o proximo passo");
                        int tecla = getch();
                        if(tecla==32){
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if (opc==2){//submenu padrao pronto
            while(true){
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
                int opcPadrao;
                scanf("%d",&opcPadrao);
                if(opcPadrao==0)
                    break;
                else if (opcPadrao==1){ //preenche a matriz com o padrao escolhido, no caso o Block
                    matrizAtual[6][6]=1;
                    matrizAtual[6][7]=1;
                    matrizAtual[7][6]=1;
                    matrizAtual[7][7]=1;
                }
                else if (opcPadrao==2){
                    matrizAtual[5][6]=1;
                    matrizAtual[5][7]=1;
                    matrizAtual[6][5]=1;
                    matrizAtual[6][8]=1;
                    matrizAtual[7][6]=1;
                    matrizAtual[7][7]=1;
                }
                else if (opcPadrao==3){
                    matrizAtual[5][6]=1;
                    matrizAtual[6][6]=1;
                    matrizAtual[7][6]=1;
                }
                else if (opcPadrao==4){
                    matrizAtual[1][3]=1; matrizAtual[1][4]=1; matrizAtual[1][5]=1;
                    matrizAtual[1][9]=1; matrizAtual[1][10]=1; matrizAtual[1][11]=1;
                    matrizAtual[3][1]=1; matrizAtual[3][6]=1; matrizAtual[3][8]=1;
                    matrizAtual[3][13]=1; matrizAtual[4][1]=1; matrizAtual[4][6]=1;
                    matrizAtual[4][8]=1; matrizAtual[4][13]=1; matrizAtual[5][1]=1;
                    matrizAtual[5][6]=1; matrizAtual[5][8]=1; matrizAtual[5][13]=1;
                    matrizAtual[6][3]=1; matrizAtual[6][4]=1; matrizAtual[6][5]=1;
                    matrizAtual[6][9]=1; matrizAtual[6][10]=1; matrizAtual[6][11]=1;
                    matrizAtual[8][3]=1; matrizAtual[8][4]=1; matrizAtual[8][5]=1;
                    matrizAtual[8][9]=1; matrizAtual[8][10]=1; matrizAtual[8][11]=1;
                    matrizAtual[9][1]=1; matrizAtual[9][6]=1; matrizAtual[9][8]=1;
                    matrizAtual[9][13]=1; matrizAtual[10][1]=1; matrizAtual[10][6]=1;
                    matrizAtual[10][8]=1; matrizAtual[10][13]=1; matrizAtual[13][3]=1;
                    matrizAtual[13][4]=1; matrizAtual[13][5]=1; matrizAtual[13][9]=1;
                    matrizAtual[13][10]=1; matrizAtual[13][11]=1; matrizAtual[11][1]=1;
                    matrizAtual[11][6]=1; matrizAtual[11][8]=1; matrizAtual[11][13]=1;
                }
                else if (opcPadrao==5){
                    matrizAtual[1][2]=1;
                    matrizAtual[2][3]=1;
                    matrizAtual[3][1]=1;
                    matrizAtual[3][2]=1;
                    matrizAtual[3][3]=1;
                }
                else if (opcPadrao==6){
                    matrizAtual[5][2]=1;
                    matrizAtual[5][3]=1;
                    matrizAtual[5][4]=1;
                    matrizAtual[5][5]=1;
                    matrizAtual[5][6]=1;
                    matrizAtual[5][7]=1;
                    matrizAtual[6][1]=1;
                    matrizAtual[6][7]=1;
                    matrizAtual[7][7]=1;
                    matrizAtual[8][1]=1;
                    matrizAtual[8][6]=1;
                    matrizAtual[9][3]=1;
                    matrizAtual[9][4]=1;
                }
                else if (opcPadrao==7){
                    while (true){//execucao
                        system("cls");
                        imprimirMatriz(matrizAtual);
                        executarPasso(matrizAtual, matrizFutura);
                        copiarMatriz(matrizFutura,matrizAtual);
                        printf("\n\nAperte Espaco para sair ou Enter para o executar o proximo passo");
                        int tecla = getch();
                        if(tecla==32){
                            break;
                        }
                    }
                    break;
                }
            }
        }
        system("cls");
    }
    return 0;
}
