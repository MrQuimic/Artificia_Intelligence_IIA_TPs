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
#include "funcao.h"
#include "utils.h"
// Calcula a qualidade de uma solução
// Recebe:  A solução, a, a matriz de adjacências, mat, e o número de vértices, vert
// Devolve: O custo que é o número de ligações que existem na solução

int calcula_fit(int a[], int *mat, int vert, int num_iter)
{
    int total=0;
    int i;

    for(i=0; i< vert; i++) {
            if (a[i] == 0) {
                total++; //soma so se for valor 0
            }
    }

    return total;
}

int calcula_fit2(int a[], int *mat, int vert, int num_iter)
{
    int total=0;
    int i, j, h;

    check_valid(a, mat, vert, num_iter);
    for(i=0; i< vert; i++) {
        if (a[i] == 0) {
            total++; //soma so se for valor 0
        }
    }


    return total;
}

