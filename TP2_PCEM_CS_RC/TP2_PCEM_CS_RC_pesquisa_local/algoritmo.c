#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include "math.h"

#define PROB 0.01
#define TMAX 100
#define TMIN 2
// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices

void gera_vizinho(int a[], int b[], int n, int *mat, int num_iter) {
    int i, p1, p2, *arr_rand_p1, valid = 0;

    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }

    arr_rand_p1 = malloc(sizeof(int) * (n + 1)); //alocar memoria - array para random para ver se numero ja saiu no random x
    if (!arr_rand_p1) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        *(arr_rand_p1 + i) = i;
    }

    do {
        p1 = check_random(arr_rand_p1, n-1); //verfica random
        if (p1 == -1) {
            p1 = -1;
            valid = 2;
        } else {
            valid = alter_to_valid(a, b, mat, p1, n, num_iter); //verifica se válido
        }
    }while (valid == 0);
        // Encontra posicao com valor 1
        do
            p2 = random_l_h(0, n-1);
        while (b[p2] != 1);


        b[p2] = 1;
}

void gera_vizinho2(int a[], int b[], int n, int *mat, int num_iter) {
    int i, p1, p2, p3, p4, *arr_rand_p1, *arr_rand_p3, valid = 0;

    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }

    arr_rand_p1 = malloc(sizeof(int) * (n)); //alocar memoria - array para random para ver se numero ja saiu no random x
    if (!arr_rand_p1) {
        printf("Erro na alocacao de memoria p1\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        *(arr_rand_p1 + i) = i;
    }

    do {
        p1 = check_random(arr_rand_p1, n-1); //verfica random
        if (p1 == -1) {
            p1 = -1;
            valid = 2;
        } else {
            valid = alter_to_valid(a, b, mat, p1, n, num_iter); //verifica se válido
        }
    }while (valid == 0);
    // Encontra posicao com valor 1
    do
        p2 = random_l_h(0, n-1);
    while (b[p2] != 1);

    b[p2] = 1;

    arr_rand_p3 = malloc(sizeof(int) * (n)); //alocar memoria - array para random para ver se numero ja saiu no random x
    if (!arr_rand_p3) {
        printf("Erro na alocacao de memoria p3\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        *(arr_rand_p3 + i) = i;
    }

    do {
        p3 = check_random(arr_rand_p3, n-1); //verfica random
        if (p3 == -1) {
            p3 = -1;
            valid = 2;
        } else {
            valid = alter_to_valid(a, b, mat, p3, n, num_iter); //verifica se válido
        }
    }while (valid == 0);

    // Encontra posicao com valor 1
    do
        p4 = random_l_h(0, n-1);
    while (b[p4] != 1);

    b[p4] = 1;

    free(arr_rand_p1);
    free(arr_rand_p3);

}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter, int opcaoGeraVizinho) {
    int custo, custo_viz, i;
    int *nova_sol;

    // Avalia solucao inicial
    nova_sol = malloc(sizeof(int) * vert);
    if (nova_sol == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    custo = calcula_fit(sol, mat, vert, num_iter);
    if(opcaoGeraVizinho == 1){
        for (i = 0; i < num_iter; i++) { // Para cada subconjunto
            // Gera vizinho

            gera_vizinho(sol, nova_sol, vert, mat, num_iter);
            // Avalia vizinho
            custo_viz = 0;
            custo_viz = calcula_fit(nova_sol, mat, vert, num_iter);
            //printf("\ncusto_viz0 %d\n", custo_viz);
            // Aceita vizinho se o custo aumentar (problema de maximização)
            if (custo_viz >= custo) {
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }
    } else if(opcaoGeraVizinho == 2){
        for (i = 0; i < num_iter; i++) { // Para cada subconjunto
            // Gera vizinho

            gera_vizinho2(sol, nova_sol, vert, mat, num_iter);
            // Avalia vizinho
            custo_viz = 0;
            custo_viz = calcula_fit(nova_sol, mat, vert, num_iter);
            //printf("\ncusto_viz0 %d\n", custo_viz);
            // Aceita vizinho se o custo aumentar (problema de maximização)
            if (custo_viz > custo) {
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    return custo;
}
