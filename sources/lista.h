#ifndef _LISTA_H_
#define _LISTA_H_

/*
TAD de Lista encadeda simples utilizando dados genéricos
Matheus Vieira Gonçalves
*/

//estrutura que define cada nó da lista, um char e um endereço para o próximo elemento
typedef struct elemento{
	void* dado;
	struct elemento *prox;
}elemento;

typedef  elemento* Lista; //vetor que apontará para o último elemento da lista
typedef elemento elem;//typedef para declaração dos elementos da lista 
typedef void* buscar (void* elemento,void* dadoProcurado);//tipo padrão de função de buscar

Lista *criarLista();//funcao que cria a lista
void criarElemento(Lista* li,void* dado);//funcao que cria um novo nó na lista
void removerElementoInicio(Lista* li,int _FREE_DATA_);//remove o último nó adicionado na lista
void criarElementoFinal(Lista* li,void* dado);// cria um elemento após o ultimo nó
void removerElementoFinal(Lista* li,int _FREE_DATA_);// remove o último elemento da lista
int removerElementoBuscado(Lista* li,void* dadoProcurado,void* funcDeBusca,int _FREE_DATA_);//remove um elemento especifico
void* lerElemento(Lista* li,int elemento);// le um elemento especifico da lista
void* buscarElemento(Lista* li,void* dadoProcurado,void* funcDeBusca);//busca um elemento a partir de certo dado
void limparLista(Lista* li,int _FREE_DATA_);//limpa e libera a memória alocada para uma lista em específico
int estaVazia(Lista* li);//testa se determinada lista esta vazia

#endif
