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
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 100

void menuFicheiros(){
    printf("Selecione os ficheiros:\n\n\n");
    printf("\t# 0 - Teste.txt\n"
           "\t# 1 - File1.txt\n"
           "\t# 2 - File2.txt\n"
           "\t# 3 - File3.txt\n"
           "\t# 4 - File4.txt\n"
           "\t# 5 - File5.txt\n"
           "\t# 6 - File6.txt\n"
           "\t# 7 - EXIT\n");
}

void selecionaFicheiro(char (*nomeFicheiro)[]){
    int opcao = 8;

    while(opcao < 0 || opcao > 7){
        printf("Opcao:  ");
        scanf("%d",&opcao);

        switch(opcao){
            case 0: strcpy(*nomeFicheiro,"teste.txt");
                return;
            case 1: strcpy(*nomeFicheiro,"file1.txt");
                return;
            case 2: strcpy(*nomeFicheiro,"file2.txt");
                return;
            case 3: strcpy(*nomeFicheiro,"file3.txt");
                return;
            case 4: strcpy(*nomeFicheiro,"file4.txt");
                return;
            case 5: strcpy(*nomeFicheiro,"file5.txt");
                return;
            case 6: strcpy(*nomeFicheiro,"file6.txt");
                return;
            case 7: strcpy(*nomeFicheiro,"exit");
                return;
            default: printf("Selecionou a opcao errada!\n");
                break;
        }
    }
}

void selectGeraVizinho(int *opcao){

    *opcao = 0;

    printf("Selecione que tipo de gera Vizinho que pretende: \n\n");
    printf("\t# 1 - Gera vizinho 1\n"
           "\t# 2 - Gera vizinho 2\n\n");

    while(*opcao < 1 || *opcao > 2){
        printf("Opcao:  ");
        scanf("%d",opcao);
    }
}

void select_onlyBestSol(int *opcao){

    *opcao = 0;

    printf("Visualização: \n\n");
    printf("\t# 1 - Ver apenas a solução final \n"
           "\t# 2 - Ver as soluções de cada run\n\n");

    while(*opcao < 1 || *opcao > 2){
        printf("Opcao:  ");
        scanf("%d",opcao);
    }
}

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     vert, num_iter, k, runs, custo, best_custo=0;
    int     *grafo, *sol, *best;
	float   mbf = 0.0;
    int opcaoGeraVizinho = 1, opcaoBestSol = 1;

	if(argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
        if(argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nome_fich, argv[1]);
        }
        else{
            runs = DEFAULT_RUNS;
        }

	if(runs <= 0)
		return 0;

    menuFicheiros();

    while(1){
        selecionaFicheiro(&nome_fich); // Selecionar qual é o ficheiro
        if (strcmp("exit", nome_fich) == 0) {
            printf("\n\nA terminar...\n");
            scanf(" ");
            return 0;
        }

        selectGeraVizinho(&opcaoGeraVizinho); // selecionar qual é o geraVizinho
        select_onlyBestSol(&opcaoBestSol);
        init_rand();
        // Preenche matriz de adjacencias
        grafo = init_dados(nome_fich, &vert, &num_iter,&opcaoBestSol);
        //printf("\t\t\t\t\t\t---%d\n", grafo);


        sol = malloc(sizeof(int)*(vert));
        //printf("vert %d- %d \n", runs, vert);
        best = malloc(sizeof(int)*(vert));

        if(sol == NULL || best == NULL)
        {
            printf("Erro na alocacao de memoria");
            exit(1);
        }


        for(k=0; k<runs; k++)
        {
            // Gerar solucao inicial
            gera_sol_inicial(sol, vert, grafo, num_iter);
            //escreve_sol(sol, vert, grafo,num_iter);
            // Trepa colinas

            custo = trepa_colinas(sol, grafo, vert, num_iter, opcaoGeraVizinho);
            if(opcaoBestSol == 2){
                // Escreve resultados da repeticao k
                printf("\nRepeticao %d:", k);
                escreve_sol(sol, vert, grafo,num_iter);
                printf("Custo final: %2d\n", custo);
            }
                mbf += custo;
                if(k==0 || best_custo < custo)
                {
                    best_custo = custo;
                    substitui(best, sol, vert);
                }

        }
        // Escreve eresultados globais
        if(opcaoBestSol == 1) {
            printf("\n\nFicheiro: %s -- Runs: %i\n", nome_fich, k);
        }
        printf("\nMBF: %f\n", mbf/k);

        printf("\nMelhor solucao encontrada");
        escreve_sol(best, vert,grafo, num_iter);
        printf("Custo final: %2d\n", best_custo);

        liberta_tudo(sol, grafo, best, &mbf, &best_custo, vert, num_iter);

        printf("\n\n(#7 para sair) \nEscolha ficheiro - ");
    }

    return 0;
}