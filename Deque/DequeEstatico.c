#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
} tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct Deque{
    int inicio, final, qtd; //parecido com no descritor, posiçao inicial , qtd e final
    struct aluno dados[MAX];
} Deque;//Definição do tipo deque

Deque* cria_Deque();
void libera_Deque(Deque* dq);
int consultaInicio_Deque(Deque* dq, struct aluno *al);
int consultaFinal_Deque(Deque* dq, struct aluno *al);
int insereInicio_Deque(Deque* dq, struct aluno al);
int insereFinal_Deque(Deque* dq, struct aluno al);
int removeInicio_Deque(Deque* dq);
int removeFinal_Deque(Deque* dq);
int tamanho_Deque(Deque* dq);
int Deque_vazio(Deque* dq);
int Deque_cheio(Deque* dq);
void imprime_Deque(Deque* dq);

int main(){
    Deque* dq = cria_Deque();
    int i;

    tAluno al,a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    printf("Tamanho: %d\n\n\n",tamanho_Deque(dq)); //nao adicionei nada ainda tamanho 0

    for(i=0; i < 4; i++){
        insereInicio_Deque(dq,a[i]);
        consultaInicio_Deque(dq,&al);
        printf("Consulta (inicio): %d - %s\n", al.matricula, al.nome); //so consulta o primeiro que ainda nao removi
    }

    printf("\n\n------------\n");
    imprime_Deque(dq);
    printf("Tamanho: %d\n\n", tamanho_Deque(dq));


    for(i=0; i < 4; i++){
        removeFinal_Deque(dq);
        if (consultaFinal_Deque(dq,&al))
            printf("Consulta (final): %d - %s\n", al.matricula, al.nome); //erro do ultimo corrigido
    }
    printf("Tamanho: %d\n\n\n\n", tamanho_Deque(dq));
    imprime_Deque(dq);

    for(i=0; i < 4; i++)
        insereFinal_Deque(dq,a[i]);

    printf("Tamanho: %d\n\n\n\n", tamanho_Deque(dq));
    imprime_Deque(dq);

    libera_Deque(dq);
    system("pause");
    return 0;
}

Deque* cria_Deque(){
    Deque *dq; //ponteiro para alocar
    dq = (Deque*) malloc(sizeof(struct Deque)); //alocacao dinamica
    if(dq != NULL){ //se valida possui 0 elementos, todo mundo eh 0 ate os indices.
        dq->inicio = 0;
        dq->final = 0;
        dq->qtd = 0;
    }
    return dq; //retorna o ponteiro para o primeiro elemento
}

void libera_Deque(Deque* dq){
    free(dq); //libera a alocacao que so foi feita uma vez
}

int consultaInicio_Deque(Deque* dq, struct aluno *al){
    if(dq == NULL || Deque_vazio(dq)) //Deque valido? Deque vazio? se for vazio deve retornar 0
        return 0;
    *al = dq->dados[dq->inicio]; //o que al aponta agora vale os dados do aluno da posiçao inicial que eu nao sei qual eh
    return 1;
}

int consultaFinal_Deque(Deque* dq, struct aluno *al){
    if(dq == NULL || Deque_vazio(dq)) //Deque valido? Deque vazio? se for vazio deve retornar 0
        return 0;
    int pos = dq->final-1; //corecao do ultimo
    if (pos < 0) //caso o i=0 for o final (acesso ao final)
        pos = MAX-1;
    *al = dq->dados[pos]; //o que al aponta agora vale os dados do aluno da posiçao final que eu nao sei qual eh
    return 1;
}

int insereInicio_Deque(Deque* dq, struct aluno al){
    if(dq == NULL || Deque_cheio(dq)) //Deque valido? Deque cheio?
        return 0;
    dq->inicio--; //insiro antes do antigo inicio
    if (dq->inicio < 0) //corrige o fato do antigo inicio for 0, devido a lista ser circular
        dq->inicio = MAX-1;
    dq->dados[dq->inicio] = al; //inicio aponta pra posicao onde vou inserir os dados
    dq->qtd++; //almento a quantidade
    return 1; //ok
}

int insereFinal_Deque(Deque* dq, struct aluno al){
    if(dq == NULL || dq->qtd == MAX) //Deque valido? Deque cheio?
        return 0;
    dq->dados[dq->final] = al; //o final que era a ultima posicao valida agora ta ocupado
    dq->final = (dq->final+1)%MAX; //o pinal agora eh somado a 1, o %MAX serve para fazer da Deque circular
    dq->qtd++; //almento a quantidade
    return 1; //ok
}

int removeInicio_Deque(Deque* dq){
    if(dq == NULL || Deque_vazio(dq)) //nao posso remover de uma Deque invalida, e nem de uma Deque vazio
        return 0;
    dq->inicio = (dq->inicio+1)%MAX; //libero a posiçao onde estava o inicio, ou seja o inicial agora eh o proximo, o %max eh  lista circular
    dq->qtd--; //diminuo a qtd uma vez q eu removi alguem
    return 1;
}

int removeFinal_Deque(Deque* dq){
    if(dq == NULL || Deque_vazio(dq)) //nao posso remover de uma Deque invalida, e nem de uma Deque vazio
        return 0;
    dq->final--; //removo o ultimo
    if (dq->final < 0) //corrige o fato do antigo final for 0, devido a lista ser circular
        dq->final = MAX-1;
    dq->qtd--; //diminuo a qtd uma vez q eu removi alguem
    return 1;
}

int tamanho_Deque(Deque* dq){
    if(dq == NULL) //deque valido?
        return -1;
    return dq->qtd; //graças ao no descritor
}

int Deque_cheio(Deque* dq){
    if(dq == NULL) //deque valido?
        return -1; //mostrar erro
    if (dq->qtd == MAX) //se estiver cheio
        return 1;
    else
        return 0; //se nao estiver cheio
}

int Deque_vazio(Deque* dq){
    if(dq == NULL)//Deque valido?
        return -1;//mostrar erro
    if (dq->qtd == 0)
        return 1; //se estiver vaizia (qtd, e nao subtracao)
    else
        return 0; //se estiver com algum elemento
}

void imprime_Deque(Deque* dq){
    if(dq == NULL)//Deque valida?
        return;
    int n, i = dq->inicio; //o n eh a variavel contadora, que vai ate a qtd de elementos e i indica a posicao
    for(n=0; n < dq->qtd; n++){
        printf("Matricula: %d\n",dq->dados[i].matricula);
        printf("Nome: %s\n",dq->dados[i].nome);
        printf("Notas: %f %f %f\n",dq->dados[i].n1,
                                   dq->dados[i].n2,
                                   dq->dados[i].n3);
        printf("-------------------------------\n");
        i = (i + 1) % MAX; //garante percorrer a Deque em forma circular
    }
}

