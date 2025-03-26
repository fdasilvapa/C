#include <stdio.h>
#include <stdlib.h>
#define TAM 100

void insertionSort(int *v, int tam){
    int i;
    for(i = 1; i < tam; i++){
        int aux, j = i;
        aux = v[j];
        while(j > 0 && aux < v[j - 1]){
            v[j] = v[j - 1];
            j--;
        }
        v[j] = aux;
    }
}

int main(){
    int vetor[TAM], i, valores = TAM;

    for(i = 0; i < TAM; i++){
        vetor[i] = valores;
        valores--;
    }

    printf("Ordem atual:");
    for(i = 0; i < TAM; i++){
        printf("%d ", vetor[i]);
    }

    insertionSort(vetor, TAM);

    printf("\nOrdenado:");
    for(i = 0; i < TAM; i++){
        printf("%d ", vetor[i]);
    }

    return 0;
}
