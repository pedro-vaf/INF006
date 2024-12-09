/*
    ----- Dados do Aluno -----
    Nome: Pedro Vitor Aquino Ferreira
    email: pedro.aquino.ct@gmail.com
    Matrícula: 20222160022
    Semestre: 2024/2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ERROR -1
#define MAX 1000
#define TAM 1000

typedef struct Points {
    float x;
    float y;
    char stringSlice[30];
} Points;

double distancia2Pontos(float x1, float y1, float x2, float y2) {
    float tempX;
    float tempY;
    double temp;
    tempX = (x2 - x1) * (x2 - x1);
    tempY = (y2 - y1) * (y2 - y1);
    temp = sqrt(tempX + tempY);

    return temp;
}

void limparString(char *str) {
    char *p = strchr(str, '\n'); // Procura o caractere '\n'
    if (p) {
        *p = '\0'; // Substitui '\n' por '\0'
    }
}

int main() {
    Points listaPontos[MAX];
    Points listaOrdenada[MAX]; // Cópia para ordenação
    int qtdePontos = 0;
    int linhaAtual = 0;

    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Files cannot be opened\n");
        return ERROR;
    }

    // Verifica a quantidade de linhas no arquivo de entrada    
    char line[TAM];
    int qtdeLinhas = 0;
    while (fgets(line, sizeof(line), fp_in)) {
        qtdeLinhas++;
    }
    rewind(fp_in);

    // Separa a string em slices
    while (fgets(line, sizeof(line), fp_in)) {
        linhaAtual++;
        qtdePontos = 0; // Resetar a contagem para cada linha
        // Ler cada ponto
        char *slice = strtok(line, " ");
        slice = strtok(NULL, " ");  // Ignorar "points"

        while (slice != NULL) {
            float x, y;
            sscanf(slice, "(%f,%f)", &x, &y);
            if (qtdePontos < MAX) {
                listaPontos[qtdePontos].x = x;
                listaPontos[qtdePontos].y = y;
                limparString(slice);
                snprintf(listaPontos[qtdePontos].stringSlice, sizeof(listaPontos[qtdePontos].stringSlice), "%s", slice);
                listaOrdenada[qtdePontos] = listaPontos[qtdePontos]; // Copiar para ordenação
                qtdePontos++;
            }
            slice = strtok(NULL, " ");
        }

        // Calcular a distância total (de acordo com a ordem da entrada)
        float distanciaTotal = 0.0;
        for (int i = 0; i < qtdePontos - 1; i++) {
            distanciaTotal += distancia2Pontos(listaPontos[i].x, listaPontos[i].y, listaPontos[i + 1].x, listaPontos[i + 1].y);
        }

        // Ordenação dos pontos pela distância até a origem (0,0)
        for (int i = 0; i < qtdePontos - 1; i++) {
            for (int j = 0; j < qtdePontos - i - 1; j++) {
                float d1 = distancia2Pontos(0, 0, listaOrdenada[j].x, listaOrdenada[j].y);
                float d2 = distancia2Pontos(0, 0, listaOrdenada[j + 1].x, listaOrdenada[j + 1].y);
                if (d1 > d2) {
                    Points aux = listaOrdenada[j];
                    listaOrdenada[j] = listaOrdenada[j + 1];
                    listaOrdenada[j + 1] = aux;
                }
            }
        }

        // Calcular o shortcut (distância entre o primeiro e o último pontos da entrada)
        float shortcut = distancia2Pontos(listaPontos[0].x, listaPontos[0].y, listaPontos[qtdePontos - 1].x, listaPontos[qtdePontos - 1].y);

        fprintf(fp_out, "points ");
        for (int i = 0; i < qtdePontos; i++) {
            if (i > 0) {
                fprintf(fp_out, " ");  // Adiciona espaço entre os pontos
            }
            fprintf(fp_out, "%s", listaOrdenada[i].stringSlice);
        }
        fprintf(fp_out, " distance %.2f shortcut %.2f", distanciaTotal, shortcut);
        if(linhaAtual != qtdeLinhas){
            fprintf(fp_out, "\n");
        }
    }    

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}