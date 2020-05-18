#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "sources/grafo.h"

void definirPosicoes(grafo* tGrafo,vertice** fantasma,vertice** pacman,int posMax){
    srand(time(NULL));
    int fPos = (int)rand()%posMax;
    int pPos = (int)rand()%posMax;
    *fantasma = (vertice*)buscaVertice(tGrafo,fPos);
    *pacman = (vertice*)buscaVertice(tGrafo,pPos);
    (*fantasma)->peca = 'F';
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
    int dist  = (logica == 1) ? __INT_MAX__ : -__INT_MAX__;
    vertice* novaPos;
    vertice* tVertice;
    for(int i=0;i<(*peca)->numArestas;i++){
        aresta* tAresta = (aresta*)buscaAresta(*peca,i);
        tVertice = (vertice*)tAresta->destino;
        if((logica == 1 && tVertice->dist < dist) || (logica == 0 && tVertice->dist > dist)){
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

int rolagem(){
    return (int)(rand()%2) + 1;
}

void delay(int ms) { 
    ms = ms*1000;
    clock_t init = clock(); 
    while (clock() < init + ms) ; 
}

int main(){
    grafo* g;
    vertice* fantasma;
    vertice* pacman;
    int x= 0;
    int rodada = 0;
    int logica = 0;
    int fim=0;
    vertice** turno;
    vertice** naoTurno;
    g = criarMatrizConexa(10,10);
    definirPosicoes(g,&fantasma,&pacman,(10*10)-1);
    while(rodada< 100 && fim==0){
        if(rodada%2==0){
            turno = &pacman;
            naoTurno = &fantasma;
            logica =1;
        }else{
            turno = &fantasma;
            naoTurno = &pacman;
            logica = 0;
        }
        for(int i=0;i<rolagem();i++){
            system("clear");
            printf("Rodada: %d\n",rodada);
            buscaPorLargura(g,(*naoTurno)->value);
            imprimeDistanciasMatriz(g,10,10);
            delay(300);
            system("clear");
            printf("Rodada: %d\n",rodada);
            fim = moverPeca(turno, logica);
            imprimeDistanciasMatriz(g,10,10);
            delay(300);
        }
        rodada++;
    }
    if(fim){
        printf("Pacman venceu na rodada %d\n",rodada-1);
    }else{
        printf("Fantasma venceu depois de 100 rodadas");
    }
    liberarGrafo(g);
    return 0;
}