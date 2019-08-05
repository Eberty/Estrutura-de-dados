#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct paciente{
    char nome[30];
    int prio;
}Paciente; //definindo o tipo paciente com nome e prioridade

typedef struct fila_prioridade{
    int qtd; //quantidade
    Paciente dados[MAX]; //vetor estatico
}FilaPrio;

//funcoes
FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int consulta_FilaPrio(FilaPrio* fp, char* nome);
int insere_FilaPrio(FilaPrio* fp, char *nome, int  prioridade);
int remove_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);
void imprime_FilaPrio(FilaPrio* fp);

int main(){
    Paciente itens[6] = {{"Andre",1}, {"Bianca",2}, {"Carlos",5}, {"Nilza",8}, {"Inacio",6}, {"Edu",4}};
    int i;
    FilaPrio* fp = cria_FilaPrio();

    printf("Quem eh quem anted de eu inserir:\n");
    for (i=0; i< 6; i++){
        printf("%d) %d %s\n",i,itens[i].prio, itens[i].nome);
        insere_FilaPrio(fp, itens[i].nome,itens[i].prio);
    }

    printf("=================================\n");
    imprime_FilaPrio(fp); //depois de inserir como ficou

    //teste
    printf("=================================\n");
    insere_FilaPrio(fp, "Teste",9); //adicionando o teste
    imprime_FilaPrio(fp);

    printf("=================================\n");
    remove_FilaPrio(fp); //removendo o teste
    imprime_FilaPrio(fp);

    printf("=================================\n");
    for (i=0; i< 6; i++){
        char nome[30];
        consulta_FilaPrio(fp, nome); //consulta
        printf("%d) %s\n",i,nome); //imprime o cara q consultei
        remove_FilaPrio(fp); //remove o 1
    }

    libera_FilaPrio(fp); //libero tudo

    system("pause");
    return 0;
}

FilaPrio* cria_FilaPrio(){
    FilaPrio *fp;//ponteiro para alocar
    fp = (FilaPrio*) malloc(sizeof(FilaPrio));//alocacao dinamica
    if(fp != NULL)//se valida possui 0 elementos
        fp->qtd = 0;
    return fp;//retorna ponteiro para o 1 elemento
}

void libera_FilaPrio(FilaPrio* fp){
    free(fp); //como eh estatica, eu so uso um free
}

int consulta_FilaPrio(FilaPrio* fp, char* nome){
    if(fp == NULL || fp->qtd == 0) //fila valida? tem alguem na fila?
        return 0;
    strcpy(nome,fp->dados[0].nome); //como eh fila so copia o 1
    return 1;
}

void promoverElemento(FilaPrio* fp, int filho){
    int pai; //criando um inteiro pro pai
    struct paciente temp;
    pai = (filho - 1) / 2; //pai do filhe eh essa formula (calcula a posisao do pai do filho)
    while((filho > 0) && (fp->dados[pai].prio <= fp->dados[filho].prio)){//enquanto filho maior q 0 e a prioridade do pai for menor q a do filho
        //troca de lugares
        temp = fp->dados[filho]; //temp vai receber os detalhes de filho
        fp->dados[filho] = fp->dados[pai]; //pai vai virar filho
        fp->dados[pai] = temp; //filho vira pai

        filho = pai; //filho agora eh pai
        pai = (pai - 1) / 2; //o pai do novo pai (posicao)
    }
}

int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade){
    if(fp == NULL) //fila valida?
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;
    strcpy(fp->dados[fp->qtd].nome,nome);// insere na primeira posição livre
    fp->dados[fp->qtd].prio = prioridade; //defino a prioridade de quem eu coloquei
    promoverElemento(fp,fp->qtd);// desloca elemento para posição correta (funcao)
    fp->qtd++;// incrementa número de elementos no heap
    return 1;
}

void rebaixarElemento(FilaPrio* fp, int pai){
    Paciente temp;
    int filho = 2 * pai + 1; //a formula para posicao de um filho

    while(filho < fp->qtd){
        //pai tem 2 filhos? quem eh o maior?
        if(filho < fp->qtd-1) // verifica se tem 2 filhos
            if(fp->dados[filho].prio < fp->dados[filho+1].prio) //se a prioridade do primeiro for menor q a do segundo filho
                filho++; //filho aponta para filho maior prioridade

        if(fp->dados[pai].prio >= fp->dados[filho].prio) //ja corrigi?
            break; // encontrou lugar

        //troca pai e filho de lugar
        temp = fp->dados[pai]; //temp vai receber os dados do pai
        fp->dados[pai] = fp->dados[filho]; //filho vai virar pai
        fp->dados[filho] = temp;//pai vira filho

        pai = filho; //pai agora eh filho
        filho = 2 * pai + 1; //filho do novo pai
    } //fim do while
}

int remove_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //fila valida?
        return 0;
    if(fp->qtd == 0) //ta vazia?
        return 0;

    fp->qtd--; //removi um elemento (antes apontava para a primeira casa vazia
    fp->dados[0] = fp->dados[fp->qtd]; //o primeiro recebe o ultimo
    rebaixarElemento(fp,0); //corrige pq violei a s propriedades da heap
    return 1; //ok
}

int tamanho_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao existir
        return -1; //erro
    else
        return fp->qtd; //quantidade eh o tamanho
}

int estaCheia_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao existir
        return -1; //erro
    return (fp->qtd == MAX); //se qtd for igual ao tamanho do vetor q defini
}

int estaVazia_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //caso nao exitir
        return -1; //erro
    return (fp->qtd == 0); //so ta vazia se qtd for = a 0
}

void imprime_FilaPrio(FilaPrio* fp){
    if(fp == NULL) //fila existe?
        return;
    int i; //contador
    for(i=0; i < fp->qtd ; i++){ //comeca do primeiro e vai ate o ultimo
        printf("%d) Prio: %d \tNome: %s\n",i,fp->dados[i].prio,fp->dados[i].nome);
    }
}
