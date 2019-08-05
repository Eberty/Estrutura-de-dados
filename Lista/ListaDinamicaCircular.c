#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

struct elemento{
    tAluno dados;
    struct elemento *prox;
};//Definição do tipo lista

typedef struct elemento* Lista; //definindo o q vou usar como ponteiro para ponteiro
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
    tAluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                   {4,"Ricardo",7.5,8.7,6.8},
                   {1,"Bianca",9.7,6.7,8.4},
                   {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));

    for(i=0; i < 4; i++)
        insere_lista_inicio(li,a[i]);

    imprime_lista(li);
    printf("\nTamanho: %d\n\n\n\n ",tamanho_lista(li));

    for(i=-1; i < 5; i++){
        //remove_lista(li,i+1);
        if(!remove_lista(li,i+1)) //marticula 0 nao eziste , nem a 5
            printf("Erro!!!!!!!!!\n\n");
        imprime_lista(li);
        printf("\n\n======================\n\n");
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
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)//foi bem sucedido?
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL && (*li) != NULL){ //lista valida e nao vazia?
        Elem *aux, *no = *li;//craiando no e aux
        while((*li) != no->prox){ //enquanto nao circulei a lista
            aux = no;
            no = no->prox;
            free(aux);
        }
        free(no); //libera o no q criei, e a cabeca da lista
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, tAluno *al){
    if(li == NULL || (*li) == NULL || pos <= 0) //posicao valida? lista valida? lista vazia?
        return 0;
    Elem *no = *li;//criando ponteiro auxiliar para apontar para o elemento, comecando da cabeca
    int i = 1;
    while(no->prox != (*li) && i < pos){ //percorri a lista toda?a achei o elemnto?
        no = no->prox;
        i++;
    }
    if(i != pos) //se eu nao achei
        return 0;
    else{
        *al = no->dados; //se eu achei copio os dados para o al q passei como parametro
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, tAluno *al){
    if(li == NULL || (*li) == NULL) //lista valida? lista vazia?
        return 0;
    Elem *no = *li;//criando ponteiro auxiliar para apontar para o elemento, comecando da cabeca
    while(no->prox != (*li) && no->dados.matricula != mat) //procurando, ate o fim do circulo
        no = no->prox;
    if(no->dados.matricula != mat) //nao achei
        return 0;
    else{ //achei
        *al = no->dados;//se eu achei copio os dados para o al q passei como parametro
        return 1;
    }
}

int insere_lista_final(Lista* li, tAluno al){
    if(li == NULL) // lista valida?
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem)); //criando e alocando elemento
    if(no == NULL) //consegui alocar?
        return 0;
    no->dados = al; //passando dados para no;
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->prox = no; //para ele mesmo
    }else{
        Elem *aux = *li; //criando aux q comeca do inicio a percorrer
        while(aux->prox != (*li)){ //enquanto ainda nao a circulei toda
            aux = aux->prox;
        }//cheguei no fim
        aux->prox = no; //quando eu encontrei, faço meu prox do ultimo elemento apontar pro no que eu quero inserir
        no->prox = *li; //o prox do ultimo e o primeiro
    }
    return 1;
}

int insere_lista_inicio(Lista* li, tAluno al){
    if(li == NULL)// lista valida?
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));//criando e alocando elemento
    if(no == NULL)//consegui alocar?
        return 0;
    no->dados = al;//passando dados para no;
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->prox = no;//para ele mesmo
    }else{
        Elem *aux = *li;//criando aux q comeca do inicio a percorrer
        while(aux->prox != (*li)){
            aux = aux->prox;//enquanto ainda nao a circulei toda
        }//cheguei no fim
        aux->prox = no;//quando eu encontrei, faço meu prox do ultimo elemento apontar pro no que eu quero inserir
        no->prox = *li;//o prox do ultimo e o primeiro
        *li = no; //o ultimo virou o primeiro
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, tAluno al){
    if(li == NULL)//VALIDA?
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));//criando e alocando elemento
    if(no == NULL) //consegui alocar?
        return 0;
    no->dados = al;//passando dados pro no
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->prox = no;//para ele mesmo
        return 1;
    }else{
        if((*li)->dados.matricula > al.matricula){//insere início
            Elem *atual = *li;//atual eh o primeiro para percorrer lista
            while(atual->prox != (*li))//procura o último
                atual = atual->prox;
            no->prox = *li; //prox do q eu criei eh o inicio
            atual->prox = no; //prox do anterior e o cara q coloquei
            *li = no; //inicio
            return 1;
        }
        //insiro em qualquer lugar nao precisa do else por causa do return
        Elem *ant = *li; //anterior eh o primeiro
        Elem *atual = (*li)->prox; //atual eh o segundo
        while(atual != (*li) && atual->dados.matricula < al.matricula){ //vou ate o primeiro e pergunto se achei a posisao
            ant = atual;//avanca os 2
            atual = atual->prox;
        }
        ant->prox = no; //o prox do atual e o elemen
        no->prox = atual;//elemen agora e o atual
        return 1;
    }
}

int remove_lista_inicio(Lista* li){
    if(li == NULL) //lista valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//lista fica vazia (unico elemen)
        free(*li); //libera o elemento
        *li = NULL; //liagora eh null
        return 1; //ok
    }
    Elem *atual = *li; //atual aponta pro inicio
    while(atual->prox != (*li))//procura o último
        atual = atual->prox;//procura o ultimo

    Elem *no = *li;//fazendo o no aponta pro inicio para removelo
    atual->prox = no->prox; //pulando o no
    *li = no->prox; //lista agora eh o prox
    free(no);//livre
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL) //lista valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//lista fica vaza
        free(*li); //libera o q aponta
        *li = NULL; //aponta pra null
        return 1; //fim vazia
    }
    //else
    Elem *ant; //criando anterior
    Elem *no = *li; //no no inicio
    while(no->prox != (*li)){//procura o último
        ant = no; //anterior eh no
        no = no->prox; //no eh proximo
    }
    ant->prox = no->prox; //pula o no
    free(no);//libera no final
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)//lista valida?
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *no = *li; //criando no q aponta pro inicio
    if(no->dados.matricula == mat){//remover do início
        if(no == no->prox){//lista fica vaza
            free(no); //libera no
            *li = NULL;//cabeca eh null
            return 1;
        }else{
            Elem *ult = *li; //cria o ultimo no inicio q vai percorrer ate o ultimo
            while(ult->prox != (*li))//procura o último
                ult = ult->prox;
            ult->prox = (*li)->prox; //prox do ultimo eh o segundo da lista
            *li = (*li)->prox; //li agora aponta pro segundo
            free(no); //remove primeiro
            return 1;
        }
    }
    Elem *ant = no; //anterior recebe o msm lugar q no aponta
    no = no->prox; //pula o no
    while(no != (*li) && no->dados.matricula != mat){ //no diferente de li apontando e procurando a matricula esperando chegar no fim do circulo
        ant = no; //no ant
        no = no->prox; //prox
    }
    if(no == *li)//não encontrado
        return 0;

    ant->prox = no->prox; //pula o no
    free(no); //libera
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL || (*li) == NULL) //lista valida ou vazia?
        return 0;
    int cont = 0;//criando um contador para informar tamanho
    Elem* no = *li;//auxiliar para verificar final q comeca no inicio
    do{
        cont++; //somando
        no = no->prox; //prox
    }while(no != (*li)); //ate estar no primeiro novamente
    return cont; //qtd
}

int lista_vazia(Lista* li){
    if(li == NULL) //lista valida?
        return 1;
    if(*li == NULL) // lista vazia
        return 1;
    return 0; // tem algum
}

void imprime_lista(Lista* li){

    if(li == NULL || (*li) == NULL) //lista valida ou vazia?
        return;
    Elem* no = *li;//ponteiro que aponta pro inicio
    do{
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox; //passa pro proximo
    }while(no != (*li)); //enquanto no diferente do primeiro
}
