#include <stdio.h>
#include <stdlib.h>
#define TAM 100

//bubbleSort otimizado
void bubbleSort(int *v, int tam){
    int i, aux, troca = 1;

    while(troca){
        troca = 0;
        for(i = 0; i < tam - 1; i++){
            if(v[i] > v[i + 1]){
                troca = 1;
                aux = v[i + 1];
                v[i + 1] = v[i];
                v[i] = aux;
            }
        }
        tam--;
    }

}

int main(){
    int vetor[TAM], i, valores = TAM;
    //Preencher o vetor com valores decrescentes
    for(i = 0; i < TAM; i++){
        vetor[i] = valores;
        valores--;
    }

    //Printar vetor atual
    printf("Ordem atual:");
    for(i = 0; i < TAM; i++){
        printf("%d ", vetor[i]);
    }

    bubbleSort(vetor, TAM);

    printf("\nOrdenado: ");
    for(i = 0; i < TAM; i++){
        printf("%d ", vetor[i]);
    }

    return 0;
}
