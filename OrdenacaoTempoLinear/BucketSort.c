#include <stdio.h>
#include <stdlib.h>

struct elemento {
	float dados;
	struct elemento *prox;
};

typedef struct elemento* Lista;
typedef struct elemento Elem;

void printfVet(float *V, int n);
void printList(Elem *temp);
void insertionSortListaLigada(Lista *li, float num);
void bucketSort(float *V, int tam);

int main() {
    int i, N;

    printf("\n------------------Bucket Sort---------------------\n");
    float A[10] = {0.78, 0.17, 0.39, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68, 0.26};
    N = 10;

    printf("\nSem ordenar:\n");
    printfVet(A, N);
    bucketSort(A, N);
    printf("\n\nOrdenado:\n");
    printfVet(A, N);

    printf("\n---------------------------------------------------\n");

    system("pause");
    return 0;
}


void printfVet(float *V, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%.2f  ", V[i]);
    printf("\n");
} //printar vetor

void printList(Elem *temp){ //pra teste, imprime so os da lista da casa a[i]
	while(temp != NULL){
		printf("%.2f  ", temp->dados);
		temp = temp->prox;
	}
}

void insertionSortListaLigada(Lista *li, float num){ //insere lista ordenado
    if(li == NULL) // a lista eh valida?
        exit -1;
    Elem *no = (Elem*) malloc (sizeof(Elem)); //alocacao
    if(no == NULL) //consegui alocar?
        return;
	no->dados = num; //copiando os dados para o cara da lista
	Elem *aux = *li; //ponteiro auxiliar q aponta pro inicio onde quero inserir

	if ((*li) == NULL){//se eh o primeiro no a ser inserido
		no->prox = NULL; //como eh o primeiro ele aponta pro null
		*li = no; //o inicio de a[i] agora aponta para o novo no
		return;
	} else {
        Elem *ant, *atual; //criando auxiliares
        atual = *li; //atual aponta pro mesmo que lista (cabeca) aponta
        while(atual != NULL && atual->dados < num){ //percorrer ate o fim ou ate achar o dado maior do que o q eu quero inserir
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início (atual nao pecorreu nada)
            no->prox = (*li); //aponta pro primeiro
            *li = no; //ele vira oprimeiro
        }else{
            no->prox = atual; //aponta pro que o autauta apontadno (insere antes dele)
            ant->prox = no; //o que tava antes do atual aponta pro q inseri
        }
        return; //consegui
	}
}

void bucketSort(float *V, int tam){
    int i;
    Lista li[tam]; //lista do tamanho max do vetor, posso nao usar todos
    int aux; //bucketIndex

	for(i = 0; i < tam; i++)
		li[i] = NULL; //inicializa a lista com buckets NULL (corrige erro)

	for(i = 0; i < tam; i++){ //coloca os elementos do array em n diferentes buckets
		aux = tam * V[i]; //calcula indice de insecrcao do bucket no array
		insertionSortListaLigada(&li[aux], V[i]); //inserir usando insertionSort
	}

    Elem *temp;
	int j = 0; //contador de tamanho, ate completar o vetor V de novo
	for(i = 0; j < tam; i++){ //concatenar, note q a variavel de controle do laco i eh j
        temp = li[i]; //temp recebe o primeiro cara da lista ligada
        while(temp != NULL){ //percorre ate encontar o ultimo (vazio)
            V[j] = temp->dados; //copiando os dados para v[j]
            temp = temp->prox; //percorrendo pro prox
            j++; //controle do laco q ao invez de i eh j;
        }
	}

    /*printf("\n\nOrdenado Teste:\n");
	for(i = 0; i < tam; i++){
        printf("%d | ", i);
		printList(li[i]);
        printf("\n");
	}*/
}
