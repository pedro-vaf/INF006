#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define erro -1
#define tamanho 1000 /* Tamanho máximo para os arrays */
#define maximo 1000 /* Tamanho máximo de dados da linha */

#define palavra -2
#define pontoFlutuante -3
#define inteiro -4

typedef struct String{
    char string[tamanho];
} String;

typedef struct Point {
    int pontoX, pontoY;
} Point;

typedef struct PointFloat {
    float pontoXf, pontoYf;
} PointFloat;

typedef struct Inteiro {
    int iNumero;
} Inteiro;

typedef struct Float {
    float fNumero;
} Float;

int verificarDado(char buffer[], String listaString[], String listaStringOrdenada[], Float listaFloat[], Float listaFloatOrdenada[], Inteiro listaInt[], Inteiro listaIntOrdenada[], int *quantidadeChar, int *quantidadeFloat, int *quantidadeInt){
    /* Verificar se o dado é uma palavra */
    bool isPalavra = false;
    for (int icont = 0; icont < strlen(buffer); icont = icont + 1){
        if (isalpha(buffer[icont])){
            isPalavra = true;
            break;
        }
    }

    if (isPalavra == true){
        strcpy(listaString[*quantidadeChar].string, buffer);
        strcpy(listaStringOrdenada[*quantidadeChar].string, buffer);
        *quantidadeChar = *quantidadeChar + 1;
        return palavra;
    }

    /* Verificar se o dado é um ponto flutuante */
    bool isFloat = false;
    int pontoCount = 0;
    for (int icont = 0; icont < strlen(buffer); icont = icont + 1){
        if (buffer[icont] == '.'){
            pontoCount = pontoCount + 1;
        }

        if (isdigit(buffer[icont]) || buffer[icont] == '.'){
            isFloat = true;
        } else { isFloat = false; break; }
    }

    if (isFloat == true && pontoCount == 1){
        listaFloat[*quantidadeFloat].fNumero = atof(buffer);
        listaFloatOrdenada[*quantidadeFloat].fNumero = atof(buffer);
        *quantidadeFloat = *quantidadeFloat + 1;
        return pontoFlutuante;
    } else {

        /* Verificar se o dado é um inteiro */
        for (int icont = 0; icont < strlen(buffer); icont = icont + 1){
            if (isdigit(buffer[icont])){
                listaInt[*quantidadeInt].iNumero = atoi(buffer);
                listaIntOrdenada[*quantidadeInt].iNumero = atoi(buffer);
                *quantidadeInt = *quantidadeInt + 1;
                return inteiro;
            }
        }
    }
} 

int main (){
    Point listaPonto[tamanho], listaOrdenada[tamanho];
    PointFloat flistaPonto[tamanho], flistaOrdenada[tamanho];
    Inteiro listaInt[tamanho], listaIntOrdenada[tamanho];
    Float listaFloat[tamanho], listaFloatOrdenada[tamanho];
    String listaString[tamanho], listaStringOrdenada[tamanho];

    int retorno;
    char buffer[maximo];

    int quantidadeInt = 0, quantidadeFloat = 0, quantidadePontos = 0, quantidadeChar = 0, fquantidadePontos = 0;

    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Files cannot be opened\n");
        return erro;
    }

    char line[maximo]; /* Capacitade de caractere máximo da linha */
    while (fgets(line, sizeof(line), fp_in)){
        quantidadeInt = quantidadeFloat = quantidadePontos = quantidadeChar = 0, fquantidadePontos = 0; /* Reiniciar a contagem para cada linha */
        
        /* Ler cada dados do arquivo de entrada */
        char *slice = strtok(line, " "); /* Separador padrão de cada dado */

        while (slice != NULL){
            int iX, iY;
            float fX, fY;
            if (sscanf(slice, " (%d,%d)", &iX, &iY) == 2){
                if(quantidadePontos < tamanho){
                    listaPonto[quantidadePontos].pontoX = iX;
                    listaPonto[quantidadePontos].pontoY = iY;
                    listaOrdenada[quantidadePontos] = listaPonto[quantidadePontos]; /* Cópia para ordenar a lista de pontos na função */
                    quantidadePontos = quantidadePontos + 1;
                }
            } else if (sscanf(slice, " (%f,%f)", &fX, &fY) == 2) {
                if(fquantidadePontos < tamanho){
                    flistaPonto[fquantidadePontos].pontoXf = fX;
                    flistaPonto[fquantidadePontos].pontoYf = fY;
                    flistaOrdenada[fquantidadePontos] = flistaPonto[fquantidadePontos]; /* Cópia para ordenar a lista de pontos na função */
                    fquantidadePontos = fquantidadePontos + 1;
                }
            } else {
                retorno = verificarDado(slice, listaString, listaStringOrdenada, listaFloat, listaFloatOrdenada, listaInt, listaIntOrdenada, &quantidadeChar, &quantidadeFloat, &quantidadeInt);
            }
            slice = strtok(NULL, " ");
        }
        
        /* Ordenação dos ponto usando bubble sort */
        for (int icont = 0; icont < quantidadePontos - 1; icont = icont + 1){
            for (int jcont = 0; jcont < quantidadePontos - icont - 1; jcont = jcont + 1){
                if (listaOrdenada[jcont].pontoX > listaOrdenada[jcont + 1].pontoX){
                    Point aux = listaOrdenada[jcont];
                    listaOrdenada[jcont] = listaOrdenada[jcont + 1];
                    listaOrdenada[jcont + 1] = aux;
                }
            }
        }

        /* Ordenação dos ponto (float) usando bubble sort */
        for (int icont = 0; icont < fquantidadePontos - 1; icont = icont + 1){
            for (int jcont = 0; jcont < fquantidadePontos - icont - 1; jcont = jcont + 1){
                if (flistaOrdenada[jcont].pontoXf > flistaOrdenada[jcont + 1].pontoXf){
                    PointFloat aux = flistaOrdenada[jcont];
                    flistaOrdenada[jcont] = flistaOrdenada[jcont + 1];
                    flistaOrdenada[jcont + 1] = aux;
                }
            }
        }

        /* Ordenação da String usando bubble sort */
        for (int icont = 0; icont < quantidadeChar - 1; icont = icont + 1) {
            for (int jcont = 0; jcont < quantidadeChar - icont - 1; jcont = jcont + 1) {
                bool troca = false;
                for (int kcont = 0; kcont < tamanho; kcont = kcont + 1) {
                    /* Se a string atual for maior que a próxima */
                    if (listaStringOrdenada[jcont].string[kcont] > listaStringOrdenada[jcont + 1].string[kcont]) {
                        troca = true;
                        break;
                    }
                    /* Se a string atual for menor, não é necessário continuar a comparação */
                    if (listaStringOrdenada[jcont].string[kcont] < listaStringOrdenada[jcont + 1].string[kcont]) {
                        break;
                    }
                }
                /* Troca as posições se necessário */
                if (troca) {
                    String aux = listaStringOrdenada[jcont];
                    listaStringOrdenada[jcont] = listaStringOrdenada[jcont + 1];
                    listaStringOrdenada[jcont + 1] = aux;
                }
            }
        }

        /* Ordenação do Float usando bubble sort */
        for (int icont = 0; icont < quantidadeFloat - 1; icont = icont + 1){
            for (int jcont = 0; jcont < quantidadeFloat - icont - 1; jcont = jcont + 1){
                if (listaFloatOrdenada[jcont].fNumero > listaFloatOrdenada[jcont + 1].fNumero){
                    Float aux = listaFloatOrdenada[jcont];
                    listaFloatOrdenada[jcont] = listaFloatOrdenada[jcont + 1];
                    listaFloatOrdenada[jcont + 1] = aux;
                }
            }
        }
        

        /* Ordenação do Inteiro usando bubble sort */
        for (int icont = 0; icont < quantidadeInt - 1; icont = icont + 1){
            for (int jcont = 0; jcont < quantidadeInt - icont - 1; jcont = jcont + 1){
                if (listaIntOrdenada[jcont].iNumero > listaIntOrdenada[jcont + 1].iNumero){
                    Inteiro aux = listaIntOrdenada[jcont];
                    listaIntOrdenada[jcont] = listaIntOrdenada[jcont + 1];
                    listaIntOrdenada[jcont + 1] = aux;
                }
            }
        }
        

        /* Escrever os dados ordenados no arquivo de saida */
        fprintf(fp_out, "str:");
        for (int icont = 0; icont < quantidadeChar; icont = icont + 1){
            fprintf(fp_out, " %s", listaStringOrdenada[icont].string);
        }
        fprintf(fp_out, " int:");
        for (int icont = 0; icont < quantidadeInt; icont = icont + 1){
            fprintf(fp_out, " %d", listaIntOrdenada[icont].iNumero);
        }
        fprintf(fp_out, " float:");
        for (int icont = 0; icont < quantidadeFloat; icont = icont + 1){
            fprintf(fp_out, " %.2f", listaFloatOrdenada[icont].fNumero);
        }
        fprintf(fp_out, " p:");
        if (fquantidadePontos > 0) { // Se houver pontos flutuantes
            for (int icont = 0; icont < fquantidadePontos; icont = icont + 1) {
                fprintf(fp_out, " (%.2f,%.2f)", flistaOrdenada[icont].pontoXf, flistaOrdenada[icont].pontoYf);
            }
        }
        if (quantidadePontos > 0) { // Se houver pontos inteiros
            for (int icont = 0; icont < quantidadePontos; icont = icont + 1) {
                fprintf(fp_out, " (%d,%d)", listaOrdenada[icont].pontoX, listaOrdenada[icont].pontoY);
            }
        }
        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}
