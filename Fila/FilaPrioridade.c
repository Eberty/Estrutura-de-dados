#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct paciente{
    char nome[30];
    int prio;
}Paciente; //definindo o tipo paciente com nome e prioridade

typedef struct fila_prioridade{
    int qtd; //quantidade
    Paciente dados[MAX]; //vetor estatico
}FilaPrio;

//funcoes
FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int consulta_FilaPrio(FilaPrio* fp, char* nome);
int insere_FilaPrio(FilaPrio* fp, char *nome, int  prioridade);
int remove_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);
void imprime_FilaPrio(FilaPrio* fp);

int main(){
    struct paciente itens[6] = {{"Andre",1}, {"Bianca",2}, {"Carlos",5}, {"Nilza",8}, {"Inacio",6}, {"Edu",4}};
    int i;
    FilaPrio* fp = cria_FilaPrio();

    for (i=0; i< 6; i++){
        printf("%d) %d %s\n",i,itens[i].prio, itens[i].nome);
        insere_FilaPrio(fp, itens[i].nome,itens[i].prio);
    }

    printf("=================================\n");
    imprime_FilaPrio(fp);//depois de inserir como ficou

    printf("=================================\n");
    for (i=0; i< 6; i++){
        remove_FilaPrio(fp);
        imprime_FilaPrio(fp);
        printf("=================================\n");
    }

    libera_FilaPrio(fp);//libero tudo

    system("pause");
    return 0;
}

FilaPrio* cria_FilaPrio(){
    FilaPrio *fp;//ponteiro para alocar
    fp = (FilaPrio*) malloc(sizeof(FilaPrio));//alocacao dinamica
    if(fp != NULL)//se valida possui 0 elementos
        fp->qtd = 0;
    return fp;//retorna ponteiro para o 1 elemento
}

void libera_FilaPrio(FilaPrio* fp){
    free(fp);//como eh estatica, eu so uso um free
}

int consulta_FilaPrio(FilaPrio* fp, char* nome){
    if(fp == NULL || fp->qtd == 0) //fila valida? tem alguem na fila?
        return 0;
    strcpy(nome,fp->dados[fp->qtd-1].nome);//como eh fila so copia o 1
    return 1;
}

int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade){
    if(fp == NULL)//fila valida?
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;

    int i = fp->qtd-1; //o de maior prio ta no fim do array, vou voutando ate sBER ONDE IN SERIR
    while(i >= 0 && fp->dados[i].prio >= prioridade){ //enquanto nao chegeui no inicio do array a prio ain da for maior
        fp->dados[i+1] = fp->dados[i];//desloca
        i--; //deminui procurando menor prio
    }
    //agora so colocar o cara la
    strcpy(fp->dados[i+1].nome,nome);//a posicao i+1 ta livre (repetida)
    fp->dados[i+1].prio = prioridade;//copia a prioridade
    fp->qtd++;//adicionei 1
    return 1;//ok
}

int remove_FilaPrio(FilaPrio* fp){
    if(fp == NULL)//fila valida?
        return 0;
    if(fp->qtd == 0)//fila vazia
        return 0;
    fp->qtd--; //eh uma fila, so posso remover o ultimo (maior prioridade) - q na verdade eh o 1 da fila
    return 1;
}

int tamanho_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao existir
        return -1; //erro
    else
        return fp->qtd; //quantidade eh o tamanho
}

int estaCheia_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao existir
        return -1; //erro
    return (fp->qtd == MAX); //se qtd for igual ao tamanho do vetor q defini
}

int estaVazia_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao exitir
        return -1; //erro
    return (fp->qtd == 0); //so ta vazia se qtd for = a 0
}

void imprime_FilaPrio(FilaPrio* fp){
    if(fp == NULL)//fila existe?
        return;
    int i;//contador
    for(i=fp->qtd-1; i >=0 ; i--){ //do ultimo ate o primeiro
        printf("Prio: %d \tNome: %s\n",fp->dados[i].prio,fp->dados[i].nome);
    }
}
