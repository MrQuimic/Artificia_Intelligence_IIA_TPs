#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS    50

void menuFicheiros() {
    printf("\n\n  -- Trabalho desenvolvido em contexto académico \n");
    printf("  -- IIA - ISEC - 2021/2022 \n");
    printf("  -- Aluno: Carlos Santos - Email: a2003035578@isec.pt  \n");
    printf("  -- Aluno: Rodrigo Costa - Email: a2020133325@isec.pt  \n");
    printf("  -- Trabalho desenvolvido em contexto académico ## \n\n\n");
    printf("\n  .. Max MAX_OBJ a 670\n\n\n");


    printf("  Selecione os ficheiros:\n\n\n");
    printf("\t# 0 - Teste.txt\n"
           "\t# 1 - File1.txt\n"
           "\t# 2 - File2.txt\n"
           "\t# 3 - File3.txt\n"
           "\t# 4 - File4.txt\n"
           "\t# 5 - File5.txt\n"
           "\t# 6 - File6.txt\n"
           "\t# 7 - EXIT\n");
}


void selecionaFicheiro(char (*nomeFicheiro)[]) {
    int opcao = 8;

    while (opcao < 0 || opcao > 7) {
        printf("\n  Opcao:  ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                strcpy(*nomeFicheiro, "teste.txt");
                return;
            case 1:
                strcpy(*nomeFicheiro, "file1.txt");
                return;
            case 2:
                strcpy(*nomeFicheiro, "file2.txt");
                return;
            case 3:
                strcpy(*nomeFicheiro, "file3.txt");
                return;
            case 4:
                strcpy(*nomeFicheiro, "file4.txt");
                return;
            case 5:
                strcpy(*nomeFicheiro, "file5.txt");
                return;
            case 6:
                strcpy(*nomeFicheiro, "file6.txt");
                return;
            case 7:
                strcpy(*nomeFicheiro, "exit");
                return;
            default:
                printf("Selecionou a opcao errada!\n");
                break;
        }
    }
}

void select_onlyBestSol(int *opcao) {

    *opcao = 0;

    printf("\n  Visualização: \n\n");
    printf("\t# 1 - Ver apenas a solução final \n"
           "\t# 2 - Ver as soluções de cada run\n\n");

    while (*opcao < 1 || *opcao > 2) {
        printf("  Opcao:  ");
        scanf("%d", opcao);
    }
}

int main(int argc, char *argv[]) {
    char nome[100];
    FILE *f;
    info EA_param;
    pchrom pop = NULL, parents = NULL, parentsaux = NULL, popaux = NULL;
    chrom best_run, best_ever;
    int gen_actual, r, j, runs, i, *sol, *mataux, *solaux, *mat, *mat_num_aux, *arr_rand_p1, opcaoBestSol = 1;
    float mbf = 0.0, inv, invTotal = 0;


    // Lê os argumentos de entrada
    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome, argv[1]);
    } else
        // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
    if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome, argv[1]);
    }
        // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
    else {
        runs = DEFAULT_RUNS;
    }
    // Se o número de execuções do processo for menor ou igual a 0, termina o programa
    if (runs <= 0)
        return 0;


    menuFicheiros();

    while (1) {

        selecionaFicheiro(&nome);
        select_onlyBestSol(&opcaoBestSol);
        if (strcmp("exit", nome) == 0) {
            printf("\n\nA terminar...\n");
            scanf("\n");
            free(mat_num_aux);
            free(parents);
            free(popaux);

            liberta_tudo(sol, mat, &mbf, EA_param, best_ever, EA_param.capacity);
            return 0;
        }


        EA_param = init_data(nome);

        // Numero de vertices
        // fscanf(f, " %d", EA_param.capacity);
        // Alocacao dinamica da matriz
        mat = malloc(sizeof(int) * (EA_param.capacity * EA_param.capacity));
        if (!mat) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        mataux = mat;

        sol = malloc(sizeof(int) * (EA_param.capacity));
        if (!sol) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        solaux = sol;

        pop = malloc(sizeof(chrom) * EA_param.popsize);
        if (pop == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        popaux = pop;

        arr_rand_p1 = malloc(sizeof(int) * (EA_param.capacity)); //alocar memoria - array para random para ver se numero ja saiu no random x
        if (!arr_rand_p1) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        parents = malloc(sizeof(chrom) * (EA_param.popsize));
        // Caso não consiga fazer a alocação, envia aviso e termina o programa
        if (parents == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        parentsaux = parents;
        //Inicializa a geração dos números aleatórios
        init_rand();

        // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
        mat_num_aux = read_data(nome, mat, mat_num_aux, &EA_param.capacity, &EA_param.numGenes, &opcaoBestSol);


        // Faz um ciclo com o número de execuções definidas

        for (r = 0; r < runs; r++) {
            sol = solaux;
            if (opcaoBestSol == 2) {
                printf("Repeticao %d\n", r + 1);
            }
            // Reserva espaço para os pais da população seguinte
            pop = popaux;
            parents = parentsaux;

            // Geração da população inicial
            pop = init_pop(EA_param, pop, sol, mat, arr_rand_p1, EA_param.capacity);
            best_run = get_best(pop, EA_param, best_run);

            // Avalia a população inicial
            evaluate(sol, pop, mat_num_aux, EA_param, mat, &EA_param.capacity);

            gen_actual = 1;
            // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
            best_run = pop[0];
            // Encontra-se a melhor solução dentro de toda a população
            best_run = get_best(pop, EA_param, best_run);


            // Ciclo de optimização
            inv =0;
            while (gen_actual <= EA_param.numGenerations) {
                // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                tournament(pop, EA_param, parents);
                // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                genetic_operators(parents, EA_param, pop);
                // Avalia a nova população (a dos filhos)
                evaluate(sol, pop,mat_num_aux,  EA_param, mat, &EA_param.capacity);
                // Actualiza a melhor solução encontrada
                best_run = get_best(pop, EA_param, best_run);
                gen_actual++;
                // Contagem das soluções inválidas

                    if (pop->valido == 0)
                        inv++;
            }

            // Escreve resultados da repetição que terminou
            if (opcaoBestSol == 2) {
                printf("\n\n Repeticao %d:", r);

            write_best(best_run, EA_param);

                printf("\nPercentagem Invalidos: %f\n", (100 * inv) / (EA_param.capacity + EA_param.popsize + EA_param.numGenerations));
            }
            mbf += best_run.fitness;

            if (r == 0 || best_run.fitness > best_ever.fitness)
                best_ever = best_run;


            reinicializa_sol(sol, EA_param.capacity, EA_param.numGenes);//reinicializamos a solução --> tudo a -1
            reinicializa_sol(parents->p, EA_param.capacity, EA_param.numGenes);//reinicializamos a solução --> tudo a -1
            reinicializa_sol(pop->p, EA_param.capacity, EA_param.numGenes);//reinicializamos a solução --> tudo a -1


        }
        invTotal += inv;
        sol = solaux;
        // Escreve resultados globais
        if (opcaoBestSol == 1) {
            printf("\n\nFicheiro: %s -- Runs: %i\n", nome, r);
        }

        printf("\nMedia de Invalidos: %f\n", 100 * invTotal / ((EA_param.capacity + EA_param.popsize + EA_param.numGenerations)* r));

        printf("\n\nMBF: %f\n", mbf /  /*(EA_param.numGenerations)*/ r);
        printf("\nMelhor solucao encontrada");
        write_best(best_ever, EA_param);
       // free(mat_num_aux);


        printf("\n\nSelecione outro ficheiro (#7 para sair): ");
    }

    return 0;
}
