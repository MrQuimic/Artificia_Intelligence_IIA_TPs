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
#ifndef TP2_PCEM_CS_RC_ALGORITMO_H
#define TP2_PCEM_CS_RC_ALGORITMO_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OBJ 670
void gera_vizinho(int a[], int b[], int n, int *mat, int num_iter);
void gera_vizinho2 (int a[], int b[], int n, int *mat, int num_iter);
		// Numero maximo de objectos

// EStrutura para armazenar parametros
typedef struct{
    // Tamanho da população
    int popsize;
    // Probabilidade de mutação
    float   pm ;
    // Probabilidade de recombinação
    float   pr;
    // Tamanho do torneio para seleção do pai da próxima geração
    int     tsize;
    // Constante para avaliação com penalização
    float   ro;
    // Número de objetos que se podem colocar na mochila
    int     numGenes;
    // Capacidade da mochila
    int     capacity;
    // Número de gerações
    int     numGenerations;
} info;

// Individuo (solução)
typedef struct individual chrom, *pchrom;


struct individual
{
    // Solução (objetos que estão dentro da mochila)
    int     p[MAX_OBJ];
    // Valor da qualidade da solução
    float   fitness;
    // 1 se for uma solução válida e 0 se não for
    int     valido;
};

void tournament(pchrom pop, info d, pchrom parents);

void genetic_operators(pchrom parents, info d, pchrom offspring);

void crossover(pchrom parents, info d, pchrom offspring);

void mutation(pchrom offspring,info d);

void mutacao_por_troca(pchrom offspring, info d);

void recombinacao_dois_pontos_de_corte(pchrom parents, info d, pchrom offspring);

void recombincacao_uniforme(pchrom parents, info d, pchrom offspring);

#endif //TP2_PCEM_CS_RC_ALGORITMO_H




