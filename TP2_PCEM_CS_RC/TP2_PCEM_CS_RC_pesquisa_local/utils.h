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

#ifndef TP2_PCEM_CS_RC_UTILS_H
#define TP2_PCEM_CS_RC_UTILS_H

int* init_dados(char *nome, int *n, int *iter, int *opcaoBestSol);

void gera_sol_inicial(int *sol, int v, int *mat, int num_iter);

void escreve_sol(int *sol, int vert, int *mat, int num_iter);

void substitui(int a[], int b[], int n);

void reinicializa_sol(int *sol, int v, int num_iter);

int check_random(int *arr_rand_p1, int n);

int check_valid(int *a, int *mat, int vert, int num_iter);

int alter_to_valid(int *a, int *b, int *mat, int randomn, int vert, int num_iter);

int liberta_tudo(int *sol, int *mat, int *best, float *mbf, int *best_custo, int vert, int num_iter);

void init_rand(void);

int random_l_h(int min, int max);

float rand_01(void);

#endif //TP2_PCEM_CS_RC_UTILS_H
