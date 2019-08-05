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
void shellSort(int*, int);
void shellSort2(int*, int, int*, int);

int main(){
    int i, N, V[8] = {65,75,6,57,99,27,0,96};
    N = 8;

    printf("\nSem ordenar:\n");
    printfVet(V,N);

    printf("\nExecucao:\n");
    shellSort(V,N);

    printf("\n\nOrdenado:\n");
    printfVet(V,N);

    printf("\n\n\n---------------------------------------------------\n");
    int a1[10] = {5,3,7,5,9,4,8,2,7,6};
    N = 10;
    int tamP = 3, P[3] = {1,3,5};

    printf("\nSem ordenar:\n");
    printfVet(a1,N);

    printf("\nExecucao:\n");
    shellSort2(a1,N,P,tamP);

    printf("\n\nOrdenado:\n");
    printfVet(a1,N);

    system("pause");
    return 0;
}

void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

void shellSort(int *V, int N) {
    int i, j, valor; //Cria variáveis auxiliares
    int h = 1; //Cria a variável h que será usada para selecionar os grupos de valores do vetor

    while(h < N)
        h = 3 * h + 1;

    while (h > 1) {//E a validação de h > 1 é feita para que quando a última ordenação h1 for feita, o programa termine.
        //Aqui dividimos o incremento de shell para montar os grupos de valores que serão ordenados. Depois de todos os valores de h
        //serem ordenados, dividimos h novamente e ordenamos pares mais próximos, até que h = 1 e os pares adjacentes sejam ordenados.
        h /= 3;

        for(i = h; i < N; i++) {//É aqui que a comparação e a ordenação acontecem:
            valor = V[i]; //Valor vai receber o h-ésimo elemento do vetor
            j = i - h; //j vai ser o índice do elemento que será comparado com valor
            while (j >= 0 && valor < V[j]) { //Aqui é feita a troca de lugares entre os elementos
                V[j + h] = V[j];
                j -= h;
            }
            V[j + h] = valor;
        }
        printf("\nh = %d\n", h);
        printfVet(V,N);
    }
}

void shellSort2(int *V, int N, int *P, int tamP) {
    int i, j, valor; //Cria variáveis auxiliares
    int h; //contador de tamanho de

    for(h = tamP-1; h >= 0; h--){ //conta como vai ser a contagem de pacos a partir do vetor de passos
        for(i = P[h]; i < N; i++) {//É aqui que a comparação e a ordenação acontecem:
            valor = V[i]; //Valor vai receber o h-ésimo elemento do vetor
            j = i - P[h]; //j vai ser o índice do elemento que será comparado com valor
            while (j >= 0 && valor < V[j]) { //Aqui é feita a troca de lugares entre os elementos
                V[j + P[h]] = V[j];
                j -= P[h];
            }
            V[j + P[h]] = valor;
        }
        printf("\nP[%d] = %d\n", h, P[h]);
        printfVet(V,N);
    }
}
