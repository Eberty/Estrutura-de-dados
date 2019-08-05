#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
} Elem;//Definição do tipo deque

typedef struct Deque{ //definicao do No descritor do Deque
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
} Deque;//Definição do tipo deque

/**Funções**/
Deque* cria_Deque();
void libera_Deque(Deque*);
int consultaInicio_Deque(Deque*, tAluno*);
int consultaFinal_Deque(Deque*, tAluno*);

int insereInicio_Deque(Deque*, tAluno);
int insereFinal_Deque(Deque*, tAluno);
int removeInicio_Deque(Deque*);
int removeFinal_Deque(Deque*);

int tamanho_Deque(Deque*);
int deque_cheio(Deque*);
int deque_vazio(Deque*);
void imprime_Deque(Deque*);

/**Exemplo Teste**/
int main(){
    int i;
    Deque* dq;
    tAluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
                       {4,"Ricardo",7.5,8.7,6.8},
                       {1,"Bianca",9.7,6.7,8.4},
                       {3,"Ana",5.7,6.1,7.4}};
    dq = cria_Deque();
    printf("Tamanho: %d\n\n\n", tamanho_Deque(dq));


    for(i=0; i < 4; i++)
        insereInicio_Deque(dq, a[i]);

    imprime_Deque(dq);
    printf("\nTamanho: %d\n\n\n", tamanho_Deque(dq));


    for(i=0; i < 4; i++){
        removeFinal_Deque(dq);
        imprime_Deque(dq);
        printf("\nTamanho: %d\n\n\n", tamanho_Deque(dq));
    }

    for(i=0; i < 4; i++)
        insereFinal_Deque(dq, a[i]);

    imprime_Deque(dq);
    libera_Deque(dq);

    system("pause");
    return 0;
}

//(*dq) = o que ele aponta
// *dq o que esta sendo apontado

Deque* cria_Deque(){
    Deque* dq = (Deque*) malloc(sizeof(Deque)); //cria e aloca ponteiro para no descritor
    if(dq != NULL){ //consegui alocar
        dq->inicio = NULL; //td mundo eh null e nao tem elemento
        dq->final = NULL;
        dq->qtd = 0;
    }
    return dq;
}

void libera_Deque(Deque* dq){
    if(dq != NULL){ //Deque valido?
        Elem* no; //cria no auxiliar pra remover
        while((dq->inicio) != NULL){ //inicio do Deque == null? liberacao interna
            no = dq->inicio; //no aponta pro inicio
            dq->inicio = dq->inicio->prox; //inicio agr eh prox
            free(no); // libera elemento
        }
        free(dq); //libera o Deque vazio == liberacao final
    }
}

int consultaInicio_Deque(Deque* dq, tAluno* al){
    if (dq == NULL || deque_vazio(dq))  //deque valido? esta vazio?
        return 0;
    *al = dq->inicio->dados; //passa os dados do inicio
    return 1; //ok
}

int consultaFinal_Deque(Deque* dq, tAluno* al){
    if (dq == NULL || deque_vazio(dq)) //deque valido? esta vazio?
        return 0;
    *al = dq->final->dados; //passa os dados do final
    return 1; //ok
}

int insereInicio_Deque(Deque* dq, tAluno al){
    if(dq == NULL) //Deque valida?
        return 0;
    Elem* no; //criando ponteiro para elemento a ser inserido
    no = (Elem*) malloc(sizeof(Elem)); // alocando elemento
    if(no == NULL)//consegui alocar?
        return 0; //problema

    no->dados = al;//recebe os dados do aluno que eu mandei como parametro
    no->prox = dq->inicio;//ele vai apontar pro mesmo que dq aponta (ele eh o novo inicio)
    no->ant = NULL; //ja q e no inicio, nao ha anterior
    if(dq->inicio == NULL) //deque vazio
        dq->final = no; //so tem esse elemento
    else //Deque nao vazio: apontar para o anterior
        dq->inicio->ant = no; // o cara q era o inicio, o anterior dele será o novo no
    dq->inicio = no; //insere no inicio
    dq->qtd++; //inserido: qtd +1
    return 1;
}

int insereFinal_Deque(Deque* dq, tAluno al){
    if(dq == NULL) //Deque valido?
        return 0;
    Elem *no; //criando ponteiro para o elemento
    no = (Elem*) malloc(sizeof(Elem)); //alocando
    if(no == NULL) // deu certo?
        return 0;
    no->dados = al; //recebendo dados que mandei como parametro
    no->prox = NULL;//ultimo do Deque

    if(dq->final == NULL){//Deque vazio: insere início
        no->ant = NULL;//o anterior tambem é num, ja que ta vazia
        dq->inicio = no;//dq agora aponta para no no
    }else{
        no->ant = dq->final; //no vai ser o ultimo, o anigo final e o anterior do ultimo
        dq->final->prox = no; //no agora eh o final
    }

    dq->final = no; //no agora eh o fim
    dq->qtd++; //inseri
    return 1; //ok
}

int removeInicio_Deque(Deque* dq){
    if(dq == NULL || deque_vazio(dq)) //Deque eh valido? deque vazio?
        return 0;

    Elem *no = dq->inicio; //crio um no auxiliar q aponta pro inicio
    dq->inicio = dq->inicio->prox; //inicio agr eh prox

    if(dq->inicio == NULL) //ficou vazio?
        dq->final = NULL; //final tb vai ficar null
    else
        dq->inicio->ant = NULL; //o anterior ao inicio nao aponta mais pro cara q vou remover

    free(no); //libera o auxiliar
    dq->qtd--; //removido
    return 1; //ok
}

int removeFinal_Deque(Deque* dq){
    if(dq == NULL || deque_vazio(dq)) //Deque eh valido? deque vazio?
        return 0;
    Elem *no = dq->final; //crio um no auxiliar q aponta pro final

    if(no == dq->inicio){ //remover primeiro? o deque vai ficar vazio
        dq->inicio = NULL; //inicio vai ficar null
        dq->final = NULL; //final tb vai ficar null
    }else{
        no->ant->prox = NULL; // o anterior dele vai apontar pra null como proximo elemento
        dq->final = no->ant; //o final e o penultimo
    }

    free(no); //libera o auxiliar
    dq->qtd--; //removido
    return 1; //ok
}

int tamanho_Deque(Deque* dq){
    if(dq == NULL) //valido?
        return 0;
    return dq->qtd; //ponto pro descritor
}

int deque_cheio(Deque* dq){
    return 0;//o Deque nunca vai encher (memoria)
}

int deque_vazio(Deque* dq){
    if(dq == NULL) //valido?
        return 1;
    if(dq->inicio == NULL) //vazio? posso olhar qtd tambem
        return 1;
    return 0;//tem algum
}

void imprime_Deque(Deque* dq){
    if(dq == NULL || dq->inicio == NULL) //deque valida ou vazia?
        return;
    Elem* no = dq->inicio; //ponteiro q aponta pro inicio
    while(no != NULL){ //caso nao cheguei no fim ainda faz:
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
