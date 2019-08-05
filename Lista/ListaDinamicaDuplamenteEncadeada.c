#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};//Definição do tipo lista

typedef struct elemento* Lista; //definindo **
typedef struct elemento Elem; //disendo q cada elemento se chamara Elem

//funcoes
Lista* cria_lista();
void libera_lista(Lista*);
int consulta_lista_pos(Lista*, int, tAluno*);
int consulta_lista_mat(Lista*, int, tAluno*);
int insere_lista_final(Lista*, tAluno);
int insere_lista_inicio(Lista*, tAluno);
int insere_lista_ordenada(Lista*, tAluno);
int remove_lista(Lista*, int);
int remove_lista_inicio(Lista*);
int remove_lista_final(Lista*);
int tamanho_lista(Lista*);
int lista_vazia(Lista*);
void imprime_lista(Lista*);

int main(){
    int i;
    Lista* li;
    tAluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
                       {4,"Ricardo",7.5,8.7,6.8},
                       {1,"Bianca",9.7,6.7,8.4},
                       {3,"Ana",5.7,6.1,7.4}};
    li = cria_lista();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));


    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);

    imprime_lista(li);
    printf("\nTamanho: %d\n\n\n\n",tamanho_lista(li));


    for(i=0; i < 4; i++){
        remove_lista_final(li);
        imprime_lista(li);
        printf("\nTamanho: %d\n\n\n\n",tamanho_lista(li));
    }

    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);

    imprime_lista(li);
    libera_lista(li);
    system("pause");
    return 0;
}

//(*li) = o que ele aponta
// *li o que esta sendo apontado

Lista* cria_lista(){
    Lista* li; //criando a cabeca da lista
    li = (Lista*) malloc(sizeof(Lista)); //alocando
    if(li != NULL)//foi bem sucedido?
        *li = NULL;//acabei de criar, portanto ela ta vazia
    return li;
}

void libera_lista(Lista* li){//libera a lista por completo
    if(li != NULL){//tem algum elemento na lista?
        Elem* no;//criando ponteiro ponteiro para apontar para o elemento que eu quero remover
        while((*li) != NULL){//minha cabeca aponta para o final (vazio, null?)
            no = *li;//auxiliar vai apontar para o mesmo elemento que a minha cabeca aponta
            *li = (*li)->prox;//minha cabeca vai apontar para o o mesmo lugar que o o elemento prox que ela aponta apontar
            free(no);//liberando o auxiliar (primeiro elemento da lista)
        }
        free(li);//toda memoria foi liberada
    }
}

int consulta_lista_pos(Lista* li, int pos, tAluno *al){
    if(li == NULL || pos <= 0)//lista é valida? A posisao informada eh valida?
        return 0;
    int i = 1;
    Elem *no;//criando ponteiro auxiliar para apontar para o elemento que eu quero remover
    no = *li;//auxiliar vai apontar para o mesmo elemento que a minha cabeca aponta

    while(no != NULL && i < pos){//ou voce percorre a lista toda ou voce percorre ate o elemento, note q i comeca com 1 de primeiro elemento
        no = no->prox;//caso nao seja quem eu procure, auxiliar aponta para o proximo
        i++;//conta em qual elemento eu to
    }
    if(no == NULL) // eu encontrei o elemento?
        return 0; //caso eu pecorri a lista toda e nao achei retorna falso
    else{
        *al = no->dados; //os dados do elemento serao passados para um tAluno
        return 1; //tAluno é meu retorno com o dados, o 1 eu consegui fazer tudo
    }
}

int consulta_lista_mat(Lista* li, int mat, tAluno *al){
    if(li == NULL)//lista valida?
        return 0;
    Elem *no = *li;//auxiliar vai apontar para o mesmo elemento que a minha cabeca aponta
    while(no != NULL && no->dados.matricula != mat){//cheguei no fim? achei a matricula?
        no = no->prox;//aponta para o prox elemento
    }
    if(no == NULL)//caso eu nao achei a matricula
        return 0;
    else{
        *al = no->dados;//os dados do elemento serao passados para um tAluno
        return 1;//tAluno é meu retorno com o dados, o 1 eu consegui fazer tudo
    }
}

int insere_lista_final(Lista* li, tAluno al){
    if(li == NULL) //lista valida?
        return 0;
    Elem *no; //criando ponteiro para o elemento
    no = (Elem*) malloc(sizeof(Elem)); //alocando
    if(no == NULL) // deu certo?
        return 0;
    no->dados = al; //recebendo dados que mandei como parametro
    no->prox = NULL;//ultimo da lista
    if((*li) == NULL){//lista vazia: insere início
        no->ant = NULL;//o anterior tambem é num, ja que ta vazia
        *li = no;//li agora aponta para no no
    }else{
        Elem *aux; //criando um auxiliar
        aux = *li; //aponta pra cabeca antes de pecorrer
        while(aux->prox != NULL){ //varre a lista ate o ultimo elemento
            aux = aux->prox;
        }
        aux->prox = no; //prox agora nao é mais null,eh o novo no
        no->ant = aux;//o anterior do no eh o auiliar q percorri
    }
    return 1; //ok
}

int insere_lista_inicio(Lista* li, tAluno al){
    if(li == NULL) //lista valida?
        return 0;
    Elem* no; //criando ponteiro para elemento a ser inserido
    no = (Elem*) malloc(sizeof(Elem)); // alocando elemento
    if(no == NULL)//consegui alocar?
        return 0;
    no->dados = al;//recebeos dados do aluno que eu mandei como parametro
    no->prox = (*li);//ele vai apontar pro mesmo que li aponta
    no->ant = NULL; //ja q e no inicio, nao ha anterior
    if(*li != NULL)//lista não vazia: apontar para o anterior!
        (*li)->ant = no; //o anterior para q li aponta eh o no novo
    *li = no; //li agora aponta para no
    return 1;
}

int insere_lista_ordenada(Lista* li, tAluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ante, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ante = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if(atual != NULL)
                atual->ant = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){//TERMINAR
    if(li == NULL) //lista valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *no = *li; //criando ponteiro q aponta pro inicio da lista
    while(no != NULL && no->dados.matricula != mat){//no procura quem ele quer ou vai ate o fim sem acahr
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no->ant == NULL)//remover o primeiro?
        *li = no->prox;
    else
        no->ant->prox = no->prox;//o anterior aponta pro cara q ta dpois do no

    if(no->prox != NULL)//não é o último?
        no->prox->ant = no->ant;

    free(no);//libera o q eu removi
    return 1; //ok
}


int remove_lista_inicio(Lista* li){
    if(li == NULL)// a lista eh valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;//criando ponteiro que aponta pro inicio da lista
    *li = no->prox;//faco  a cabeca apontar pro proximo
    if(no->prox != NULL)
        no->prox->ant = NULL; //faco o 2 q agr eh 1 apontar o anterior pro vazio

    free(no); //libero memoria e ok
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)// a lista eh valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;//criando ponteiro que aponta pro inicio da lista
    while(no->prox != NULL)
        no = no->prox; //procuro o ultimo elemento

    if(no->ant == NULL)//remover o primeiro e único
        *li = no->prox;
    else
        no->ant->prox = NULL; //o anterior q ele apontava eh null agora, e nao ele mais

    free(no); //libero mem
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)//lista valida?
        return 0;
    int cont = 0; //criando um contador para informar tamanho
    Elem* no = *li;//auxiliar para verificar final , comecar auxiliar aponta pro inicio
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;//a lista nunca vai encher
}

int lista_vazia(Lista* li){
    if(li == NULL)//lista valida? existe?
        return 1;
    if(*li == NULL)//lista vazia
        return 1;
    return 0;//tem algum
}

void imprime_lista(Lista* li){
    if(li == NULL)//lista valida?
        return;
    Elem* no = *li;//ponteiro que aponta pro inicio
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
