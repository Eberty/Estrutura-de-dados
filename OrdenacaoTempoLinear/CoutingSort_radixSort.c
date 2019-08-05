#include <stdio.h>
#include <stdlib.h>

void printfVet(int *V, int n);
int getMax(int *V, int n);
void coutingSort(int *A, int n, int k);
void coutingSort2(int *A, int n, int k);
void radixSort(int *V, int n);

int main() {
    int i, N;

    printf("\n------------------Couting Sort---------------------\n");
    int A[6] = {5,4,8,7,2,9};
    N = 6;
    int maior = getMax(A, N);

    printf("\nSem ordenar:\n");
    printfVet(A, N);
    coutingSort(A, N, maior);
    printf("\n\nOrdenado:\n");
    printfVet(A, N);


    printf("\n--------------------Radix Sort----------------------\n");
    int Rs[7] = {329, 457, 657, 839, 436, 720, 355};
    N = 7;

    printf("\nSem ordenar:\n");
    printfVet(Rs, N);
    radixSort(Rs, N);
    printf("\n\nOrdenado:\n");
    printfVet(Rs, N);

    printf("\n---------------------------------------------------\n");

    system("pause");
    return 0;
}


void printfVet(int *V, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

int getMax(int *V, int n){ //funcao auxiliar que pega o maior elemento do vetor
    int mx = V[0]; //primeiro
    int i;
    for (i = 1; i < n; i++) //do segundo ao ultimo
        if (V[i] > mx) //se for maior
            mx = V[i]; //recebe o valor do maior
    return mx; //retorna o maior
}

void coutingSort(int *A, int n, int k){ //vetor A, quantidade n e maior elemento k
    int i; //contador
    int B[n]; //vetor auxiliar q vai recebe os de A ordenado, possui a mesma qtd de A
    int C[k + 1]; //vetor auxiliar c com a maior posicao representando o valor k (maior valor do vetor)

    for (i = 0; i <= k; i++) //todos os elementos de c sao zerados
        C[i] = 0;

	for (i = 0; i < n; i++) //C[i] eh o numero de Js tais que A[j] = i
        C[A[i]]++; //indica que existe um numero em na posicao a[j]=i no vetor c

	for (i = 1; i <= k; i++) //C[i] eh o numero de Js tais que A[j] <= i
        C[i] += C[i-1]; //soma o valor dessse cara com o anterior
    //ao chegar aqui, significa que existem x numeros menores ou igauis a posicao i de C no vetor A

	for (i = n-1; i >= 0; i--){ //comeca da ultima casa do vetro A ate o inicio
		C[A[i]]--; //o numero foi contabilizado
		B[C[A[i]]] = A[i]; //o valor da casa A[i] vai ser dada a B da casa C[A[i]] (que representa a posicao que deve ser encaixado em B, devido a condicao do for a cima

	}

	for(i=0; i<n; i++) //B eh A ordenado, por isso to substituindo os valores
        A[i] = B[i];
}

void coutingSort2(int *A, int n, int k){ //nesse caso k eh o valor das casas decimais (digitos) que estou ordenando
    int i; //contador
    int B[n]; //vetor auxiliar q vai recebe os de A ordenado, possui a mesma qtd de A
    int C[10]; //nesse couting sort c so possui dez casas pois vai de 0...9 q representa as casas q ele vai olhar para ordenar

    for (i = 0; i < 10; i++)//todos os elementos de c sao zerados
        C[i] = 0;

	for (i = 0; i < n; i++) //C[i] eh o numero de Js tais que A[j] = i
        C[(A[i] / k) % 10]++;//como c so tem dez casas tenho q fazer o %10, a divisao por k eh para pegar o digito q quero

	for (i = 1; i < 10; i++)
        C[i] += C[i-1]; //ao chegar aqui, significa que existem x numeros menores ou igauis a posicao i de C no vetor A

	for (i = n - 1; i >= 0; i--)
		B[--C[(A[i] / k) % 10]] = A[i];

	for(i=0; i<n; i++)
        A[i] = B[i]; //B eh A que esta sendo ordenado, por isso to substituindo os valores
}

void radixSort(int *V, int n){
    int i;
    int m = getMax(V, n); //o valor de max representa o valor da maior casa, q vou usar para a contagem da qtd de digitos q devo percorrer
    for (i = 1; m/i > 0; i *= 10) //for onde i percorre a qtd de digitos
        coutingSort2(V, n, i); //Ordene A[1..n] pelo i-esimo digito usando um metodo estavel.
}
