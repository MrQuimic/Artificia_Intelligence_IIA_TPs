// Trabalho Pratico IIA - LEI
// DEIS-ISEC 2021-2022
/*
 * Authors:
 * Carlos Santos
 * Email: a2003035578@isec.pt
 * Rodrigo Costa
 * Email: a2020133365@isec.pt
 * Created on: 18/12/2021
 * Last Edit: 18/12/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int *init_dados(char *nome, int *n, int *iter, int *opcaoBestSol) {
    FILE *f;
    int *p, *q, *p_orig, *q_orig;
    int i, j, k, x, h;
    int aux1 = 0;
    int aux2 = 0;

    int arrayAux1[2];
    int arrayAux2[2];
    char aux_inicio;
    char str1[10];

    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    // Numero de iteracoes
    while (fscanf(f, "%c", &aux_inicio) != EOF) {
        if (aux_inicio == 'p') {
            if (fscanf(f, " edge %d %d", n, iter))
                break;
        }
    }
    fclose(f);
    // Numero de vertices
    // fscanf(f, " %d", n);
    // Alocacao dinamica da matriz
    p = malloc(sizeof(int) * (((*n) * (*n))));
    if (!p) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    p_orig = malloc(sizeof(int) * (((*n) * (*n))));
    if (!p_orig) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    q = p;
    q_orig = p_orig;

    // Preenchimento da matriz
    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    while (fscanf(f, "%c", &aux_inicio) != EOF) {

        if (aux_inicio == 'p') {

            if (fscanf(f, " edge %d %d", n, iter)) {
                //continue;
                break;
            }
        }
    }

    while (fscanf(f, "%c", &aux_inicio) != EOF) {
        if (aux_inicio == 'e') {
            fscanf(f, "%d", &aux1);
            fscanf(f, "%d", &aux2);
            i = aux1;
            q_orig += 2;
            i = 1;

            *(q_orig) = aux1;
            *(q_orig + 1) = aux2;
        }
    }

    q_orig = p_orig; //reinicializa ponteiro array

    printf("\n\tA importar dados ");

    if (*opcaoBestSol == 2) {

        for (i = 2; i <= ((*iter) * 2); i = i + 2) {

            printf("\t%d -- %d\n", *(q_orig + i), *(q_orig + i + 1));
        }
        printf("\n\tArray \n");
    }
    q_orig = p_orig; //reinicializa ponteiro array
    x = 1;
    int resultado[*n][*n];
    q_orig = p_orig; //reinicializa ponteiro array

    for (i = 2; i <= ((*iter) * 2); i = i + 2) {
        arrayAux1[0] = *(q_orig + i);
        arrayAux1[1] = *(q_orig + i + 1);


        for (j = 0; j < *n; j++) {
            if (*opcaoBestSol == 1) {
                if (i == ((j-1) * (*iter-1) / 10)) {
                    printf("»");
                }
            }
            arrayAux2[0] = j + 1;
            for (k = 0; k < *n; k++) {
                arrayAux2[1] = k + 1;

                if (arrayAux1[0] == arrayAux2[0] && arrayAux1[1] == arrayAux2[1]) {
                    if (i >= 2 && resultado[j][k] == 1) {
                        resultado[j][k] = 0;
                    } else {
                        if (arrayAux1[0] == arrayAux1[1]) {
                            resultado[j][k] = 0;
                        } else {
                            resultado[j][k] = 1;
                            resultado[k][j] = 1;
                        }
                    }
                } else {
                    if (i >= 2 && resultado[j][k] == 1) {
                        continue;
                    } else if (i >= 2 && resultado[j][k] == 0) {
                        resultado[j][k] = 0;
                    } else {
                        resultado[j][k] = 0;
                    }
                }
            }
        }
    }

    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            *(q + i + ((*n) * j)) = resultado[i][j];

            if (j < i && *opcaoBestSol == 2) {
                printf(" [%d]", resultado[i][j]);
            }
        }
        if (j < i && *opcaoBestSol == 2) {
            printf("\n");
        }
    }

    fclose(f);

    free(p_orig);
    return q;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int n, int *mat, int num_iter) {
    int i, j, m, p1, y, *sol_aux, valid = 0, a_rand_check_x = 0, invalids = 1, *arr_rand_p1, findneg1 = 1, fim_x = 1, cont = 0, v_mat = n;


    sol_aux = malloc(sizeof(int) * n + (1));
    if (sol_aux == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        sol_aux[i] = sol[i];
    }

    arr_rand_p1 = malloc(
            sizeof(int) * (n + 1)); //alocar memoria - array para random para ver se numero ja saiu no random x
    if (!arr_rand_p1) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    reinicializa_sol(sol, n, num_iter);//reinicializamos a solução --> tudo a -1

    for (i = 0; i < n; i++) {
        *(arr_rand_p1 + i) = i;
    } //array para random para ver se numero ja saiu no random x

    p1 = random_l_h(0, n - 1); // aleatoriamente um numero

    //printf("\n\t primeira atribuição x %d ", x);

    invalids = 2;
    *(sol + 0) = p1; // atribui primeira posição da nossa solução

    *(arr_rand_p1 + p1) = -1;

    //printf("\t *(sol + 0) %d ", *(sol + 0) );

    for (i = 0; i < n; i++) {  //ele preenche cada espaço da solução
        p1 = check_random(arr_rand_p1, n); //verfica random
        if (p1 == -1) {
            p1 = -1;
            valid = 2;
        } else {
            valid = alter_to_valid(sol, sol_aux, mat, p1, n, num_iter); //verifica se válido
        }
    }

    for (i = 0; i < n; i++) { // tradução para o escreve_sol() para os 1
        if (*(sol + i) != 0) {
            *(sol + i) = 1;
        }
    }

    free(arr_rand_p1);
    free(sol_aux);


}

void reinicializa_sol(int *sol, int v, int num_iter) {
  int i;
    for (i = 0; i < v; i++) {
        // if (sol[i] != 0)
        *(sol + i) = -1;
    }  //reinicializamos a solução --> tudo a -1

}
// Escreve solucao
// Parametros: solucao e numero de vertices

void escreve_sol(int *sol, int vert, int *mat, int num_iter) {
    int i;

    printf("\nConjunto A: ");
    for (i = 0; i < vert; i++)
        if (sol[i] == 0)
            printf("%2d  ", i+1);


    printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n) {
    int i, temp;
    for (i = 0; i < n; i++) {

        a[i] = b[i];
    }
}

int check_random(int *arr_rand_p1, int n) {
    int i, j, p1, v_mat = n;
    int fim_p1 = 1, cont = 0, a_rand_check_p1 = 0;

    do {
        p1 = random_l_h(0, n-1);
        cont = 0;
        v_mat = n;

        if (*(arr_rand_p1 + p1) !=-1) { // se o numero ja foi ou nao utilizado no random faz random ate 6 valores diferentes
            a_rand_check_p1 = 0; //sair do ciclo
            *(arr_rand_p1 + p1) = -1; // colocar como numero ja tirado
        } else { // se for - 1 -----> valor ja repetido anteriormente
            a_rand_check_p1 = 1; // volta a repetir o ciclo

            for (j = 0; j < n; j++) {
                if (*(arr_rand_p1 + j) == -1) {
                    cont++;
                }
                if (cont == n) {
                    fim_p1 = 0;
                    a_rand_check_p1 = 0;
                }
            } //condição de fim - quando array toda percorrida
        }
    } while (a_rand_check_p1 == 1 && fim_p1 == 1); //lança randoms de numeros diferentes X

    if (fim_p1 == 0) {
        p1 = -1;
    }
    return p1;
}

int check_valid(int *a, int *mat, int vert, int num_iter) {
    int i, j = 0, verifica0, verifica = 0;

    for (i = 0; i < vert; i++) {
        //
        if (*(a + i) == 1) {

            for (j; j < num_iter * 2; j += 2) {

                if (*(mat + (j) + ((0))) > i + 1) {
                    break;
                }

                if (*(mat + (j) + ((0))) == i + 1) {

                    if (*(a + (*(mat + (j) + ((1))) - 1)) == 1) {

                        verifica = random_l_h(0, 1);
                        if (verifica == 0) {
                            *(a + (*(mat + (j) + ((0))) - 1)) = 0;
                        } else {
                            *(a + (*(mat + (j) + ((1))) - 1)) = 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int alter_to_valid(int *a, int *b, int *mat, int randomn, int vert, int num_iter) {
    int i, v_mat = vert, valid = 0;

    if (b[randomn] != 0) {

        for (i = 0; i < vert; i++) {
            if (b[i] == 0) {
                if (i == randomn) {
                    break;
                }
                if (*(mat + randomn + (vert * i)) == 1) { // verifica numeros impossiveis
                    v_mat--;
                    break;
                }
            }
        } //verifica se há numero incompativeis

        if (v_mat == vert) { //se encontrou um impossivel não altera  e altera se for igual aos vertices
            b[randomn] = 0;
            valid = 1;
        }
        return 1;
    } else {
        return 0;
    }

}

int liberta_tudo(int *sol, int *mat, int *best, float *mbf, int *best_custo, int vert, int num_iter){

    *mbf = 0;
    *best_custo =0;

    reinicializa_sol(sol, vert, num_iter);//reinicializamos a solução --> tudo a -1
    reinicializa_sol(mat, vert*vert, num_iter);//reinicializamos a solução --> tudo a -1
    reinicializa_sol(best, vert, num_iter);//reinicializamos a solução --> tudo a -1

    free(mat);
    free(sol);
    free(best);

    return 0;

}

// Inicializa o gerador de numeros aleatorios
void init_rand() {
    srand((unsigned) time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
    //return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01() {
    return ((float) rand()) / RAND_MAX;
}

