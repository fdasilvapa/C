#include <stdio.h>
#include <stdlib.h>
#define TAM 100

void selectionSort(int *v, int tam){
    int i, j, aux, menor;

    for(i = 0; i < TAM; i++){
        menor = v[i];
        for(j = i + 1; j < TAM; j++){
            if(v[j] < v[i]){
                aux = v[j];
                v[j] = v[i];
                v[i] = aux;
            }
        }
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

    selectionSort(vetor, TAM);

    printf("\nOrdenado:");
    for(i = 0; i < TAM; i++){
        printf("%d ", vetor[i]);
    }

    return 0;
}
