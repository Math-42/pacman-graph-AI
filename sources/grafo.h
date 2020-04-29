#ifndef _GRAFO_H_
#define _GRAFO_H_
#include "lista.h"


/*
TAD de Grafo utilizando lista encadeada simples
Matheus Vieira Gonçalves
*/

typedef struct{//estrutura que conterá as variaveis necessárias para operar com o grafo
    int buscaPorLarguraStatus;
}stats;

typedef struct{//estrutura para cada vertice do grafo
    int value;//valor ou id que ele assume
    int numArestas;//numArestas total
    int dist;//distancia desse vertice a algum outro vertice
    stats status;//struct onde ficará salvo as variáveis necessárias para operar com o grafo
    void* dado;//dado que esse vertice salva
    Lista* arestas;//Lista das arestas do vertice
}vertice;

typedef struct{//estrutura para cada aresta ligante
    vertice* destino;//endereço do vertice para onde está indo
    int no;//valor do no que esta sendo conectada
    void* dado;//dado que essa aresta salva
    int peso;//valor da conexão
}aresta;

typedef struct{//struct do grafo
    Lista* vertices;//lista de structs de vertice
    int numVertices;//numero total de vertice
    int numArestas;//numero total de arestas
}grafo;

grafo* criarGrafo();//cria o grafo alocando a lista de vertices
void inserirVertice(grafo* tGrafo,int no);//insere um vertice na lista de vertices
void inserirAresta(grafo* tGrafo,int no1,int no2,int peso);//insere uma aresta ,nao direcionada, em dois vertices
void inserirArestaDirecional(grafo* tGrafo,int no1,int no2,int peso);//insere uma aresta indo do no1 para no2 
void removerAresta(grafo* tGrafo,int no1,int no2);//remove uma aresta nao direcionada entre no1 e o no2
void removerArestaDirecional(grafo* tGrafo,int no1,int no2);//remove uma aresta saindo do no1 para o no2
void imprimirListaAdjacencias(grafo* tGrafo);//imprime a lista de adjacência do grafo
void liberarGrafo(grafo* tGrafo);//libera a memória alocada
grafo* criarMatrizConexa(int i,int j);//cria uma matriz que cada casa é conectada as casas do lado
void buscaPorLargura(grafo* tGrafo,int vInicial);
vertice* buscaVertice(grafo* tGrafo,int value);//Busca um vértice na lista de adjacência
aresta* buscaAresta(vertice* tVertice,int value);//Busca uma aresta na lista de arestas
grafo* copiarGrafo(grafo* tGrafo);//copia o grafo na memória


#endif