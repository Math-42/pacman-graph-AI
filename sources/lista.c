#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

Lista* criarLista(){
	Lista* li = (Lista*)malloc(sizeof(Lista));//alocacao do ponteiro
	if(li!=NULL){//o aponta primeiramente para null
		*li=NULL;
	}
	return li;//retorna o ponteiro alocado
}

void criarElemento(Lista* li,void* dado){
	elem *e1 = (elem*)malloc(sizeof(elem));// aloca um espaco de tamanho elem na memória
	e1->dado = dado;//atribui ao dado do elemento o dado passado como parametro
	e1->prox = *li;//atribui ao prox do elemento o endereco que o ponteiro "bobo" apontava anteriormente
	*li = e1;//atualiza o ponteiro para o endereco do elemento criado
}

void removerElementoInicio(Lista* li, int _FREE_DATA_){
	if(*li!=NULL){//testa se é o último elemento da lista
		elem *temp;//ponteiro temporário
		temp = (*li)->prox;//ponteiro temporário passa a apontar para o segundo elemento da lista
		if(_FREE_DATA_){
			free((*li)->dado);//libera o dado alocado
		}
		free((*li));// o primeiro elemento é liberado
		*li = temp;//o ponteiro "bobo" recebe o endereco do novo primeiro elemento
	}
}

void criarElementoFinal(Lista* li,void* dado){
	if(*li!=NULL){//testa se é o primeiro elemento a ser criado
		elem *temp = *li;
		while((*li)->prox!=NULL){//procura o último elemento da lista
			*li=(*li)->prox;
		}
		elemento *e1 = (elem*)malloc(sizeof(elem));// aloca um novo elemento
		e1->dado = dado;//atribui o dado desejado que foi passado por parametro
		e1->prox = NULL;// atribui o valor NULL por ser o último elemento da lista
		(*li)->prox = e1;//atribui ao campo prox do penultimo elemento o endereco do último elemento
		*li = temp;// recupera o endereco do primeiro elemento da lista
	}
	else{//caso seja o primeiro elemento a ser criado, chama a funcao criarElemento normalmente
		criarElemento(li,dado);
	}
}

void removerElementoFinal(Lista* li, int _FREE_DATA_){
	if(*li!=NULL){//testa se existe algum elemento
		elem *temp = *li;
		elem *temp2;
		while((*li)->prox!=NULL){//procura o ultimo elemento da lista
			temp2 = *li;
			*li=(*li)->prox;
		}
		(*temp2).prox = NULL;// atribui o valor null ao campo prox do penultimo elemento, que se tornará o último
		if(_FREE_DATA_){
			free((*li)->dado);//libera o dado alocado
		}
		free(*li);//libera o espaco alocado para o antigo ultimo elemento
		*li = temp;//recupera o endereco do primeiro elemento
	}
}

void* lerElemento(Lista* li,int nodulo){
	elem *temp = *li;//armazena-se o endereco do primeiro elemento da lista
	for(int i=0;i<nodulo;i++){// procura o nodulo passado por parametro 
		if((*li)->prox!=NULL){
			*li=(*li)->prox;
		}
		else{//caso a lista nao possua aquele numero de nódulos é retornado o último nódulo
			void* temp2 = (*li)->dado;
			*li=temp;
			return temp2;
		}
	}
	void* temp2 = (*li)->dado;
	*li=temp;//recupera-se o endereco
	return temp2;//retorna o char encontrado
}

void* buscarElemento(Lista* li,void* dadoProcurado,void* funcDeBusca){
	buscar *buscador = funcDeBusca;//recebe o ponteiro para função passado como parâmetro
	elem *temp = *li;//armazena-se o endereco do primeiro elemento da lista
	while((*li) !=NULL){
		if((*buscador)((*li)->dado,dadoProcurado)){//testa se é o elemento buscado
			void* temp2 = (*li)->dado;//salva o dado temporariamente
			*li=temp;//recupera-se o endereco
			return temp2;//retorna o dado salvo
		}else{
			*li=(*li)->prox;
		}
	}
	*li = temp;//recupera-se o endereco
	return NULL;
}

int removerElementoBuscado(Lista* li,void* dadoProcurado,void* funcDeBusca, int _FREE_DATA_){
	buscar *buscador = funcDeBusca;
	elem *temp = *li;//armazena-se o endereco do primeiro elemento da lista
	elem *temp2 = *li;//armazena-se o endereço do elemento anterior ao atual durante a busca
	int inicio = 1;// variavel para saber se o primeiro elemento está sendo removido;
	while((*li) !=NULL){
		if((*buscador)((*li)->dado,dadoProcurado)){
			if(_FREE_DATA_){
				free((*li)->dado);//libera o dado alocado
			}
			if(!inicio){//testa se não é o primeiro elemento daa lista
				temp2->prox = (*li)->prox;//religa a cadeia da lista
				free(*li);//libera o elemento encontrado
				*li = temp;//recupera-se o endereco
			}else{
				(*li) = (*li)->prox;//move a cabeça da lista para o segundo elemento
				free(temp);//libeira o primeiro elemento
			}
			return 1;//retorn 1 caso tenha encontrado o elemento
		}else{
			temp2 = *li;//salva o elemento atual
			*li=(*li)->prox;//move com a cabeça da lista
			inicio = 0;//atribue 0 a variavel, equivalente a falso, indicando n ser mais o inicio da lista
		}
	}
	*li = temp;//recupera-se o endereco
	return 0;//retorna 0 caso n tenha encontrado o elemento
}

int estaVazia(Lista* li){
	if(*li == NULL){
		return 1;
	}
	return 0;
}

void limparLista(Lista* li, int _FREE_DATA_){
	while(*li!=NULL){
		removerElementoInicio(li,_FREE_DATA_);//remove cada elemento da lista
	}
	free(li);//libera o espaco de memória alocado para o ponteiro que percorre a lista
}