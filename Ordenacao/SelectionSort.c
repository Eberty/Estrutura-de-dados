#include <stdio.h>
#include <stdlib.h>

void printfVet(int*, int);
void selectionSort(int*, int);

int main(){
    int i;
    int N;

    printf("\n---------------------------------------------------\n");
    int a4[5] = {23,4,67,-8,21};
    N = 5;
    printf("Sem ordenar:\n");
    printfVet(a4,N);

    printf("Ordenado:\n");
    selectionSort(a4,N);
    printfVet(a4,N);

    system("pause");
    return 0;
}


void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

void selectionSort(int *V, int N){ //ordenacao por selecao
    //a cada passo procuro o menor valor do array e coloco no 1 lugar do array, descartando a primeira posicao
    int i, j, menor, troca;
    for(i = 0; i < N-1; i++){ //laco principal, compara todas as posicoes
        menor = i; //procura o menor elemento em relacao a i
        for(j = i+1; j < N; j++){ //j comeca do prox em relacao a i, ate o fim
            if(V[j] < V[menor]) //se for menor
                menor = j; //atualizo o menor
        }
        if(i != menor){ //o menor foi atualizado?
            troca = V[i];//troca valores da posicao atual com a menor
            V[i] = V[menor];
            V[menor] = troca;
        }
    } //fim do principal
}
