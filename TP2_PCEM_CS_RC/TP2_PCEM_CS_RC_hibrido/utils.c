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


#include "algoritmo.h"
#include "utils.h"


void selectInfo(info *sx, int n, int iter) {
    int opcao;

    sx->capacity = n;
    sx->numGenes = iter;

    printf("\nSelecione as opcoes da populacao: \n\n");
    printf("Popsize: #1 - 10 / #2 - 50 / #3 - 100 / #4 - 150 \n");
    while (1) {
        int check = 0;
        printf("Opcao:  ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1 :
                sx->popsize = 10;
                sx->numGenerations = 2500;
                check = 1;
                break;
            case 2 :
                sx->popsize = 50;
                sx->numGenerations = 500;
                check = 1;
                break;
            case 3 :
                sx->popsize = 100;
                sx->numGenerations = 200;
                check = 1;
                break;
            case 4 :
                sx->popsize = 150;
                sx->numGenerations = 50;
                check = 1;
                break;
            default:
                printf("Opcao errada!\n");
                break;
        }
        if (check == 1)
            break;
    }

    printf("\nPm: #1 - 0.0 / #2 - 0.001 / #3 - 0.01 / #4 - 0.05 \n");
    while (1) {
        int check = 0;
        printf("Opcao:  ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1 :
                sx->pm = 0.0001;
                check = 1;
                break;
            case 2 :
                sx->pm = 0.001;
                check = 1;
                break;
            case 3 :
                sx->pm = 0.01;
                check = 1;
                break;
            case 4 :
                sx->pm = 0.05;
                check = 1;
                break;
            default:
                printf("Opcao errada!\n");
                break;
        }
        if (check == 1)
            break;
    }

    printf("\nPr: #1 - 0.3 / #2 - 0.5 / #3 - 0.7 \n");
    while (1) {
        int check = 0;
        printf("Opcao:  ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1 :
                sx->pr = 0.3;
                check = 1;
                break;
            case 2 :
                sx->pr = 0.5;
                check = 1;
                break;
            case 3 :
                sx->pr = 0.7;
                check = 1;
                break;
            default:
                printf("Opcao errada!\n");
                break;
        }
        if (check == 1)
            break;
    }


}
// Leitura dos parâmetros e dos dados do problema
// Parâmetros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Parâmetros de saída: Devolve a estrutura com os parâmetros

info init_data(char *nome) {
    FILE *f;
    int n, iter;
    char aux_inicio;
    info sx;


    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    // Numero de iteracoes
    while (fscanf(f, "%c", &aux_inicio) != EOF) {
        if (aux_inicio == 'p') {
            if (fscanf(f, " edge %d %d", &n, &iter))
                break;
        }
    }
    selectInfo(&sx, n, iter);


    sx.tsize = 2;
    sx.ro = 0.0; //avalicao de penalização
/*
    // Leitura dos parâmetros do problema
    sx.popsize = 10;
    sx.pm = 0.01;
    sx.pr = 0.1;
    sx.numGenerations = 2500;
    sx.numGenes = *iter;
    sx.capacity = *n;
*/


    /*
    if (sx.numGenes > MAX_OBJ) {
        printf("Number of itens is superior to MAX_OBJ\n");
        // exit(1);
    }
*/
    fclose(f);
    return sx;
}


int *read_data(char *nome, int *mat, int *mat_num_aux, int *n, int *iter, int *opcaoBestSol) {
    FILE *f;
    int *p, *q, *p_orig, *q_orig;
    int i, j, k, x, h, aux1 = 0, aux2 = 0, iter1, n1, count = 1, count2 = 1;

    int arrayAux1[2];
    int arrayAux2[2];
    char aux_inicio[100];
    char str1[10];


    mat_num_aux = malloc(sizeof(int) * (*iter) * 2 + 1);
    if (!mat_num_aux) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }


    q_orig = mat_num_aux;

    // Preenchimento da matriz
    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }
    while (fscanf(f, "%[^\n] ", aux_inicio) != EOF && aux_inicio[0] != 'p') {}

    i = 0;
    while (fscanf(f, "%[^\n] ", aux_inicio) != EOF && i < *iter * 2) {
        if (aux_inicio[0] == 'e') {
            sscanf(aux_inicio, "%*c %d %d", &aux1, &aux2);
            *(mat_num_aux + i) = aux1;
            *(mat_num_aux + 1 + i) = aux2;
            if (*opcaoBestSol == 2) {
                printf("\t%d - %d\n", *(mat_num_aux + i), *(mat_num_aux + 1 + i));
            }
            i += 2;
        }
    }
    mat_num_aux = q_orig; //reinicializa ponteiro array
    printf("\n\tA importar dados ");
    if (*opcaoBestSol == 2) {

        for (i = 2; i <= ((*iter) * 2); i = i + 2) {

            printf("\t%d -- %d\n", *(mat_num_aux + i), *(mat_num_aux + i + 1));
        }
        printf("\n\tArray \n");
    }

    mat_num_aux = q_orig; //reinicializa ponteiro array

    x = 1;
    int resultado[*n][*n];

    for (i = 2; i <= ((*iter) * 2); i = i + 2) {
        arrayAux1[0] = *(mat_num_aux + i);
        arrayAux1[1] = *(mat_num_aux + i + 1);


        for (j = 0; j < *n; j++) {

            if (*opcaoBestSol == 1) {
                if (i == ((j - 1) * (*iter - 1) / 10)) {
                    printf("»");
                }
            }
            arrayAux2[0] = j + 1;
            for (k = 0; k < *n; k++) {
                arrayAux2[1] = k + 1;

                if (arrayAux1[0] == arrayAux2[0] && arrayAux1[1] == arrayAux2[1]) {
                    if (i >= 2 && resultado[j][k] == 0) {
                        resultado[j][k] = 1;
                    } else {
                        if (arrayAux1[0] == arrayAux1[1]) {
                            resultado[j][k] = 1;
                        } else {
                            resultado[j][k] = 0;
                            resultado[k][j] = 0;
                        }
                    }
                } else {
                    if (i >= 2 && resultado[j][k] == 0) {
                        continue;
                    } else if (i >= 2 && resultado[j][k] == 1) {
                        resultado[j][k] = 1;
                    } else {
                        resultado[j][k] = 1;
                    }
                }
            }
        }
    }

    printf("\n");
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            *(mat + i + ((*n) * j)) = resultado[i][j];

            if (j < i && *opcaoBestSol == 2) {
                printf(" [%d]", resultado[i][j]);

            }

        }
        if (j < i && *opcaoBestSol == 2) {
            printf("\n");
        }
        //printf("\n");
    }


    printf("\n");

    // Devolve a estrutura com os parâmetros
    return mat_num_aux;
}


// Criacao da populacao inicial. O vector e alocado dinamicamente
// Parâmetro de entrada: Estrutura com parâmetros do problema
// Parâmetro de saída: Preenche da estrutura da população apenas o vector binário com os elementos que estão dentro ou fora da solução
pchrom init_pop(info d, pchrom indiv, int *sol, int *mat, int *arr_rand_p1, int n) {
    int j, i, p, k, m, p1, y, valid = 0, *sol_aux, *arr_rand_p1_aux, invalids = 1, flip2;

    sol_aux = sol;

    for (m = 0; m < d.popsize; m++) {
        sol = sol_aux;
        arr_rand_p1_aux = arr_rand_p1;
        init_rand();
        for (k = 0; k < d.capacity; k++) {
            reinicializa_sol(sol, d.capacity, d.numGenes);//reinicializamos a solução --> tudo a -1


            for (i = 0; i < n; i++) {
                *(arr_rand_p1 + i) = i;
            } //array para random para ver se numero ja saiu no random x
            for (i = 0; i < d.capacity; i++) {
                *(sol + i) = flip();
                alter_to_valid(sol, sol_aux, mat, i, n, d.numGenes);
            } //array para random para ver se numero ja saiu no random x


            for (i = 0; i < n; i++) {  //ele preenche cada espaço da solução
                p1 = check_random((arr_rand_p1_aux), n); //verfica random
                if (*(sol + p1) == 1) {
                    *(sol + p1) = 1;
                    indiv[m].p[k] = 1;
                    valid = 2;
                } else {
                    *(sol + p1) = 0;
                    valid = alter_to_valid(sol, sol_aux, mat, p1, n, d.numGenes); //verifica se válido
                    if (valid == 1) {
                        indiv[m].p[k] = 0;
                    }
                }
            }


        }
    }
    //free(arr_rand_p1);

    return indiv;
}

// Actualiza a melhor solução encontrada
// Parâmetro de entrada: populacao actual (pop), estrutura com parâmetros (d) e a melhor solucao encontrada até a geraçãoo imediatamente anterior (best)
// Parâmetro de saída: a melhor solucao encontrada até a geração actual
chrom get_best(pchrom pop, info d, chrom best) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        if (best.fitness < pop[i].fitness)
            best = pop[i];
    }
    return best;
}

// Escreve uma solução na consola
// Parâmetro de entrada: populacao actual (pop) e estrutura com parâmetros (d)
void write_best(chrom x, info d) {
    int i;


    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i = 0; i < d.capacity; i++)
        printf("%d", x.p[i]);

    putchar('\n');
}

void reinicializa_sol(int *sol, int v, int num_iter) {
    int i;
    for (i = 0; i < v; i++) {
        // if (sol[i] != 0)
        *(sol + i) = -1;
    }  //reinicializamos a solução --> tudo a -1

}

int check_random(int *arr_rand_p1, int n) {
    int j, p1, v_mat = n;
    int fim_p1 = 1, cont = 0, a_rand_check_p1 = 0;

    do {
        p1 = random_l_h(0, n - 1);
        cont = 0;
        v_mat = n;

        if (*(arr_rand_p1 + p1) !=
            -1) { // se o numero ja foi ou nao utilizado no random faz random ate 6 valores diferentes
            a_rand_check_p1 = 0; //sair do ciclo
            *(arr_rand_p1 + p1) = -1; // colocar como numero ja tirado
        } else { // se for - 1 -----> valor ja repetido anteriormente
            a_rand_check_p1 = 1; // volta a repetir o ciclo

            for (j = 0; j < n; j++) {
                if (*(arr_rand_p1 + j) == -1) {
                    cont++;
                }
                if (cont == n) {
                    fim_p1 = 0;
                    a_rand_check_p1 = 0;
                }
            } //condição de fim - quando array toda percorrida
        }
    } while (a_rand_check_p1 == 1 && fim_p1 == 1); //lança randoms de numeros diferentes X

    if (fim_p1 == 0) {
        p1 = -1;
    }
    return p1;
}



int alter_to_valid(int *a, int *b, int *mat, int randomn, int vert, int num_iter) {
    int i, v_mat = vert, valid = 0;

    if (b[randomn] != 1) {

        for (i = 0; i < vert; i++) {
            if (b[i] == 1) {
                if (i == randomn) {
                    break;
                }
                if (*(mat + randomn + (vert * i)) == 0) { // verifica numeros impossiveis
                    v_mat--;
                    break;
                }
            }
        } //verifica se há numero incompativeis

        if (v_mat == vert) { //se encontrou um impossivel não altera  e altera se for igual aos vertices
            b[randomn] = 1;
            valid = 1;
        }
        return 1;
    } else {
        return 0;
    }

}

int check_valid(int *a, int *mat, int *mat_num_aux, int vert, int num_iter) {
    int i, j = 0, verifica0, verifica = 0;

    for (i = 0; i < vert; i++) {
        //
        if (*(a + i) == 1) {

            for (j; j < num_iter * 2; j += 2) {

                if (*(a + (*(mat + (j) + (0)) - 1))  > i + 1) {
                    break;
                }
                if (*(a + (*(mat + (j) + (0)) - 1)) == i + 1) {

                    if (*(a + (*(mat + (j) + (1)) - 1)) == 1) {

                        verifica = random_l_h(0, 1);
                        if (verifica == 1) {
                            *(a + (*(mat + (j) + (0)) - 1)) = 0;
                        } else {
                            *(a + (*(mat + (j) + (1)) - 1)) = 0;

                        }
                    }
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int check_valid2(int *a, int *mat, int *mat_num_aux, int vert, int num_iter) {
    int i, k = 0, l = vert, v_mat = vert, p1, cont, verifica, valid = 0;

     do {
            for (i = 0; i < vert; i++) {
            for (k; k < 2; k++) {

                if (*(mat_num_aux + (i * 2) + (k)) == i) {
                    for (l; l > 2; l -= 2) {
                        if (a[l] == 1 && *(mat_num_aux + (l * 2) + (k + 1)) == l) {
                            //printf("\t%d\n", *(mat_num_aux + (l*2) + (k+1)));
                            verifica = random_l_h(0, 1);
                            if (verifica == 1) {
                                a[i + 1] = 0; // desactiva o numero
                            } else {
                                a[i] = 0; // desactiva o numero
                            }
                        } // verifica se o valor a seguir com ligaçao anterior está presente e a válido na solução
                    }  //percorre a solução

                } //verfica numero ncom ligação se igual ao i
            }   // percorre k de cima para baixo
            } //salta i de 2 em 2


    }while (a[i] == 1); // se o valor for valido na solução

    return 1;
}


int liberta_tudo(int *sol, int *mat, float *mbf, info d, chrom pop, int n) {
    int i, j;
    *mbf = 0;

    reinicializa_sol(sol, n, d.numGenes);//reinicializamos a solução --> tudo a -1
    reinicializa_sol(mat, n * n, d.numGenes);//reinicializamos a solução --> tudo a -1

    for (i = 0; i < d.popsize; i++) {
        for (j = 0; j < d.capacity; j++) {
            reinicializa_sol(((pop.p) + i), n, d.numGenes);//reinicializamos a solução --> tudo a -1

        }
    }

    free(mat);
    // free(sol);


    return 0;

}

// Inicializa o gerador de numeros aleatorios
void init_rand() {
    srand((unsigned) time(NULL));
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip() {
    if ((((float) rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01() {
    return ((float) rand()) / RAND_MAX;
}
