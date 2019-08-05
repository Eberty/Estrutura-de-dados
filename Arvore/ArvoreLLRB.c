#include <stdio.h>
#include <stdlib.h>
#define RED 1 //define as cores
#define BLACK 0

struct NO{ //definicao do tipo de arvore
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};
typedef struct NO* ArvLLRB; //cabeça para fazer **(RAIZ) mais facil entendimento

/**ABB RUBRO NEGRA 2-3**/
ArvLLRB* cria_ArvLLRB();
void libera_NO(struct NO* no);
void libera_ArvLLRB(ArvLLRB* raiz);
int consulta_ArvLLRB(ArvLLRB *raiz, int valor);
struct NO* rotacionaEsquerda(struct NO* A);
struct NO* rotacionaDireita(struct NO* A);
struct NO* balancear(struct NO* H);
struct NO* move2EsqRED(struct NO* H);
struct NO* move2DirRED(struct NO* H);
int cor(struct NO* H);
void trocaCor(struct NO* H);
struct NO* insereNO(struct NO* H, int valor, int *resp);
int insere_ArvLLRB(ArvLLRB* raiz, int valor);
struct NO* removerMenor(struct NO* H);
struct NO* procuraMenor(struct NO* atual);
struct NO* remove_NO(struct NO* H, int valor);
int remove_ArvLLRB(ArvLLRB *raiz, int valor);
int estaVazia_ArvLLRB(ArvLLRB *raiz);
int totalNO_ArvLLRB(ArvLLRB *raiz);
int altura_ArvLLRB(ArvLLRB *raiz);
void preOrdem_ArvLLRB(ArvLLRB *raiz, int H);
void emOrdem_ArvLLRB(ArvLLRB *raiz, int H);
void posOrdem_ArvLLRB(ArvLLRB *raiz, int H);

/**TESTE**/
int main(){
    ArvLLRB * raiz = cria_ArvLLRB();
    //system ("color C");

    /**EXEMPLOS**/
    //int i, N = 10, val[10] = {10,20,30,40,50,15,18,25,38,28};
    //int i, N = 10, val[10] = {10,20,30,40,50,15,18,25,33,28};
    //int i, N = 8, val[8] = {10,85,15,70,20,60,30,50};
    //int i, N = 8, val[8] = {8,10,15,18,14,20,16,22};
    //int i, N = 4, val[4] = {5,30,20,10};
    //int i, N = 7, val[7] = {10,15,20,30,70,85,50};
    //int i, N = 7, val[7] = {85,10,30,70,15,20,50};
    //int i, N = 10, val[10] ={10,15,10,20,30,70,70,85,50,50};
    int i, N = 7, val[7] ={20,15,30,85,50,21,70};


    for(i = 0; i < N; i++){ //insere e apresneta
        if(insere_ArvLLRB(raiz, val[i]))
            printf("Insercao: %d -> OK\n", val[i]);
        else
            printf("Insercao: %d -> ERRO\n", val[i]);

        emOrdem_ArvLLRB(raiz,0);
        printf("\n==========================\n\n");
    }


    printf("Tamanho: %d\n", totalNO_ArvLLRB(raiz));
    printf("Pos Ordem: \n");
    posOrdem_ArvLLRB(raiz, 0);
    printf("\n\n==========================\n");


    printf("\nTeste de remocao 1 - valor 30:\n");
    if(remove_ArvLLRB(raiz, 10))
        printf("Remocao: Sucesso!\n");
    else
        printf("Remocao: Erro!\n");
    emOrdem_ArvLLRB(raiz, 0);

    printf("\nTeste de remocao 2 e 3 - valores 30 e 15:\n");
    remove_ArvLLRB(raiz, 30);
    remove_ArvLLRB(raiz, 15);
    emOrdem_ArvLLRB(raiz, 0);

    printf("\nTeste de remocao 4 - valor 50:\n");
    remove_ArvLLRB(raiz, 50);
    emOrdem_ArvLLRB(raiz, 0);

    libera_ArvLLRB(raiz);
    return 0;
}


/**CRIAÇÃO DA ARVORE**/
ArvLLRB* cria_ArvLLRB(){
    ArvLLRB* raiz = (ArvLLRB*) malloc(sizeof(ArvLLRB)); //criando e alocando a arvore
    if(raiz != NULL){ //consegui alocar
        *raiz = NULL; //acabei de criar, portanto ela ta vazia
    }
    return raiz;
}


/**LIBERAR**/
void libera_NO(struct NO* no){ //libera o no especifico recursivo com os filhos
    if(no == NULL) //retorno do final do recursivo
        return;
    libera_NO(no->esq); //libera antes todos da esquerda
    libera_NO(no->dir); //libera antes todos da direita
    free(no); //libero agora que ele nao tem mais filhos
    no = NULL; //agora ele eh folha
}

void libera_ArvLLRB(ArvLLRB* raiz){
    if(raiz == NULL) //arvore valida?
        return;
    libera_NO(*raiz);//libera cada nó, ate chegar na raiz, NOTA que *raiz eh um no*, uma vez que eh o q ta sendo apontado
    free(raiz); //libera a raiz
}


/**CONSULTA ÁRVORE**/
int consulta_ArvLLRB(ArvLLRB *raiz, int valor){
    if(raiz == NULL) //arvora valida?
        return 0;
    struct NO* atual = *raiz; //o atual eh o auxiliar que ira percorrer
    while(atual != NULL){ //enquanto nao cheguei em uma folha vazia
        if(valor == atual->info){ //encontrei
            return 1; //verdade
        }
        if(valor > atual->info)  //pra onde eu devo ir? a depender do valor, lembrano q esq eh menor e direita eh maior
            atual = atual->dir;
        else
            atual = atual->esq;
    } //fim do while
    return 0; //nao achei ngm
}


/**ROTAÇÃO Complexidade O(1) E BALANCEAMENTO(MOVIMENTAÇÃO)**/
struct NO* rotacionaEsquerda(struct NO* A){
    struct NO* B = A->dir; //recebe um no A com B sendo filho direito
    A->dir = B->esq; //move B para o lugar de A, a direita de a recebe esquerda de b para poder inverter
    B->esq = A; //A se torna filho esquerdo de B
    B->cor = A->cor; //B recebe cor de A
    A->cor = RED; // A fica vermelho
    return B; //novo pai
}

struct NO* rotacionaDireita(struct NO* A){
    struct NO* B = A->esq;//recebe um no A com B sendo filho esquerdo
    A->esq = B->dir; //move B para o lugar de A, a direita de a recebe direitoa de b para poder inverter
    B->dir = A; //A se torna filho direito de B
    B->cor = A->cor; //B recebe cor de A
    A->cor = RED; // A fica vermelho
    return B; //novo pai
}

struct NO* balancear(struct NO* H){
    //se o filho direito eh vermelho: rotação a esquerda
    if(cor(H->dir) == RED) //nó Vermelho é sempre filho à esquerda
        H = rotacionaEsquerda(H);

    //se o filho direito e o neto da esquerda sao vermelhos: rotacao a direita
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED) //Filho da direita e neto da esquerda são vermelhos
        H = rotacionaDireita(H);

    //se ambos os filhos sao vermelhos: trocar a cor do pai e dos filhos
    if(cor(H->esq) == RED && cor(H->dir) == RED) //2 filhos Vermelhos: troca cor!
        trocaCor(H);

    //se mudar um, os outros concertam
    return H; //retorna o novo pai
}

struct NO* move2EsqRED(struct NO* H){
    trocaCor(H); //recebe um no h e troca as cores dele e de seus filhos
    if(cor(H->dir->esq) == RED){ //se o filho a esquerda do filho direito eh vermelho
        H->dir = rotacionaDireita(H->dir); //aplicar rotacao a direita no filho direito
        H = rotacionaEsquerda(H); //e uma rotacao esquerda no pai
        trocaCor(H); //troca as cores do no pai e de seus filhos
    }
    return H; //retorno quem ficou sendo o no h apos a operacao
}

struct NO* move2DirRED(struct NO* H){
    trocaCor(H);  //recebe um no h e troca as cores dele e de seus filhos
    if(cor(H->esq->esq) == RED){ //se o filho a esquerda do filho esquerdo eh vermelho
        H = rotacionaDireita(H); //aplicar rotacao a direita no pai
        trocaCor(H); //troca as cores do no pai e de seus filhos
    }
    return H; //retorno quem ficou sendo o no h apos a operacao
}


/**PROPRIEDADES**/
int cor(struct NO* H){
    //funcao auxiliar
    if(H == NULL) //raiz sempre eh preto
        return BLACK;
    else
        return H->cor;
}

void trocaCor(struct NO* H){
    //operacao administrativa: nao altera a estrutura ou conteudo da arvore
    H->cor = !H->cor; //inverte a cor (como red e black é igual a 0 e 1 eu posso inverter)
    //inverter filhos
    if(H->esq != NULL) //se existe alguem na direita eu inverto, assim como na esquerda
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}


/**INSERCAO**/
struct NO* insereNO(struct NO* H, int valor, int *resp){
    if(H == NULL){ //ou a arvore ta vazia ou eu dasci na recursao ate um ponto de no folha
        struct NO *novo; //crio novo no
        novo = (struct NO*)malloc(sizeof(struct NO)); //fazer alocacao para o novo no
        if(novo == NULL){ //verifico se deu certo ou errado
            *resp = 0; //falha
            return NULL; //falso
        }

        novo->info = valor; //valor e info
        novo->cor = RED; //o no q insiro sempre sera vermelho
        novo->dir = NULL; //coo e folha, a direita e a esquerda sao NULL
        novo->esq = NULL;
        *resp = 1; //deu certa a insercao, falta balanceamento
        return novo; //retorna pra subarvore q o chamou recursivamente ou para o gerenciamento
    }

    if(valor == H->info) //se o no ja existe, nao precisa inserir
        *resp = 0;// Valor duplicado
    else{ //valor nao existe
        if(valor < H->info) //recursao
            H->esq = insereNO(H->esq, valor, resp); //se for menor q o lugar onde eu to, vou para a esquerda
        else
            H->dir = insereNO(H->dir, valor, resp);//se for maior q o lugar onde eu to, vou para a direita
    }

    /**Tratar balanceamento**/
    //nó Vermelho é sempre filho à esquerda
    if(cor(H->dir) == RED && cor(H->esq) == BLACK)
        H = rotacionaEsquerda(H);

    //Filho e Neto são vermelhos: Filho vira pai de 2 nós vermelhos
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);

    //2 filhos Vermelhos: troca cor!
    if(cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H; //uma das chamadas recursivas ou a raiz...
}

int insere_ArvLLRB(ArvLLRB* raiz, int valor){
    int resp; //resposta de retorno
    //funcao responsavel pela busca do local de inserção do NO, gerencia
    *raiz = insereNO(*raiz, valor, &resp);
    if((*raiz) != NULL) //se o conteudo for diferente de null
        (*raiz)->cor = BLACK; //corrijo a cor da raiz q por padrao sempre deve ser preta

    return resp;
}


/**REMOÇÃO**/
struct NO* removerMenor(struct NO* H){
    if(H->esq == NULL){ //se ele so tiver 1 filho a direita
        free(H); //so apagar ele e retornar null
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) //tratar problemas de balanceamento
        H = move2EsqRED(H); //ok, posso remove-lo

    H->esq = removerMenor(H->esq); //chamo funcao recursiva
    return balancear(H); //antes de voltar na recursao, tenho de balancear
}

struct NO* procuraMenor(struct NO* atual){ //igual a usada na AVL
    //vao se movendo cada vez mais a esquerda ate chegar no nul (o menor entre os maiores vai ser n1, q eh anterior a n2 q chegou ao null)
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){ //procurar pelo no mais a esquerda
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

struct NO* remove_NO(struct NO* H, int valor){
    //o proprio ato de remover reestrutura a arvore
    if(valor < H->info){ //valor menor trabalho com a subarvore da esqurda
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) //faco correcao anted de continuar
            H = move2EsqRED(H);

        H->esq = remove_NO(H->esq, valor); //recusivamente vou subindo os nos
    }else{ //se o valor for maior faz:
        if(cor(H->esq) == RED) //verifico se a esquerda eh vermelha
            H = rotacionaDireita(H); //se for, tenho q corrigir o possivel erro q vira antes da remocao

        if(valor == H->info && (H->dir == NULL)){ //valor igual eu posso remover
            free(H); //nao precisa perguntar a ngm pq so tem um filho, pois a direita ta vazio
            return NULL; //fim
        }

        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK) //outra posibilidade: 2 pretos
            H = move2DirRED(H); //corrigir erro da remocao

        if(valor == H->info){ //encontrei?
            struct NO* x = procuraMenor(H->dir); //vou descendo a subarvore a direita ate encontrar o menor valor entre os maiores
            H->info = x->info; //copio a info dele pro h
            H->dir = removerMenor(H->dir); //e vou remover o antigo menor
        }else //se nao for igual
            H->dir = remove_NO(H->dir, valor);//chamo a funcao recursiva a partir da subarvore a direita
    } //terminei td o processo
    return balancear(H); //tenho q balancear antes de voltar na recursao
}

int remove_ArvLLRB(ArvLLRB *raiz, int valor){
    //funcao de gerenciamento
    if(consulta_ArvLLRB(raiz, valor)){ //o no existe pra ser removido?
        struct NO* h = *raiz;
        *raiz = remove_NO(h, valor); //funcao responsavel pela busca do no a ser removido
        if(*raiz != NULL) //existe uma raiz, arvore nao vazia
            (*raiz)->cor = BLACK; //a cor da raiz sempre deve ser preto
        return 1; //consegui
    }else
        return 0;//nao consegui
}


/**PROPRIEDADES ÁRVORE**/
int estaVazia_ArvLLRB(ArvLLRB *raiz){
    if(raiz == NULL) //se for invalida ta vazia
        return 1;
    if(*raiz == NULL) //se nao apontar pra ngm ta vazia
        return 1;
    return 0; //rodou os 2, entao tem alguem
}

int totalNO_ArvLLRB(ArvLLRB *raiz){
    if (raiz == NULL) //arvore valida?
        return 0;
    if (*raiz == NULL) //chegeui em uma folha que nao tem ngm
        return 0;

    int alt_esq = totalNO_ArvLLRB(&((*raiz)->esq)); //calculo os da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = totalNO_ArvLLRB(&((*raiz)->dir)); //calculo os da direita desse cara (pasando o endereco do filho)
    return(alt_esq + alt_dir + 1); //somo a direita, a esquera e ele
}

int altura_ArvLLRB(ArvLLRB *raiz){
    if (raiz == NULL) //arvora valida?
        return 0;
    if (*raiz == NULL)  //chegeui em uma folha que nao tem ngm
        return 0;
    int alt_esq = altura_ArvLLRB(&((*raiz)->esq)); //calculo a da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = altura_ArvLLRB(&((*raiz)->dir)); //calculo a da direita desse cara (pasando o endereco do filho)
    if (alt_esq > alt_dir)  //como eh a altura, eu so vou somar com qual dos dois eh o maior, o 1 eh o pai daqui
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


/**PERCURSOS**/
void  posOrdem_ArvLLRB(ArvLLRB *raiz, int H){
    if(raiz == NULL) //arvore invalida ou folha
        return;

    if(*raiz != NULL){ //caso eu nao esteja no fim
        posOrdem_ArvLLRB(&((*raiz)->esq), H+1); //o enderecodo filho a esquerda
        posOrdem_ArvLLRB(&((*raiz)->dir), H+1); //o endereco do filho a direita

        if((*raiz)->cor == RED) //apresenta de acordo com a cor
            printf("%d  Vermelho: H(%d) \n",(*raiz)->info, H);
        else
            printf("%d  Preto: H(%d) \n",(*raiz)->info, H);

    }
}

void emOrdem_ArvLLRB(ArvLLRB *raiz, int H){
    if(raiz == NULL) //arvore invalida ou folha
        return;

    if(*raiz != NULL){
        emOrdem_ArvLLRB(&((*raiz)->esq), H+1); //o enderecodo filho a esquerda

        if((*raiz)->cor == RED) //apresenta de acordo com a cor
            printf("%dR: H(%d) \n",(*raiz)->info, H);
        else
            printf("%dB: H(%d) \n",(*raiz)->info, H);

        emOrdem_ArvLLRB(&((*raiz)->dir), H+1); //o endereco do filho a direita
    }
}

void preOrdem_ArvLLRB(ArvLLRB *raiz, int H){
    if(raiz == NULL) //arvore invalida ou folha
        return;

    if(*raiz != NULL){ //caso eu nao esteja no fim
        if((*raiz)->cor == RED) //apresenta de acordo com a cor
            printf("%d  Vermelho: H(%d) \n",(*raiz)->info, H);
        else
            printf("%d  Preto: H(%d) \n",(*raiz)->info, H);

        preOrdem_ArvLLRB(&((*raiz)->esq), H+1); //o enderecodo filho a esquerda
        preOrdem_ArvLLRB(&((*raiz)->dir), H+1); //o endereco do filho a direita
    }
}
