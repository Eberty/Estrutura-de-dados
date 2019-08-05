#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct lista{
    int qtd;
    tAluno dados[MAX];
}Lista;//Definição do tipo lista, estatica com max quantidade de dados, eu vou alocar e acecar ela atraves de um ponteiro lista

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
int lista_cheia(Lista*);
int lista_vazia(Lista*);
void imprime_lista(Lista*);

int remove_lista_otimizado(Lista*, int);

int main(){
    Lista *li;
    int i;
    tAluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    li = cria_lista();
    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);

    imprime_lista(li);
    printf("\n\n\n\n");

    for(i=0; i < 5; i++){
        if (!remove_lista_otimizado(li,i))
            printf("Erro\n"); //matricula 0?
        //imprime invertido dps do erro
        imprime_lista(li);
        printf("\n\n\n\n");
    }

    libera_lista(li);
    system("pause");
    return 0;
}

Lista* cria_lista(){
    Lista *li; //ponteiro para alocar
    li = (Lista*) malloc(sizeof(struct lista));//alocacao dinamica
    if(li != NULL) //se valida possui 0 elementos
        li->qtd = 0;
    return li; //retorna ponteiro para o 1 elemento
}

void libera_lista(Lista* li){
    free(li); //libera a alocacao q so foi feita 1 vez
}

int consulta_lista_pos(Lista* li, int pos, tAluno* al){
    if(li == NULL || pos <= 0 ||  pos > li->qtd)  //lista valida? posisao valida? maior q 0 e menor q qtd
        return 0; //erro
    *al = li->dados[pos-1]; //oq al aponta agora vai valer os dados do aluno q u achei
    return 1; //ok
}

int consulta_lista_mat(Lista* li, int mat, tAluno* al){
    if(li == NULL) //lista valida?
        return 0;
    int i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)//ate eu achar a matricula ou ate percorrer toda a quantidade
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    *al = li->dados[i]; //al recebe todos os dados q eu achei
    return 1; //ok
}

int insere_lista_final(Lista* li, tAluno al){
    if(li == NULL) //lista valida?
        return 0;
    if(li->qtd == MAX)//lista cheia
        return 0;
    li->dados[li->qtd] = al; //inserindo na posisao quantidade
    li->qtd++; //incrementando a quantidade
    return 1; //ok
}

int insere_lista_inicio(Lista* li, tAluno al){
    if(li == NULL) //valida
        return 0;
    if(li->qtd == MAX)//lista cheia
        return 0;
    int i;
    for(i=li->qtd-1; i>=0; i--) //i comeca do ultimo ate o primeiro
        li->dados[i+1] = li->dados[i]; //cada um nsobe uma casa
    li->dados[0] = al; //substitui o da casa 0
    li->qtd++;//almenta qtd
    return 1;//ok
}

int insere_lista_ordenada(Lista* li, tAluno al){
    if(li == NULL) //lista valida?
        return 0;
    if(li->qtd == MAX)//lista cheia?
        return 0;
    int k,i = 0;
    while(i<li->qtd && li->dados[i].matricula < al.matricula)//i incrementa ate chegar na ordem q quer ou ate o fim
        i++;

    for(k=li->qtd-1; k >= i; k--) //substitui k ate chegar na posiçao i (do fim pro inicio)
        li->dados[k+1] = li->dados[k];

    li->dados[i] = al; //substitui a posicao i
    li->qtd++; //ok e +1
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL) //lista valida?
        return 0;
    if(li->qtd == 0) //lista vazia?
        return 0;
    int k,i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat) //i incrementa ate chegar na ordem q quer ou ate o fim
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    for(k=i; k< li->qtd-1; k++) //substitui k pelo prox e assim sucesivamente
        li->dados[k] = li->dados[k+1];
    li->qtd--; //ok e qtd -1
    return 1;
}

int remove_lista_otimizado(Lista* li, int mat){
    if(li == NULL)//lista valida?
        return 0;
    if(li->qtd == 0)//lista vazia?
        return 0;
    int i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)//i incrementa ate chegar na ordem q quer ou ate o fim
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    li->qtd--;
    li->dados[i] = li->dados[li->qtd]; //o ultimo vai pro q eu removi
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)//lista valida?
        return 0;
    if(li->qtd == 0)//lista vazia?
        return 0;
    int k = 0;
    for(k=0; k< li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];//substitui o 1 pelo prox e assim sucessivamente
    li->qtd--; //diminui a qtd
    return 1;//ok
}

int remove_lista_final(Lista* li){
    if(li == NULL) //lista valida?
        return 0;
    if(li->qtd == 0) //tem algum elemento na lista?
        return 0;
    li->qtd--; //diminuir quantidade da struct lista
    return 1; //pronto
}

int tamanho_lista(Lista* li){
    if(li == NULL) //lista valida?
        return -1; //mostrar erro
    else
        return li->qtd; //na struct lista a qual li aponta tem a quantidade
}

int lista_cheia(Lista* li){
    if(li == NULL)//lista exite?
        return -1; //mostrar erro
    return (li->qtd == MAX);//se ==MAX retorna 1 verdadeiro, senao falso
}

int lista_vazia(Lista* li){
    if(li == NULL) //lista exite?
        return -1;
    return (li->qtd == 0); //se ==0 retorna 1 verdadeiro, senao falso
}

void imprime_lista(Lista* li){
    int i;
    if(li == NULL)//lista valida?
        return;
    for(i=0; i< li->qtd; i++){
        printf("Matricula: %d\n",li->dados[i].matricula);
        printf("Nome: %s\n",li->dados[i].nome);
        printf("Notas: %f %f %f\n",li->dados[i].n1,
                                   li->dados[i].n2,
                                   li->dados[i].n3);
        printf("-------------------------------\n");
    }
}
