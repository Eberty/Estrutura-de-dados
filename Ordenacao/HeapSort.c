#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printfVet(int *V, int N);
void criaHeap(int *vet, int i, int f);
void heapSort(int *vet, int N);

int main(){
    int vet[11] = {1,23,4,67,-8,54,90,21,14,-5,1};
    int N = 11;

    printf("Sem ordenar:\n");
    printfVet(vet,N);

    printf("Ordenado:\n");
    heapSort(vet,N);
    printfVet(vet,N);

    system("pause");
    return 0;
}


void printfVet(int *V  , int N){ //printar vetor
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
}

// pai(i) -> "filhos": (2*i+1) e (2*i+2)
void criaHeap(int *vet, int i, int f){ //dado vetor, inicio, fim
    int aux = vet[i]; //considero inicialmente o aux como o primeiro valor da particao, essa posicao eh o pai, o i
    int j = i * 2 + 1; //calculo um dos filhos de i, nesse caso 1 filho

    while (j <= f){ //se o filho for menor q o final do vetor eu estou dentro do vetor ainda, entao continuo
        if(j < f){ //pai tem 2 filhos?, tenho q escolher o maior
            if(vet[j] < vet[j + 1]){ //quem eh o maior?
                j = j + 1; //j+1 eh o maior
            }
        }
        if(aux < vet[j]){ //filho maior que o pai(aux que nao mudei ainda, mas se mudasse era o pai)? se for ta incorreto, tenho q corrigir pois pai>filho
            vet[i] = vet[j]; //filho de torna pai
            i = j; //repetir o processo, novos valores para i e j (pais e filhos)
            j = 2 * i + 1;
        }else{ //pai nao eh menor que o filho (pai>filho)
            j = f + 1; //termino processo
        }
    }
    vet[i] = aux; //antigo pai ocupa lugar do ultimo filho analisado, devolvo ele pro lugar
}

void heapSort(int *vet, int N){ //ordenacao usando uma estrutura de heap (AB)
    int i, aux;

    for(i=(N - 1)/2; i >= 0; i--){ //cria heap a partir dos dados (considerando da metade do vetor ate a 1 posicao)
        criaHeap(vet, i, N-1);
    }

    for (i = N-1; i >= 1; i--){
        aux = vet[0];       //pegar o maior elemento da heap (que vai estar  no topo da arvore) e colocar na sua posicao correspondente no array (comecando da ultima-final posicao do vetor)
        vet [0] = vet [i];
        vet [i] = aux;
        criaHeap(vet, 0, i - 1); //reconstruir heap q ficou errada, ate ordenar todo vetor
    }
}
