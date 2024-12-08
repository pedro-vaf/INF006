#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define erro -1
#define tamanho 1000 /* Tamanho máximo de pontos */
#define maximo 1000 /* Tamanho maximo de pontos por linha no arquivo de entrada */

typedef struct Point {
    int pontoX, pontoY;
} Point;

double distancia2Pontos(int x1, int y1, int x2, int y2) {
   return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); 
}

int main (){
    Point listaPonto[tamanho], listaOrdenada[tamanho];
    int quantidadePontos = 0;

    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Files cannot be opened\n");
        return erro;
    }

    char line[maximo]; /* Capacitade de caractere máximo da linha */
    while (fgets(line, sizeof(line), fp_in)){
        quantidadePontos = 0; /* Reiniciar a contagem para cada linha */

        /* Ler cada Ponto do arquivo de entrada */
        char *slice = strtok(line, " "); /* Separador padrão de cada ponto */
        slice = strtok(NULL, " ");
        
        while (slice != NULL){
            int x, y;
            sscanf(slice, "(%d,%d)", &x, &y);
            if (quantidadePontos < tamanho){
                listaPonto[quantidadePontos].pontoX = x;
                listaPonto[quantidadePontos].pontoY = y;
                listaOrdenada[quantidadePontos] = listaPonto[quantidadePontos]; /* Cópia para ordenar a lista de pontos na função */
                quantidadePontos = quantidadePontos + 1;
            }
            slice = strtok(NULL, " ");
        }

        /* Calcular a distância total */
        float distanciaTotal = 0.0;
        for (int icont = 0; icont < quantidadePontos - 1; icont = icont + 1){
            distanciaTotal = distancia2Pontos(listaPonto[icont].pontoX, listaPonto[icont].pontoY, listaPonto[icont + 1].pontoX, listaPonto[icont + 1].pontoY);
        }

        /* Ordenação dos ponto usando bubble sort */
        for (int icont = 0; icont < quantidadePontos - 1; icont = icont + 1){
            for (int jcont = 0; jcont < quantidadePontos - icont - 1; jcont = jcont + 1){
                float temp1 = distancia2Pontos(0, 0, listaOrdenada[jcont].pontoX, listaOrdenada[jcont].pontoY);
                float temp2 = distancia2Pontos(0, 0, listaOrdenada[jcont + 1].pontoX, listaOrdenada[jcont + 1].pontoY);
                if (temp1 > temp2){
                    Point aux = listaOrdenada[jcont];
                    listaOrdenada[jcont] = listaOrdenada[jcont + 1];
                    listaOrdenada[jcont + 1] = aux;
                }
            }
        }

        /* Calcular a distância dos pontos, primeiro ponto e último da linha */
        float shortCut = 0.0;
        shortCut += distancia2Pontos(listaPonto[0].pontoX, listaPonto[0].pontoY, listaPonto[quantidadePontos - 1].pontoX, listaPonto[quantidadePontos - 1].pontoY);

        /* Escrever a saída no arquivo */
        fprintf(fp_out, "points");
        for (int icont = 0; icont < quantidadePontos; icont = icont + 1){
            fprintf(fp_out, " (%d,%d)", listaOrdenada[icont].pontoX, listaOrdenada[icont].pontoY);
        }
        fprintf(fp_out, " distance %.2f shortcut %.2f\n", distanciaTotal, shortCut);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}
