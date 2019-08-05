#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printfVet(int *V, int N);
int particiona(int *V, int inicio, int final);
void quickSort(int *V, int inicio, int fim);

int main(){
    int vet[7] = {23,4,67,-8,90,54,21};
    int N = 7;

    printf("Sem ordenar:\n");
    printfVet(vet,N);

    quickSort(vet,0,N-1);
    printf("Ordenado:\n");
    printfVet(vet,N);

    system("pause");
    return 0;
}

void printfVet(int *V, int N){ //printar vetor
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
}

int particiona(int *V, int inicio, int final){ //particionar os dados
    int esq, dir, pivo, aux;
    esq = inicio; //esquerda comeca do inicio
    dir = final; //esquerda comeca do final
    pivo = V[inicio]; //pivo eh a posicao do inicio do vetor
    while(esq < dir){ //enquanto esquerda e direita forem verdadeiras
        while(V[esq] <= pivo) //avanca posicao da esquerda
            esq++;
        while(V[dir] > pivo) //recua posicao da direita, procurando valores maiores que pivo
            dir--;

        if(esq < dir){ //troca esq e dir, procurando valores menores que pivo
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        } //fim do if
    } //fim do while esq e dir

    V[inicio] = V[dir]; //inicio recebera o ultimo valor da direita (onde ela parar)
    V[dir] = pivo; //a posicao da direita se torna o pivo
    return dir; //retorno onde parei com a direita,  eh o  ponto do veotor onde todo mundo antes do vetor eh menor e tod mundo depois eh maior
}

void quickSort(int *V, int inicio, int fim) { //ordenacao por troca de particoes (dividir e conquistar) - pivo - funcao recursiva
    int pivo;
    if(fim > inicio){
        pivo = particiona(V, inicio, fim); //separa os dados em 2 particoes (+ escolhe pivo) -  o pivo nao precisa ordenar
        quickSort(V, inicio, pivo-1); //chama funcao pros elementos antes do pivo
        quickSort(V, pivo+1, fim);//chama funcao pros elementos depois do pivo
    }
}
