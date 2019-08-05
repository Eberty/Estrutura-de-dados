#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}tAluno; //fazendo estrutura aluno para armazemar dados de um aluno

typedef struct elemento{
    tAluno dados;
    struct elemento *prox;
}Elem;//Definição do tipo Fila

typedef struct fila{
    Elem *inicio;
    Elem *final;
    int qtd;
}Fila;//Definição do Nó Descritor da Fila


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

    printf("\nTamanho: %d\n\n",tamanho_Fila(fi));

    for(i=0; i < 4; i++){
        insere_Fila(fi,a[i]);

        if(Fila_vazia(fi))
            printf("Erro!!!!!!\n");

        consulta_Fila(fi,&al);
        printf("Consulta: %d \t %s\n",al.matricula,al.nome);
    }

    imprime_Fila(fi);
    printf("\nTamanho: %d\n\n",tamanho_Fila(fi));

    for(i=0; i < 4; i++){
        remove_Fila(fi);
        if (consulta_Fila(fi,&al))
            printf("Consulta: %d \t %s\n",al.matricula,al.nome);
    }

    printf("\nTamanho: %d\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    for(i=0; i < 4; i++)
        insere_Fila(fi,a[i]);

    printf("\nTamanho: %d\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    libera_Fila(fi);
    system("pause");
    return 0;
}

Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));//cria e aloca ponteiro para no descritor
    if(fi != NULL){ //consegui alocar
        fi->final = NULL;//td mundo eh nul e nao tem elemento
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){ //fila valida?
        Elem* no;//cria no auxiliar pra remover
        while(fi->inicio != NULL){ //enquanto o inicio nao apontar pro final - vazia, faz:
            no = fi->inicio; //no aponta pro inicio
            fi->inicio = fi->inicio->prox; //inicio agora eh o proximo
            free(no); //libera elemento
        }
        free(fi); //libera fila
    }
}

int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL)//fila valida?
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    *al = fi->inicio->dados;//como eh uma fila, so posso consultar o primeiro
    return 1;//ok
}

int insere_Fila(Fila* fi, struct aluno al){ //insere lista final
    if(fi == NULL) //fila valida?
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem)); //cria e aloca elemento para inserir
    if(no == NULL) //consegui alocar?
        return 0;
    no->dados = al; //recebe os dados
    no->prox = NULL; //ele deve ser o ultimo, portanto aponta para o final (ninguem, null)
    if(fi->final == NULL)//fila vazia: insere no inicio
        fi->inicio = no; //so tem esse elemento a fila agora
    else
        fi->final->prox = no;//o ultimo aponta pro no
    fi->final = no; //agora no eh o ultimoi
    fi->qtd++; //inseri com sucesso
    return 1; //ok
}

int remove_Fila(Fila* fi){ //== remove lista inicio
    if(fi == NULL) //fila valida?
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    Elem *no = fi->inicio; //crio um auxiliar que aponta pro inicio
    fi->inicio = fi->inicio->prox; //o primeiro cara da lista eh o cara que estava em segundo
    if(fi->inicio == NULL)//fila ficou vazia
        fi->final = NULL; //esse eh o caso em que antes, final e inicio apontavam para o mesmo cara, o primeiro
    free(no);//libera o auxiliar
    fi->qtd--;//removido
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL) //fila valida?
        return 0;
    return fi->qtd;//ponto pro descritor
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)//valida?
        return 1;
    if(fi->inicio == NULL)//vazia?
        return 1;
    return 0;//tem algum
}

int Fila_cheia(Fila* fi){
    return 0;//nunca vai encher
}

void imprime_Fila(Fila* fi){
    if(fi == NULL) //fila valida?
        return;
    Elem* no = fi->inicio;//ponteiro q aponta pro inicio
    while(no != NULL){ //ate eu chegar ao fim, nota que se tiver vazia nao imprime, pq nao entra na 1 vez
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox; //proximo
    }
}

