#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct fila{
    int inicio, final, qtd; //parecido com no descritor, posiçao inicial , qtd e final
    struct aluno dados[MAX];
}Fila;//Definição do tipo Fila

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

int main(){
    Fila* fi = cria_Fila();
    int i;

    tAluno al,a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi)); //nao adicionei nada ainda tamanho 0

    for(i=0; i < 4; i++){
        insere_Fila(fi,a[i]);
        consulta_Fila(fi,&al);
        printf("Consulta: %d - %s\n\n\n",al.matricula,al.nome); //so consulta o primeiro que ainda nao removi
    }

    imprime_Fila(fi);
    printf("Tamanho: %d\n\n",tamanho_Fila(fi));

    for(i=0; i < 4; i++){
        remove_Fila(fi);
        if (consulta_Fila(fi,&al))
            printf("Consulta: %d - %s\n",al.matricula,al.nome); //erro do ultimo corrigido
    }
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    for(i=0; i < 4; i++)
        insere_Fila(fi,a[i]);

    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    libera_Fila(fi);
    system("pause");
    return 0;
}

Fila* cria_Fila(){
    Fila *fi; //ponteiro para alocar
    fi = (Fila*) malloc(sizeof(struct fila)); //alocacao dinamica
    if(fi != NULL){ //se valida possui 0 elementos, todo mundo eh 0 ate os indices.
        fi->inicio = 0;
        fi->final = 0;
        fi->qtd = 0;
    }
    return fi; //retorna o ponteiro para o primeiro elemento
}

void libera_Fila(Fila* fi){
    free(fi); //libera a alocacao que so foi feita uma vez
}

int consulta_Fila(Fila* fi, struct aluno *al){ //so pode consultar o primeiro da fila
    if(fi == NULL || Fila_vazia(fi)) //fila valida? fila vazia? se for vazia deve retornar 0
        return 0;
    *al = fi->dados[fi->inicio]; //o que al aponta agora vale os dados do aluno da posiçao inicial que eu nao sei qual eh
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL) //fila valida?
        return 0;
    if(Fila_cheia(fi)) //fila cheia?
        return 0;
    fi->dados[fi->final] = al; //o final que era a ultima posicao valida agora ta ocupado
    fi->final = (fi->final+1)%MAX; //o pinal agora eh somado a 1, o %MAX serve para fazer da fila circular
    fi->qtd++; //almento a quantidade
    return 1; //ok
}

int remove_Fila(Fila* fi){
    if(fi == NULL || Fila_vazia(fi)) //nao posso remover de uma fila invalida, e nem de uma fila vazia
        return 0;
    fi->inicio = (fi->inicio+1)%MAX; //libero a posiçao onde estava o inicio, ou seja o inicial agora eh o proximo, o %max eh  lista circular
    fi->qtd--; //diminuo a qtd uma vez q eu removi alguem
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL) //
        return -1;
    return fi->qtd;
}

int Fila_cheia(Fila* fi){
    if(fi == NULL) //lista valida?
        return -1; //mostrar erro
    if (fi->qtd == MAX) //se estiver cheia
        return 1;
    else
        return 0; //se nao estiver cheia
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)//fila valida?
        return -1;
    if (fi->qtd == 0)//mostrar erro
        return 1; //se estiver vaizia (qtd, e nao subtracao)
    else
        return 0; //se estiver com algum elemento
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)//fila valida?
        return;
    int n, i = fi->inicio; //o n eh a variavel contadora, que vai ate a qtd de elementos e i indica a posicao
    for(n=0; n < fi->qtd; n++){
        printf("Matricula: %d\n",fi->dados[i].matricula);
        printf("Nome: %s\n",fi->dados[i].nome);
        printf("Notas: %f %f %f\n",fi->dados[i].n1,
                                   fi->dados[i].n2,
                                   fi->dados[i].n3);
        printf("-------------------------------\n");
        i = (i + 1) % MAX; //garante percorrer a fila em forma circular
    }
}

