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
    (*fantasma)->value = -1;
    (*pacman)->value = -2;
    
}

void imprimeDistanciasMatriz(grafo* tGrafo,int i,int j){
    int cont = 0;
    for(int m =0; m<i;m++){
        for(int n =0; n<j;n++){
            vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,cont);
            if(tVertice->value == -1){
                printf("\033[0;31m%-3c \033[0m",'F');
            }else if(tVertice->value == -2){
                printf("\033[0;33m%-3c \033[0m",'P');
            }else{
                printf("%-3d ",tVertice->dist);
            }
            tVertice->status.buscaPorLarguraStatus = -1;
            tVertice->dist = -1;
            cont++;
        }
        printf("\n");
    }
    printf("\n");
}

void moverPeca(vertice** peca, int logica){
    int dist  = (logica == 1) ? 1000000 : -1000000;
    vertice* novaPos;
    vertice* tVertice;
    for(int i=0;i<(*peca)->numArestas;i++){
        aresta* tAresta = (aresta*)buscaAresta(*peca,i);
        tVertice = (vertice*)tAresta->destino;
        if( (logica == 1 && tVertice->dist < dist) || (logica == 0 && tVertice->dist > dist)){
            dist = tVertice->dist;
            novaPos = tVertice;
        }
    }
    int temp = novaPos->value;
    novaPos->value = (*peca)->value;
    (*peca)->value = temp;
    (*peca) = novaPos; 
}

int main(){
    grafo* g;
    vertice* fantasma;
    vertice* pacman;
    int x= 0;
    g = criarMatrizConexa(10,10);
    definirPosicoes(g,&fantasma,&pacman,(10*10)-1);
    while(x !=1){
        buscaPorLargura(g,fantasma->value);
        imprimeDistanciasMatriz(g,10,10);
        buscaPorLargura(g,fantasma->value);
        scanf("%d",&x);
        system("clear");
        moverPeca(&pacman, 1);
        buscaPorLargura(g,fantasma->value);
        imprimeDistanciasMatriz(g,10,10);
        scanf("%d",&x);
        system("clear");
        buscaPorLargura(g,pacman->value);
        imprimeDistanciasMatriz(g,10,10);
        buscaPorLargura(g,pacman->value);
        scanf("%d",&x);
        system("clear");
        moverPeca(&fantasma, 0);
        buscaPorLargura(g,pacman->value);
        imprimeDistanciasMatriz(g,10,10);
        scanf("%d",&x);
        system("clear");
    }
    liberarGrafo(g);
    return 0;
}