#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "grafo.h"

grafo* criarGrafo(){//inicializa o grafo
    grafo* novoGrafo = (grafo*)calloc(1,sizeof(grafo));//aloca espaço na memória
    novoGrafo->vertices = criarLista();//cria uma lista de vertices
    return novoGrafo;//retorna o endereço alocado
}

grafo* criarMatrizConexa(int i,int j){
    grafo* novoGrafo = criarGrafo();
    int id = 0;
    for(int m=0;m<i;m++){
        for(int n=0;n<j;n++){
            inserirVertice(novoGrafo,id);
            if(id-j>=0){
                inserirAresta(novoGrafo,id,id-j,1);
            }
            if(n-1 >=0){
                inserirAresta(novoGrafo,id,id-1,1);
            }
            id++;
        }
    }
    return novoGrafo;
}

grafo* copiarGrafo(grafo* tGrafo){
    grafo* novoGrafo = criarGrafo();
    for(int i=0;i<tGrafo->numVertices;i++){
        vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,i);
        inserirVertice(novoGrafo,tVertice->value);
    }
    for(int i=0;i<tGrafo->numVertices;i++){
        vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,i);
        for(int j=0;j< tVertice->numArestas;j++){
            aresta* tAresta = (aresta*)lerElemento(tVertice->arestas,i);
            inserirAresta(novoGrafo,tVertice->value,tAresta->no,tAresta->peso);
        }
    }
    return novoGrafo;
}

void inserirVertice(grafo* tGrafo,int no){//insere um vértice no grafo
    vertice* tVertice = (vertice*)calloc(1,sizeof(vertice));//aloca o espaço de memória
    tVertice->value = no;//da o valor daquele nó, no caso uma identificação
    tVertice->dist = -1;//define um valor de distância inicial padrão
    tVertice->status.buscaPorLarguraStatus = -1;//define como -1 valor dos nós não visitados
    tGrafo->numVertices ++;//soma 1 ao total de vertices do grafo
    tVertice->numArestas = 0;//inicializa como 0 o numero de arestas desse vertice
    tVertice->arestas = criarLista();//inicializa a lista onde ficarão salvas as arestas desse vertice
    criarElementoFinal(tGrafo->vertices,tVertice);//cria um elemento no final da lista de vertices adicionando este vertice
}

/*funções utilizadas para buscar um vertice ou aresta especifica na lista, uma vez que a lista é genérica
foi necessário utilizar ponteiro de função de comparação para que ela possa encontrar o valor requerido
elas apenas testam se o no possue o valor(id) que se está procurando
*/
int buscaVerticeFunc(void* tVertice, void* value){
    return (((vertice *)tVertice)->value == *((int *)value)) ? 1 : 0;//true | false
}

int buscaArestaFunc(void* tAresta, void* value){
    return (((aresta *)tAresta)->no == *((int *)value)) ? 1 : 0;//true | false
}

vertice* buscaVertice(grafo* tGrafo,int value){//Busca um vertice na lista de adjacência
    return (vertice*)buscarElemento(tGrafo->vertices,&value,buscaVerticeFunc);
}

aresta* buscaAresta(vertice* tVertice,int value){//Le uma aresta especifica da lista de arestas
    return (aresta*)lerElemento(tVertice->arestas,value);
}

void inserirArestaDirecional(grafo* tGrafo,int no1,int no2,int peso){//insere uma aresta direcionada no grafo
    vertice* tVertice = (vertice*)buscarElemento(tGrafo->vertices,&no1,buscaVerticeFunc);//busca o vertice que se quer inserir a aresta
    if(buscarElemento(tVertice->arestas,&no2,buscaArestaFunc) == NULL){//testa se ele já existe ou não
        tVertice->numArestas ++;//soma 1 ao total de arestas deste vertice
        tGrafo->numArestas ++;
        aresta* tAresta = (aresta*)calloc(1,sizeof(aresta));//aloca o espaço da aresta
        tAresta->peso = peso;//define o peso da conexão
        tAresta->no = no2;//define para onde vai a conexão, id do no de chegada
        tAresta->destino = ((vertice*)buscarElemento(tGrafo->vertices,&no2,buscaVerticeFunc));//salva o endereço do vértice de destino
        criarElementoFinal(tVertice->arestas,tAresta);//cria um elemento no final da lista de arestas desse vertice, adicionando essa aresta
    }
}

void inserirAresta(grafo* tGrafo,int no1,int no2,int peso){//insere uma aresta n direcionada
    inserirArestaDirecional(tGrafo,no1,no2,peso);//liga do no1 ao no2
    if(no1 != no2){//testa se a chegada é diferente da saida evitando repetição desnecessária
        inserirArestaDirecional(tGrafo,no2,no1,peso);//liga do no2 ao no1
    }
}

void removerArestaDirecional(grafo* tGrafo,int no1,int no2){//remove uma aresta direcionada
    vertice* tVertice = (vertice*)buscarElemento(tGrafo->vertices,&no1,buscaVerticeFunc);//busca o vertice de onde ser quer remover a conexão
    if(removerElementoBuscado(tVertice->arestas,&no2,buscaArestaFunc,1)){//remove a resta e testa se a mesma existe
        tVertice->numArestas--;//caso tenha sido removida subtrai 1 da quantidade de arestas desse vertice
        tGrafo->numArestas--;
    }
}

void removerAresta(grafo* tGrafo,int no1,int no2){//remove uma aresta não direcionada
    removerArestaDirecional(tGrafo,no1,no2);//remove do no1 para o no2
    removerArestaDirecional(tGrafo,no2,no1);//remove do no2 para o no1
}

void imprimirListaAdjacencias(grafo* tGrafo){//imprime a lista de adjacência
    for(int i=0; i < tGrafo->numVertices; i++){//percorre a lista de vertices do grafo
        vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,i);//retorna o elemento i da lista
        printf("%d: ",tVertice->value);//imprime seu valor
        for(int j = 0; j < tVertice->numArestas; j++){//percorre a lista de arestas do vertice
            aresta* tAresta = (aresta*)lerElemento(tVertice->arestas ,j);//retorna o elemento j da lista
            printf("%d ",tAresta->no);//imprime seu valor
        }
        printf("\n");
    }
    printf("\n");
}

void liberarGrafo(grafo* tGrafo){//libera a memória alocada
    for(int i=0; i<tGrafo->numVertices;i++){//percorre a lista de vertices do grafo
        vertice* tVertice = (vertice*)lerElemento(tGrafo->vertices,i);//retorna o elemento i da lista
        limparLista(tVertice->arestas,1);//libera a lista de arestas deste vertice
    }
    limparLista(tGrafo->vertices,1);//libera a lista de vertices
    free(tGrafo);//libera o próprio grafo
}

void buscaPorLargura(grafo* tGrafo,int vInicial){
    Lista* fila = criarLista();//fila utilizada para inserir os vertices
    vertice* tVertice = buscarElemento(tGrafo->vertices,&vInicial,buscaVerticeFunc);//busca o vertice inicial
    tVertice->status.buscaPorLarguraStatus = 0;
    tVertice->dist = 0;
    criarElementoFinal(fila,tVertice);
    while (!estaVazia(fila)){
        tVertice = (vertice*)lerElemento(fila,0);
        if(tVertice->status.buscaPorLarguraStatus == 0){
            tVertice->status.buscaPorLarguraStatus = 1;
            for(int i=0;i<tVertice->numArestas;i++){
                aresta* tAresta = (aresta*)lerElemento(tVertice->arestas,i);
                vertice* tVertice2 = (vertice*)tAresta->destino;
                if(tVertice2->status.buscaPorLarguraStatus == -1){
                    tVertice2->status.buscaPorLarguraStatus = 0;
                    tVertice2->dist = tVertice->dist + 1;
                    criarElementoFinal(fila,tVertice2);
                }   
            }
        }
        removerElementoInicio(fila,0);
    }
    limparLista(fila,0);
}
