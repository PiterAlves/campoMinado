#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tela[9][9];
int tam = 9;
int bombas = 10;
int escolhaJogador[9][9];
int posicoesNaoReveladas = 0;
int totalBombas = 0;
    
void sorteiaBombas(){
    for(int a=0; a<tam; a++)
        for(int b=0; b<tam; b++){
            escolhaJogador[a][b] = 0;
            tela[a][b] = 0;
        }    
    
    int bombasColocadas = 0; 

    while(bombasColocadas < bombas){
        int i = rand() % tam;
        int j = rand() % tam;
        if(tela[i][j] != -1){
            tela[i][j] = -1;
            bombasColocadas++;
        }    
    }
}

int contarBombasAoRedor(int x, int y){
    int bombasAoRedor = 0;
    
    for (int i = x - 1; i <= x + 1; i++) 
        for (int j = y - 1; j <= y + 1; j++){ 
            if (i >= 0 && i < tam && j >= 0 && j < tam){ 
                if (tela[i][j] == -1) 
                    bombasAoRedor++;
            }
        }    

    return bombasAoRedor;
}

void iniciaTela(){
    for(int a=0; a<tam; a++)
        for(int b=0; b<tam; b++)
            escolhaJogador[a][b] = 0;
    
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            tela[i][j] = 0;

    sorteiaBombas();
    
    for(int i=0; i<tam; i++)
        for(int j=0; j<tam; j++){
            if(tela[i][j] != -1){
                int bombasAoRedor = contarBombasAoRedor(i, j);
                tela[i][j] = bombasAoRedor;
            }
        }
    
}

void imprimeTelaJogador(int x, int y){
    
    escolhaJogador[x][y] = 1;
    
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if(escolhaJogador[i][j] == 1)
                printf("%3d", tela[i][j]);
            if(escolhaJogador[i][j] == 0){
                printf("  X");
                totalBombas++;
            }    
        }    
        printf("\n");
    }
    
    printf("Existem 10 bombas!\n\n");
}

void imprimeTelaOriginal(){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++)
            printf("%3d", tela[i][j]);
        printf("\n");
    }
}

void posicaoEscolida(int linha, int coluna){
    if(tela[linha][coluna] == -1)
        imprimeTelaOriginal();
    if (tela[linha][coluna] >= 0)
        imprimeTelaJogador(linha, coluna);
    
}

int main(){
    srand(time(NULL));
    
    int jogo = 1;
    int x, y, *p;
    
    while(jogo == 1){
        printf("CAMPO MINADO\n");
        printf("\nEscolha uma das opções seguintes para continuar:\n");
        printf("1: Jogar\n");
        printf("2: Menu\n");
        printf("3: Sair\n");
        scanf("%d", &jogo);
        while(jogo > 3){
            printf("Ai não jogador!\n");
            printf("Vou te dar mais uma chance!\n");
            printf("Escolha uma das opções abaixo:\n");
            printf("1 - Jogar\n");
            printf("2 - Menu\n");
            printf("3 - Sair\n");
            scanf("%d", &jogo);
        }
        
        if(jogo == 2){
            printf("\nPara revelar uma posição é preciso escolher a linha e coluna que essa posição se encontra.\n");
            printf("Se a posição revelada conter um 0, é porque não tem nenhuma bomba nas 8 posições ao redor dela.(Não valendo para as posições de ponta)\n");
            printf("(Sempre que a posição revelada for um 0, será revelado também outraas posições que contém 0 ao redor dela.\n");
            printf("Se a posição revelada conter um número maior que 0, o número representa a quantidade de bombas nas 8 posições ao redor dela.\n");
            printf("Se a posição revelada conter -1, siginifica que você revelou uma bomba, portanto perdeu o jogo!\n");
            printf("\nVamos para o jogo? (Digite qualquer número para seguir ou 3 para sair): ");
            scanf("%d", &jogo);
        }
        
        if(jogo == 3)
            return 0;
        
        printf("\nVamos Nessa!\n");
        iniciaTela();
        
        while(1){
            imprimeTelaOriginal();
            printf("Ecolha a posição que você deseja revelar. (linha, coluna): ");
            scanf("%d %d", &x, &y);
            while((x >= tam || y >= tam) || (x < 0 || y < 0)){
                printf("Posição escolhida invalida! (tente números de 0 - 9)\n");
                printf("Ecolha a posição que você deseja revelar. (linha, coluna): ");
                scanf("%d %d", &x, &y);
            }
            posicaoEscolida(x, y);
            if(tela[x][y] == -1){
                printf("Você perdeu!\n");
                jogo = 2;
                break;
            } if(totalBombas == 10){
                printf("Você ganhou!\n");
                jogo = 2;
                break;
            }
        }
    }    

    return 0;
}