#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "sources/grafo.h"

void definirPosicoes(grafo* tGrafo,vertice** fantasma,vertice** pacman,int posMax){
    srand(time(NULL));//seed para geracao dos numeros aleatorios
    int fPos = (int)rand()%posMax;//define posicao do fantasma
    int pPos = (int)rand()%posMax;//define posicao do pacman
    *fantasma = (vertice*)buscaVertice(tGrafo,fPos);
    *pacman = (vertice*)buscaVertice(tGrafo,pPos);
    (*fantasma)->peca = 'F';//atribui um caractere indicando qual a peça naquela casa
    (*pacman)->peca = 'P';
    
}

void imprimeDistanciasMatriz(grafo* tGrafo,int i,int j){
    int cont = 0;
    for(int m =0; m<i;m++){
        for(int n =0; n<j;n++){
            vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,cont);
            if(tVertice->peca == 'F'){
                printf("\033[0;31m%-3c \033[0m",'F');
            }else if(tVertice->peca == 'P'){
                printf("\033[0;33m%-3c \033[0m",'P');
            }else{
                printf("%-3d ",tVertice->dist);
            }
            cont++;
        }
        printf("\n");
    }
    printf("\n");
}

int moverPeca(vertice** peca, int logica){
    vertice* novaPos;
    vertice* tVertice;
    novaPos = *peca;
    int dist = (*peca)->dist;
    //testa cada uma das casas para onde se pode movimentar
    /*
    No caso do fantasma testará qual casa é mais distante do pacman e tem mais arestas
    No caso do pacman apenas se move para a posição mais próxima do fantasma
    */
    for(int i=0;i<(*peca)->numArestas;i++){
        aresta* tAresta = (aresta*)buscaAresta(*peca,i);
        tVertice = (vertice*)tAresta->destino;
        if((logica == 1 && tVertice->dist < dist) ||
         (logica == 0 && tVertice->dist + tVertice->numArestas > dist+ novaPos->numArestas && tVertice->dist!= 1)){
            dist = tVertice->dist;
            novaPos = tVertice;
        }
    }
    if(novaPos->peca =='F' && logica == 1){
        novaPos->peca = (*peca)->peca;
        (*peca)->peca = '\0';
        return 1;
    }
    char temp = novaPos->peca;
    novaPos->peca = (*peca)->peca;
    (*peca)->peca = temp;
    (*peca) = novaPos; 
    return 0;
}

int rolagem(){//define a quantidade de movimentos naquele turno, 1 ou 2
    return (int)(rand()%2) + 1;
}

void delay(int ms) { //delay utilizado para mostra o movimento das peças
    ms = ms*1000;
    clock_t init = clock(); 
    while (clock() < init + ms) ; 
}

int main(){
    grafo* g;//declaracao do grafo
    vertice* fantasma;//vertice onde se posiciona o fantasma
    vertice* pacman;//vertice onde se posiciona o pacman
    int rodada = 1;
    int logica = 0;//define a logica do movimento 1 = perseguir, 0 = fugir
    int fim=0;//variavel que indica o fim do jogo
    vertice** turno;//ponteiro para o jogador do turno atual
    vertice** naoTurno;//ponteiro para o jogador do proximo turno
    g = criarMatrizConexa(10,10);//inicializa o grafo do tipo matriz
    definirPosicoes(g,&fantasma,&pacman,(10*10)-1);//define as posicoes dos dois jogadores
    while(rodada<= 60 && fim==0){//enquanto o fantasma nao for pego ou nao for a rodada 60
        if(rodada%2==0){//turno pares sao os turnos do pacman
            turno = &pacman;
            naoTurno = &fantasma;
            logica =1;//logica de perseguidor
        }else{
            turno = &fantasma;
            naoTurno = &pacman;
            logica = 0;//logica de fuga
        }
        for(int i=0;i<rolagem();i++){//calcula quantos movimentos poderao ser feitos
            system("clear");//limpa a tela
            printf("Rodada: %d\n",rodada);//imprime a rodada atual
            buscaPorLargura(g,(*naoTurno)->value);//calcula a distancia de todas as casas a partir de uma das pecas
            imprimeDistanciasMatriz(g,10,10);//imprime o grafo com as distancias
            delay(300);//delay 300 ms
            system("clear");
            printf("Rodada: %d\n",rodada);
            fim = moverPeca(turno, logica);//move a peca do turno atual com base em sua logica
            imprimeDistanciasMatriz(g,10,10);//imprime o grafo apos a peça ter mexido
            delay(300);
        }
        rodada++;
    }
    if(fim){
        printf("Pacman venceu na rodada %d\n",rodada-1);
    }else{
        printf("Fantasma venceu depois de 60 rodadas\n");
    }
    liberarGrafo(g);
    return 0;
}