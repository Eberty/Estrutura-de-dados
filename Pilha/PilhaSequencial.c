#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct pilha{
    int qtd;
    struct aluno dados[MAX];
}Pilha;//Definição do tipo Pilha

Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);

int main(){
    Pilha* pi = cria_Pilha();
    int i;
    tAluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    printf("Tamanho: %d\n\n\n",tamanho_Pilha(pi));

    for(i=0; i < 4; i++)
        insere_Pilha(pi,a[i]);

    imprime_Pilha(pi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));

    for(i=0; i < 4; i++)
        remove_Pilha(pi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));
    imprime_Pilha(pi);

    for(i=0; i < 4; i++)
        insere_Pilha(pi,a[i]);

    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));
    imprime_Pilha(pi);

    libera_Pilha(pi);
    system("pause");
    return 0;
}


Pilha* cria_Pilha(){
    Pilha *pi; //ponteiro para alocar
    pi = (Pilha*) malloc(sizeof(struct pilha)); //alocacao dinamica
    if(pi != NULL) //se valida, possui 0 elementos
        pi->qtd = 0;
    return pi;
}

void libera_Pilha(Pilha* pi){
    free(pi); //libera a alocacao q so foi feita 1 vez
}

int consulta_topo_Pilha(Pilha* pi, struct aluno *al){ //como eh pilha, so posso consultar o q ta em ultimo
    if(pi == NULL || pi->qtd == 0) //verifico se a pilha eh valida ou se esta vazia
        return 0; //erro
    *al = pi->dados[pi->qtd-1]; //os dados seram copiados para a variavel q mandei o endereço (o ultimo eh a qtd -1)
    return 1; //ok
}

int insere_Pilha(Pilha* pi, struct aluno al){
    if(pi == NULL) //pilha valida?
        return 0;
    if(pi->qtd == MAX)//pilha cheia
        return 0;
    pi->dados[pi->qtd] = al; //inserindo na posiçao quantidade
    pi->qtd++; //incrementa a qtd
    return 1; //ok
}

int remove_Pilha(Pilha* pi){
    if(pi == NULL || pi->qtd == 0) //pilha valida? possui elementos?
        return 0;
    pi->qtd--; //diminui a quantidade da struct
    return 1; //ok, removi o ultimo
}

int tamanho_Pilha(Pilha* pi){
    if(pi == NULL) //lista valida?
        return -1; //erro
    else
        return pi->qtd; //retorna a qtd da pilha
}

int Pilha_cheia(Pilha* pi){
    if(pi == NULL) //pilha existe?
        return -1;
    return (pi->qtd == MAX);//se ==MAX retorna 1 verdadeiro, senao falso
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL)//pilha existe?
        return -1;
    return (pi->qtd == 0);//se ==0 retorna 1 verdadeiro, senao falso
}

void imprime_Pilha(Pilha* pi){
    if(pi == NULL)//pilha existe?
        return;
    int i;
    for(i=pi->qtd-1; i >=0; i--){ //imprimindo dado de cada 1
        printf("Matricula: %d\n",pi->dados[i].matricula);
        printf("Nome: %s\n",pi->dados[i].nome);
        printf("Notas: %f %f %f\n",pi->dados[i].n1,
                                   pi->dados[i].n2,
                                   pi->dados[i].n3);
        printf("-------------------------------\n");
    }
}
