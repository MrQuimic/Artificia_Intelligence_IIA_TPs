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
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
// Calcula a qualidade de uma solução
// Recebe:  A solução, a, a matriz de adjacências, mat, e o número de vértices, vert
// Devolve: O custo que é o número de ligações que existem na solução

// Calcula a qualidade de uma solução
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual(int *sol, int *a, info d, int *mat, int n, int *v) {
    int i, j, k, v_mat;
    float sum_profit, sum_weight; sum_weight = sum_profit = 0;

    // Percorre todos os objectos
    for (i=0; i < n; i++){
        // Actualiza o peso total

        // Verifica se o objecto i esta na mochila
        if (*(a+i) == 1){
            // Actualiza o lucro total
            ++sum_profit;
            *v = 1;
        }else if (*(a+i) == 0){
            *v = 0;
            ++sum_weight;
        }else if (*(a+i) > 1){
            ++sum_weight;
            *v = 0;
        }else if (*(a+i) < 0){
            ++sum_weight;
            *v = 0;
        }
    }
        // Solucao válida


        return sum_profit;

}



// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(int *sol, pchrom pop,int *mat_num_aux, info d, int *mat, int *n){
    int i, j, check, *sol_aux;
        sol_aux = sol;


    //check_valid2(sol_aux, mat,mat_num_aux, *n, d.numGenes);

    for (i=0; i<d.popsize; i++){
        check_valid(sol, mat, mat_num_aux, *n, d.numGenes);
            pop[i].fitness = eval_individual(sol, pop[i].p, d, mat, *n, &pop[i].valido);
    }

}
