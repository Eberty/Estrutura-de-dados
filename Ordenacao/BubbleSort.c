#include <stdio.h>
#include <stdlib.h>

void printfVet(int*, int);
void bubbleSort(int*, int);
void bubbleSort2(int*, int);

int main(){
    int i;
    int N;

    printf("\n---------------------------------------------------\n");
    int a1[10] = {23,4,67,-8,54,90,21,14,-5,1};
    N = 10;
    printf("Sem ordenar:\n");
    printfVet(a1,N);

    printf("Ordenado:\n");
    bubbleSort(a1,N);
    printfVet(a1,N);

    printf("\n\n\n---------------------------------------------------\n");
    int a2[5] = {23,4,67,-8,21};
    N = 5;
    printf("Sem ordenar:\n");
    printfVet(a2,N);

    printf("Ordenado:\n");
    bubbleSort2(a2,N);
    printfVet(a2,N);

    system("pause");
    return 0;
}


void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
} //printar vetor

void bubbleSort(int *V, int N){ //ordenaçao por bolha
    int i, continua, aux;
    do{
        continua = 0;
        for(i = 0; i < N-1; i++){ //troca dois valores consecutivos no vetor
            if (V[i] > V[i+1]){//comparando com o prox
                aux = V[i];//troca com aux
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = 1;//continuar busca
            }
        } //verifica tudo (ja q nao ta otimizado tb verifica o do fim q ja ta no lugar)
    }while(continua);
}

void bubbleSort2(int *V, int N){//bolha otimizado
    int i, continua, aux, fim = N;
    do{
        continua = 0;
        //fim-1 pois eh ate o penultimo por causa do if
        for(i = 0; i < fim-1; i++){ //troca dois valores consecutivos no vetor
            if (V[i] > V[i+1]){//comparando com o prox
                aux = V[i]; //troca com aux
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = i; //continuar busca
            }
        }//quando acaba o maior vai pro final
        fim--;//como o maior ta no fim eu diminuo o fim na contagem de elementos
    }while(continua != 0); //continua ate nao ter mais trocas
}
