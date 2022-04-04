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

#ifndef TP2_PCEM_CS_RC_FUNCAO_H
#define TP2_PCEM_CS_RC_FUNCAO_H

void evaluate(int *sol, pchrom pop,int *mat_num_aux, info d, int *mat, int *n);

int calcula_fit2(int a[], int *mat, int vert, int num_iter);

int calcula_fit(int a[], int *mat, int vert, int num_iter);
#endif //TP2_PCEM_CS_RC_FUNCAO_H
