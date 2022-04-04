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


#ifndef TP2_PCEM_CS_RC_ALGORITMO2_H
#define TP2_PCEM_CS_RC_ALGORITMO2_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"


void gera_vizinho(int a[], int b[], int *mat, int n,int num_iter);

void gera_vizinho2 (int a[], int b[],  int *mat, int n, int num_iter);

void trepa_colinas(int sol[], int *mat, pchrom pop,  info d, int vert, int num_iter, int opcaoGeraVizinho);



#endif //TP2_PCEM_CS_RC_ALGORITMO2_H