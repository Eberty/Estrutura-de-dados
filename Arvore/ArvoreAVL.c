#include <stdio.h>
#include <stdlib.h>

struct NO{
    int info;
    int altura; //altura daquela sub arvore, pra nao precisar percorrer toda hr pra calcular
    struct NO *esq;
    struct NO *dir;
}; //ab + altura

typedef struct NO* ArvAVL;//cabeça para fazer ** mais facil entendimento

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);

int main(){
    ArvAVL* avl = cria_ArvAVL();
    int res,i;
    int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6};

    for(i=0;i<N;i++){
        printf("========================\n");
        printf("Inserindo: %d\n", dados[i]);
        res = insere_ArvAVL(avl,dados[i]);
        printf("\nRes = %d\n",res);
        preOrdem_ArvAVL(avl);
        printf("\n\n");
    }

    printf("\n\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    printf("========================\n");

    remove_ArvAVL(avl,6);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,7);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,4);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    libera_ArvAVL(avl);

    return 0;
}

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL)); //criando e alocando a lista
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

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL) //arvore valida?
        return;
    libera_NO(*raiz);//libera cada nó, ate chegar na raiz, NOTA que *raiz eh um no*, uma vez que eh o q ta sendo apontado
    free(raiz); //libera a raiz
}

int altura_NO(struct NO* no){ //auxiliar
    if(no == NULL) //se ele nao existe
        return -1; //considera altura -1
    else
        return no->altura; //autura do no
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir)); //labs nao importa se e positivo ou negativo +esquerdo, -direito
}

int maior(int x, int y){ //faz comparacao de x e y
    if(x > y)
        return x; //x maior
    else
        return y; //y maior
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) //se for invalida ta vazia
        return 1;
    if(*raiz == NULL) //se nao apontar pra ngm ta vazia
        return 1;
    return 0; //rodou os 2, entao tem alguem
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL) //arvore valida?
        return 0;
    if (*raiz == NULL) //chegeui em uma folha que nao tem ngm
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq)); //calculo os da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir)); //calculo os da direita desse cara (pasando o endereco do filho)
    return(alt_esq + alt_dir + 1); //somo a direita, a esquera e ele
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL) //arvora valida?
        return 0;
    if (*raiz == NULL) //chegeui em uma folha que nao tem ngm
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq)); //calculo a da esquerda desse cara (pasando o endereco do filho)
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));//calculo a da direita desse cara (pasando o endereco do filho)
    if (alt_esq > alt_dir) //como eh a altura, eu so vou somar com qual dos dois eh o maior, o 1 eh o pai daqui
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) //arvore invalida ou folha
        return;
    if(*raiz != NULL){ //caso eu nao esteja no fim
        printf("No %d: %d\n",(*raiz)->info, altura_NO(*raiz)); //as infos do pai(ele)
        preOrdem_ArvAVL(&((*raiz)->esq)); //o enderecodo filho a esquerda
        preOrdem_ArvAVL(&((*raiz)->dir)); //o endereco do filho a direita
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) //arvore invalida ou folha
        return;
    if(*raiz != NULL){ //caso eu nao esteja no fim
        emOrdem_ArvAVL(&((*raiz)->esq)); //o enderecodo filho a esquerda
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info, altura_NO(*raiz), fatorBalanceamento_NO(*raiz)); //as infos do pai(ele)
        emOrdem_ArvAVL(&((*raiz)->dir)); //o endereco do filho a direita
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)//arvore invalida ou folha
        return;
    if(*raiz != NULL){ //caso eu nao esteja no fim
        posOrdem_ArvAVL(&((*raiz)->esq)); //o enderecodo filho a esquerda
        posOrdem_ArvAVL(&((*raiz)->dir)); //o endereco do filho a direita
        printf("%d\n",(*raiz)->info); //as infos do pai(ele)
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL) //arvora valida?
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

/*
quando usar cada rotacao -> FATOR BALANCEAMENTO
    A=+2 e B=+1 LL //sinais iguais
    A=-2 e B=-1 RR
    A=+2 e B=-1 LR //sinais diferentes
    A=-2 e B=+1 RL
*/

//rotacaoes aplicadas no ancestral mais prox do no inserido cujo fator ficou 2

void RotacaoLL(ArvAVL *A){//LL rotacao simples a esquerda
    printf("RotacaoLL\n");
    struct NO *B; //crio no auxiliar
    B = (*A)->esq; //auxiliar recebe filho da esquerda
    (*A)->esq = B->dir; //o filho da esquerda da raiz recebe o filho a direita da esquerda
    B->dir = *A; //o filho a direita recebe a raiz

    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1; //calcula nova altura da raiz
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1; //nova autura do auxiliar
    *A = B; //raiz recebe quem ta no no
}

void RotacaoRR(ArvAVL *A){//RR: rotacao simples a esquerda
    printf("RotacaoRR\n");
    struct NO *B;  //crio no auxiliar
    B = (*A)->dir; //auxiliar recebe filho da direita
    (*A)->dir = B->esq;//o filho da direita da raiz recebe o filho a esquerda  da direita
    B->esq = (*A);

    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1; //calcula nova altura da raiz
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1; //nova autura do auxiliar
    (*A) = B; //raiz recebe quem ta no no (no no lugar da raiz)
}

void RotacaoLR(ArvAVL *A){//LR rotacao dupla a direita
    //composta por 2 rotacaoes simples
    RotacaoRR(&(*A)->esq); //rr no filho da esquerda
    RotacaoLL(A);//ll na raiz
}

void RotacaoRL(ArvAVL *A){//RL rotacao dupla a esquerda
    //composta por 2 rotacaoes simples
    RotacaoLL(&(*A)->dir); //ll no filho da direita
    RotacaoRR(A);//rr na raiz
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res; //resposta ao longo das chamadas
    if(*raiz == NULL){//árvore vazia ou nó  folha
        struct NO *novo; //cria no auxiliar
        novo = (struct NO*)malloc(sizeof(struct NO)); //aloca auxiliar
        if(novo == NULL) //deu certa a alocacao?
            return 0;

        novo->info = valor; //copia valor inserido
        novo->altura = 0; //folha ou raiz
        novo->esq = NULL; //folha, filhos null
        novo->dir = NULL;
        *raiz = novo; //adicionei primeiro elemento
        return 1; //deu certo a operacao
    }

    struct NO *atual = *raiz; //atual eh o primeiro no

    if(valor < atual->info){ //se o valor for menor, a insercao eh na arvore da esquerda
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){ //funcao recursiva, o res==1 a insercao deu serto e eu faco o q ta dentro do if
            if(fatorBalanceamento_NO(atual) >= 2){ //balanceamento se nescessario: se >=2 faz
                if(valor < (*raiz)->esq->info ){ //se esse valor eh menor q filho da esquerda do atual
                    RotacaoLL(raiz);
                }else{ //se for maior / \,
                    RotacaoLR(raiz);
                }
            }
        }
    }else{ //se o valor for maior, a insercao eh na arvore da direitaa
        if(valor > atual->info){//msm ideia
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){//funcao recursiva, o res==1 a insercao deu serto e eu faco o q ta dentro do if
                if(fatorBalanceamento_NO(atual) >= 2){ //balanceamento se nescessario: se >=2 faz
                    if((*raiz)->dir->info < valor){ //a direita do atual eh menor q o valor q inseri, rotacao rr
                        RotacaoRR(raiz);
                    }else{ //se nao inseri direita esquerda
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{ //se o valor for igual
            printf("Valor duplicado!!\n"); //considero q nao vou inserir na arvore
            return 0;
        }
    }
    //terminei a insercao, calcular a autura
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;//a maior autura entre os filhos + o pai

    return res; //res diz se consegui ou nao
}

struct NO* procuraMenor(struct NO* atual){ //tratar a remocao do no com 2 filhos
    struct NO *no1 = atual; //no 1 atual
    struct NO *no2 = atual->esq;//no2 esquerda do atual
    while(no2 != NULL){ //enquanto no2 nao chegar no final
        no1 = no2;  //vou andando ate no2 encontrar ull
        no2 = no2->esq;
    }
    return no1; //no 1 eh o ultimo no - o mais a esquerda da subarvore a direita
}

int remove_ArvAVL(ArvAVL *raiz, int valor){ //trata no folha, com 1 filho ou 2, responsavel pela busca do no a ser removido
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0; //falhou a remocao
	}

    int res; //resposta da remocao q eh uma funcao recursiva
	if(valor < (*raiz)->info){ //valor q estou procurando eh menor q o da raiz
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){ //tento remover o da esquerda dele, recursiva, se fizer continua
            if(fatorBalanceamento_NO(*raiz) >= 2){ //se consegui, calcula o valor balanceamento, se precisar faz
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir)) //como eu to na esquerda, tenho q verificar a da direita
                    RotacaoRR(raiz);
                else //as rotacoes dependen da autura das partes
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){ // se o valor da raiz for menor, eh o msmo proceso, mas olhando a subarvore da direita
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){//tento remover o da direita dele, recursiva, se fizer continua
            if(fatorBalanceamento_NO(*raiz) >= 2){ //se consegui, calcula o valor balanceamento, se precisar faz
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )//como eu to na direita, tenho q verificar os da esquerda
                    RotacaoLL(raiz);
                else //as rotacoes dependen da autura das partes
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){ //valor q quero remover eh igual a raiz, eh aq q eu trato a remocao
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL) //qual deles eh null
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);//substituir pelo no mais a esquerda da subarvore a direita
			(*raiz)->info = temp->info; //copio as informacoes dele pro no raiz
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info); //chamo a funcao remove recusivamente para tratar problemas do lado direito
            if(fatorBalanceamento_NO(*raiz) >= 2){ //calculo balanceamento
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))//como eu to na direita, tenho q verificar os da esquerda
					RotacaoLL(raiz);
				else //as rotacoes dependen da autura das partes
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL) //para calcular nova altura
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1; //nova altura
		return 1; //corrigi
	}
    //calcula nova altura depois de realizadas todas as recusividades
	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res; //ou acrtei ou nao
}
