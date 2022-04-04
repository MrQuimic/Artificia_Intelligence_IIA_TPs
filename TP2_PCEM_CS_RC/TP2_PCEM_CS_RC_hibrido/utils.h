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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "algoritmo.h"


info init_data(char *nome);

int* read_data(char *nome, int *mat, int mat_num_aux[], int *n, int *iter, int *opcaoBestSol);

pchrom init_pop(info d, pchrom indiv, int *sol, int *mat, int *arr_rand_p1, int n);

void print_pop(pchrom pop, info d);

chrom get_best(pchrom pop, info d, chrom best);

void write_best(chrom x, info d);

void reinicializa_sol(int *sol, int v, int num_iter);

int check_random(int *arr_rand_p1, int n);

int check_valid(int *a, int *mat, int *mat_num_aux, int vert, int num_iter);

int check_valid2(int *a, int *mat,int *mat_num_aux, int vert, int num_iter);

int alter_to_valid(int *a, int *b, int *mat, int randomn, int vert, int num_iter);

int liberta_tudo(int *sol, int *mat, float *mbf, info d, chrom pop, int n);

void init_rand();

int flip();

int random_l_h(int min, int max);

float rand_01();



#endif //TP2_PCEM_CS_RC_UTILS_H
