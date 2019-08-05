#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno;

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};//Definição do tipo Pilha

typedef struct elemento* Pilha; //definindo um nome para a cabeca q ira apontar pros elementos
typedef struct elemento Elem; //typdef do elemento


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

    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));

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

//(*pi) = o que ele aponta
// *pi o que esta sendo apontado

Pilha* cria_Pilha(){
    Pilha* pi;//criando cabeca da pilha
    pi = (Pilha*) malloc(sizeof(Pilha)); //alocando
    if(pi != NULL) //foi bem sucedido?
        *pi = NULL; //acabei de criar, portanto ela ta vazia
    return pi;
}

void libera_Pilha(Pilha* pi){ //libera pilha por completo
    if(pi != NULL){ //tem algum elemento na pilha?
        Elem* no; //criando ponteiro auxiliar para apontar para o elemento que eu quero remover
        while((*pi) != NULL){//minha cabeca aponta para o final (vazio, null?)
            no = *pi;//auxiliar vai apontar para o mesmo elemento que a minha cabeca aponta
            *pi = (*pi)->prox;//minha cabeca vai apontar para o o mesmo lugar que o o elemento prox que ela aponta apontar
            free(no);//liberando o auxiliar (primeiro elemento da lista) - ultimo q coloquei
        }
        free(pi);//toda memoria foi liberada
    }
} //nota: o primerio eh o ultimo, deveido a forma que eu inseri

int consulta_topo_Pilha(Pilha* pi, struct aluno *al){ //consulta o 1
    if(pi == NULL) //lista valida?
        return 0;
    if((*pi) == NULL) //lista vazia?
        return 0;
    *al = (*pi)->dados; //aceso os dados do ultimop cara que coloqui, e agora eh o primeiro
    return 1; //ok
}

int insere_Pilha(Pilha* pi, struct aluno al){ //insere no inicio
    if(pi == NULL) //pilha valida?
        return 0;
    Elem* no; //criando ponteiro para elemento que será alocado e depois inserido na lista
    no = (Elem*) malloc(sizeof(Elem)); //alocando o elemento
    if(no == NULL) //consegui alocar?
        return 0;
    no->dados = al; //recebeos dados do aluno que eu mandei como parametro
    no->prox = (*pi); //ele vai apontar pro mesmo que li aponta
    *pi = no; //li agora aponta pro meu no, sendo ele agora o topo
    return 1;
}

int remove_Pilha(Pilha* pi){ //remove o primeiro
    if(pi == NULL) //pilha valida?
        return 0;
    if((*pi) == NULL) //pilha vazia?
        return 0;
    Elem *no = *pi;//criando ponteiro que aponta pro inicio da pilha
    *pi = no->prox;//faco  a cabeca apontar pro proximo elemento
    free(no); //elimino o topo
    return 1;
}

int tamanho_Pilha(Pilha* pi){
    if(pi == NULL) //pilha valida?
        return 0;
    int cont = 0; //criando contador para informar o tamanho
    Elem* no = *pi;//auxiliar que comeca do inicio e vai ate o final percorrendo um por um elemento
    while(no != NULL){ //enquanto ele nao chegou no final
        cont++; //somando
        no = no->prox; //prox
    }
    return cont; //quantidade
}

int Pilha_cheia(Pilha* pi){
    return 0; //a pilha nunca vai ta cheia porque a alocacao eh dinamica
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL) //pilha valida?
        return 1;
    if(*pi == NULL)//pilha vazia?
        return 1;
    return 0; //tem algum
}

void imprime_Pilha(Pilha* pi){ //imprime pilha
    if(pi == NULL) //pilha valida
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox; //passa pro prox depois de imprimir
    }
}
