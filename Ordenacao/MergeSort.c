#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printfVet(int*, int);
void merge(int*, int, int, int);
void mergeSort(int*, int, int);

int main(){
    int N = 7, a[7] = {23,4,67,-8,90,54,21};

    printf("\nNao ordenado\n");
    printfVet(a, N);

    printf("\nOrdenado\n");
    mergeSort(a, 0, N-1);
    printfVet(a, N);

    system("pause");
    return 0;
}


void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

void merge(int *V, int inicio, int meio, int fim){ // combina, recebo as 3 partes do vetor principal
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;

    tamanho = fim-inicio+1; //tamanho do vetor eh so olhar o inicio e o fim
    p1 = inicio; //calculo indice p1 (inicio) pois vou combinar doi vetores
    p2 = meio+1; //calculo indice p2 (meio)

    temp = (int *) malloc(tamanho*sizeof(int)); //alocando vetor auxiliar
    if(temp != NULL){ //se eu consegui alocar faz
        for(i=0; i<tamanho; i++){ //para percorrer vetor temp
            if(!fim1 && !fim2){ //verifica - nao chegou no fim de ngm ainda
                if(V[p1] < V[p2]) //combinar ordenado (quem eh o menor? entre p1 e p2) - copio o menor
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];

                //quero para de verificar?
                if(p1>meio) fim1=1; //vetor 1 acabou?
                if(p2>fim) fim2=1; //vetor 2 acabou?
            }else{ //copia o que sobrar
                if(!fim1) //quem foi q acabou? p1 ou p2?
                    temp[i]=V[p1++]; //p2 acabou, copia p1
                else
                    temp[i]=V[p2++]; //p1 acabou cobia p2
            }
        } //fim do for

        //importante
        for(j=0, k=inicio; j<tamanho; j++, k++) //copia do auxiliar para o original
            V[k]=temp[j];

    } //fim do if principal
    free(temp); //libera a alocacao pq ja copiei ele pro original
}

void mergeSort(int *V, int inicio, int fim){ //ordenacao por mistura (dividir para conquistar - recursivo)
    int meio;
    if(inicio < fim){ //se inicio menor q fim
        //floor
        meio = floor((inicio+fim)/2); //piso (valor inteiro) funcao ja existe
        mergeSort(V,inicio,meio); //chama a funcao para a primeira metade
        mergeSort(V,meio+1,fim); //chama a funcao para a segunda metade
        merge(V,inicio,meio,fim); //combina as 2 metades de forma ordenada
    }
}
