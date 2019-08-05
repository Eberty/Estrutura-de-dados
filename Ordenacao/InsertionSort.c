#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};  //struct aluno

void printfVet(int*, int);
void insertionSort(int*, int);
void insertionSortMatricula(struct aluno*, int);
void insertionSortNome(struct aluno*, int);

int main(){
    int i;
    int N;

    printf("---------------------------------------------------\n");
    printf("\nStruct Aluno, insertionsort\n");
    struct aluno al[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    //insertionSortMatricula(al,4);
    insertionSortNome(al,4);
    for(i = 0; i < 4; i++)
        printf("%d) %s\n", al[i].matricula, al[i].nome);

    printf("\n\n\n---------------------------------------------------\n");
    int a3[8] = {0,23,4,67,-8,90,54,21};
    N = 8;
    printf("\nSem ordenar:\n");
    printfVet(a3,N);
    insertionSort(a3,N);
    printf("\n\nOrdenado:\n");
    printfVet(a3,N);

    system("pause");
    return 0;
}


void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

void insertionSort(int *V, int N){ //ordenaçso por inserçao
    int i, j, aux;
    for(i = 1; i < N; i++){ //move os maiores para a frente, i=1 pq j vai ate 0
        aux = V[i]; //auxiliar
        for(j = i; (j > 0) && (aux < V[j - 1]); j--)
            //pegando determinada posicao e comparando com j diminuindo em relacao a zero lembrando q faz enquanto aux for menor q o valr antes dele
            V[j] = V[j - 1]; //desloca todo mundo maior q aux uma posicao a frente
        V[j] = aux; //insere no lugar vago
    }
}

void insertionSortMatricula(struct aluno *V, int N){ //ordenaçao por inserçao usando struct aluno (ordenacao em vetor de struct)
    int i, j; //contadores
    struct aluno aux; //aux q recebe dados
    for(i = 1; i < N; i++){ //move os maiores para a frente, i=1 pq j vai ate 0
        aux = V[i]; //struct auxiliar
        for(j=i;(j>0) && (aux.matricula<V[j-1].matricula);j--) //quem conta aqui eh a matricula da struct aluno
        //pegando determinada posicao e comparando com j diminuindo em relacao a zero lembrando q faz enquanto aux for menor q o valr antes dele
            V[j] = V[j - 1];//desloca todo mundo (structs) maior q aux uma posicao a frente
        V[j] = aux; //insere struct aux no lugar vago
    }
}

void insertionSortNome(struct aluno *V, int N){ //(ordenacao em vetor de struct)
    int i, j; //contadores
    struct aluno aux; //aux q recebe dados
    for(i = 1; i < N; i++){ //move os maiores para a frente, i=1 pq j vai ate 0
        aux = V[i]; //struct auxiliar
        for(j=i;  (j>0) && (strcmp(aux.nome, V[j-1].nome)<0);  j--)
            // condicao de parada eh j>0 e comparacao por strcop validas ao mesmo tempo
                /*saída strcmp(str1,str2)
                    == 0: str1 é igual a str2
                     > 0: str1 vem depois de str2
                     < 0: str1 vem antes de str2
                */
            V[j] = V[j-1];//desloca todo mundo (structs) maior q aux uma posicao a frente
        //fim for j
        V[j] = aux; //insere struct aux no lugar vago
    } //fim do for i
}
