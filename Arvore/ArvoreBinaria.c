#include <stdio.h>
#include <stdlib.h>

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
}; //definicao do tipo arvore binaria

typedef struct NO* ArvBin; //cabeça para fazer ** mais facil entendimento

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};
    int i;
    ArvBin* raiz = cria_ArvBin();

    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    printf("Pre ordem:\n");
    preOrdem_ArvBin(raiz);

    printf("\n\nEm ordem:\n");
    emOrdem_ArvBin(raiz);

    printf("\n\nPos ordem:\n");
    posOrdem_ArvBin(raiz);

    if(remove_ArvBin(raiz,50)){
        printf("\n\nRemovido o 50\n");
        preOrdem_ArvBin(raiz);
    }else
        printf("\n\nNAO removido\n");

    if(remove_ArvBin(raiz,75)){
        printf("\n\nRemovido\n");
    }else
        printf("\nNAO removido\n\n");


    printf("Altura: %d\n",altura_ArvBin(raiz));
    printf("Total NOs: %d\n",totalNO_ArvBin(raiz));

    if (consulta_ArvBin(raiz, 100))
        printf("Valor encontrado");

    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin)); //criando e alocando a lista
    if(raiz != NULL) //consegui alocar
        *raiz = NULL; //acabei de criar, portanto ela ta vazia
    return raiz;
}

void libera_NO(struct NO* no){ //libera o no especifico recursivo com os filhos
    if(no == NULL) //retorno do final do recursivo
        return;
    libera_NO(no->esq); //libera antes todos da esquerda
    libera_NO(no->dir); //libera antes todos da direita
    free(no); //libero agora que ele nao tem mais filhos
    no = NULL; //agora ele eh folha
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL) //arvore valida?
        return;
    libera_NO(*raiz);//libera cada nó, ate chegar na raiz, NOTA que *raiz eh um no*, uma vez que eh o q ta sendo apontado
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL) //arvore valida?
        return 0;
    struct NO* novo; //criando ponteiro para elemento a ser inserido
    novo = (struct NO*) malloc(sizeof(struct NO));// alocando elemento
    if(novo == NULL) //consegui alocar?
        return 0;
    novo->info = valor; //ele vai ser folha, a info denle eh o valor passado e aponta os 2 lados pro null
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL) //caso arvore estiver vazia, NOTA * eh o que esta sendo apontado
        *raiz = novo;
    else{ //caso ela tiver alguem
        struct NO* atual = *raiz; //atual que vai percorrer
        struct NO* ant = NULL; //anterior que ainda nao comeca com ngm que vai colocar o no no lugar
        while(atual != NULL){ //ate encontar o null de um no folha
            ant = atual; //anterior agora eh atual (o ultimo visto)
            if(valor == atual->info){//elemento já existe, nao vou por repetido aqui, qualquer coisa faz >= em baixo que resolve
                free(novo);
                return 0;
            }

            if(valor > atual->info) //verifica se vou pra esquerda ou direita pra percorrer
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        //fim do while, cheguei em um null = atual
        if(valor > ant->info) //verifica se vou pra direita ou esquerda pra colocar o elemento
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

struct NO* remove_atual(struct NO* atual) { //vai liberar so um no, sem contar os filhos q vao ser realocados
    struct NO *no1, *no2; //criando duas referencias a struct NO
    if(atual->esq == NULL){ //se nao tiver ngm a esquerda
        no2 = atual->dir; //a dirita dele q vai subir
        free(atual); //libera
        return no2; //retorna
    } //se nao
    no1 = atual; //no1 eh o no q passei
    no2 = atual->esq; //o dois segue a esquerda dele
    while(no2->dir != NULL){
        no1 = no2;// no1 é o pai de no2
        no2 = no2->dir;//no2 é o nó anterior a r na ordem e-r-d
    }

    if(no1 != atual){ //se o no1 for diferente do no q mandei
        no1->dir = no2->esq; //a direita do no pai e a esquerda do seu filho a direita
        no2->esq = atual->esq;//como a esquerda do filho sobiu, a esquerda do atual agora eh ele, pq o no2 ocupou o atual
    }
    no2->dir = atual->dir; //corrigindo a direita
    free(atual); //liberei
    return no2; //no2 agora ocupou o lugar
}

int remove_ArvBin(ArvBin *raiz, int valor){ //vou remover um valor especifico, corrigindo pra nao eliminar td mundo q for filho
    if(raiz == NULL) //arvore valida?
        return 0;
    struct NO* ant = NULL; //criando anterior e atual para percorrer
    struct NO* atual = *raiz;
    while(atual != NULL){ //se eu cheguei no null eu nao achei ninguem, to no while ate achar o valor (olhar retorno 1)
        if(valor == atual->info){ //caso eu achei quem eu quero remover
            if(atual == *raiz) //se o cara q eu quero remover for o pai de tod mundo
                *raiz = remove_atual(atual); //a raiz vai ser o no que subi
            else{
                if(ant->dir == atual)//o cara que eu quero remover eh filho de quem?em que lado ele esta?
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1; //consegui remover
        } //fim do if que ta procurando o valor exato
        ant = atual; //anterior agora eh o atual
        if(valor > atual->info) //pergunto se tenho de ir para a direita ou esquerda, lembrando q a direita eh o maior e a esquerda o menor
            atual = atual->dir;
        else
            atual = atual->esq;
    } //fim do while, td de novo
    return 0; //nao consegui remover
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL) //se for invalida ta vazia
        return 1;
    if(*raiz == NULL) //se nao apontar pra ngm ta vazia
        return 1;
    return 0; //rodou os 2, entao tem alguem
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)//arvore valida?
        return 0;
    if (*raiz == NULL)//chegeui em uma folha que nao tem ngm
        return 0;
    //recursivamente
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));//calculo os da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));//calculo os da direita desse cara (pasando o endereco do filho)
    return(alt_esq + alt_dir + 1); //somo a direita, a esquera e ele
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL) //arvora valida?
        return 0;
    if (*raiz == NULL)//chegeui em uma folha que nao tem ngm
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));//calculo os da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = altura_ArvBin(&((*raiz)->dir));//calculo os da direita desse cara (pasando o endereco do filho)
    if (alt_esq > alt_dir) //como eh a altura, eu so vou somar com qual dos dois eh o maior, o 1 eh o pai daqui
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)//arvora valida?
        return 0;
    struct NO* atual = *raiz; //o atual eh o auxiliar que ira percorrer
    while(atual != NULL){ //enquanto nao cheguei em uma folha vazia
        if(valor == atual->info){ //encontrei
            return 1; //verdade
        }
        if(valor > atual->info) //pra onde eu devo ir? a depender do valor, lembrano q esq eh menor e direita eh maior
            atual = atual->dir;
        else
            atual = atual->esq;
    } //fim do while
    return 0; //nao achei ngm
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)//arvore invalida
        return;
    if(*raiz != NULL){//caso eu nao esteja no fim
        printf("%d\n",(*raiz)->info); //a info do pai
        preOrdem_ArvBin(&((*raiz)->esq)); //o enderecodo filho a esquerda
        preOrdem_ArvBin(&((*raiz)->dir)); //o endereco do filho a direita
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)//arvore invalida
        return;
    if(*raiz != NULL){ //caso eu nao esteja no fim
        emOrdem_ArvBin(&((*raiz)->esq));//o enderecodo filho a esquerda
        printf("%d\n",(*raiz)->info);//a info do pai
        emOrdem_ArvBin(&((*raiz)->dir));//o endereco do filho a direita
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)//arvore invalida
        return;
    if(*raiz != NULL){//caso eu nao esteja no fim
        posOrdem_ArvBin(&((*raiz)->esq));//o enderecodo filho a esquerda
        posOrdem_ArvBin(&((*raiz)->dir));//o endereco do filho a direita
        printf("%d\n",(*raiz)->info);//a info do pai
    }
}
