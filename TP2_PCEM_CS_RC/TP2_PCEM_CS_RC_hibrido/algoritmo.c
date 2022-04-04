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
//#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"


// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(pchrom pop, info d, pchrom parents)
{
    int i, x1, x2, parent1, pop1;

    // Realiza popsize torneios
    for(i=0; i<d.popsize-1;i++){
        x1 = random_l_h(0, d.capacity);
        do
            x2 = random_l_h(0, d.capacity);
        while(x1==x2);

 /*
        if((pop+x1)->fitness <= (pop+x2)->fitness)	{	// Problema de maximizacao
            *(parents+d.popsize) = *(parents+x1);
        }
        else{
            *(parents+d.popsize) = *(parents+x2);
        }
*/

    }
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pchrom parents, info d, pchrom offspring){
    // Recombinação com um ponto de corte
    recombincacao_uniforme(parents, d, offspring);
    //recombinacao_dois_pontos_de_corte(parents, d, offspring);
    //recombincacao_uniforme(parents, d, offspring);
    //crossover(parents, d, offspring);

    // Mutação binária
    //mutacao_por_troca(offspring, d);
    mutation(offspring, d);
}

// Preenche o vector descendentes com o resultado das operações de recombinação
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void crossover(pchrom parents, info d, pchrom offspring)
{
    int i, j, point;

    for (i=0; i<d.popsize-1; i+=2)
    {
        if (rand_01() < d.pr)
        {
            point = random_l_h(0, d.numGenes-1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, info d){
    int i, j;

    for (i=0; i<d.popsize-1; i++)
        for (j=0; j<d.numGenes; j++)
            if (rand_01() < d.pm)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

// 4.3 > Operador de mutação (por troca)
void mutacao_por_troca(pchrom offspring, info d){
    int i, pos1, pos2, aux, count=0;

    for(i = 0; i < d.popsize-1; i++){
        if(rand_01() < d.pm){
            count = 0;
            do{
                count++;
                pos1 = random_l_h(0, d.capacity);

            } while(offspring[i].p[pos1] == 1 && count<d.capacity); // encontra fim e sai
            count = 0;
            do{
                count++;

                pos2 = random_l_h(0, d.capacity);

            } while(offspring[i].p[pos2] == 0 && count<d.capacity && pos1 == pos2);

            aux = offspring[i].p[pos1];
            offspring[i].p[pos1] = offspring[i].p[pos2];
            offspring[i].p[pos2] = aux;
        }
    }
}

// 4.4 Operador recombinação
// operador com 2 pontos de corte
// Operador com 2 pontos de corte e operador de commbinação uniforme
// diferenca entre 1 ponto e 2 pontos -> na 1 ponto usa-se apenas point1
void recombinacao_dois_pontos_de_corte(pchrom parents, info d, pchrom offspring){
    int i, j, point1, point2;

    for(i = 0; i < d.popsize-1; i += 2){
        if(rand_01() < d.pr){
            point1 = random_l_h(0,d.numGenes - 2);
            point2 = random_l_h(point1 + 1, d.numGenes - 1);

            for(j = 0; j < point1; j++){ // Igual aos pais
                offspring[i].p[j]  = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }

            for(j = point1; j < point2; j++){ // TROCA
                offspring[i].p[j]  = parents[i+1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }

            for(j = point2; j < d.numGenes; j++){ // Igual aos pais
                offspring[i].p[j]  = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
        } else {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i + 1];
        }
    }
}

// 4.5 operador de recombinação Uniforme
void recombincacao_uniforme(pchrom parents, info d, pchrom offspring){
    int i, j;

    for(i = 0; i < d.popsize-1; i += 2){
        if(rand_01() < d.pr){
            for(j = 0; j < d.capacity; j++){
                if(flip() == 1){ // funcao utils.c
                    offspring[i].p[j]  = parents[i].p[j];
                    offspring[i + 1].p[j] = parents[i + 1].p[j];
                } else {
                    offspring[i].p[j] = parents[i + 1].p[j];
                    offspring[i + 1].p[j] = parents[i].p[j];
                }
            }
        } else {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}


