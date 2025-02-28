#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <time.h>
#include <unistd.h>

#define QUANTIDADECURSOS 2000
#define CODIGOCURSO 2000
#define QUANTIDADEDISCIPLINAS 2000
#define QUANTIDADEALUNOS 2000
#define QUANTIDADENOTAS 2000

double tempos_insercao_crescente[QUANTIDADECURSOS];
double tempos_insercao_decrescente[QUANTIDADECURSOS];
double tempos_insercao_aleatorio[QUANTIDADECURSOS];

void free_arvore_cursos(Arv_curso *raiz)
{
    if (raiz != NULL)
    {
        free_arvore_cursos(raiz->esq);
        free_arvore_cursos(raiz->dir);
        free(raiz);
    }
}

void free_lista_alunos(Lista_alunos *alunos)
{
    Lista_alunos *temp;
    while (alunos != NULL)
    {
        temp = alunos;
        alunos = alunos->prox;
        free(temp);
    }
}
// --------------------------------------  POVOAMENTO CURSOS ---------------------------------
void povoamento_crescente_cursos(Arv_curso **raiz){
    *raiz = NULL;
    for (int i = 1; i <= QUANTIDADECURSOS; i++){
        clock_t inicio = clock();
        cadastrar_curso(raiz,i,10,"DIREITO");
        clock_t fim = clock();

        // tranforma em segundos e depois multiplica por 100 para tranformar em milesegundos
        tempos_insercao_crescente[i-1] = ((double)(inicio - fim)/CLOCKS_PER_SEC) * 1000;
    }   
}

void povoamento_decrescente_cursos(Arv_curso **raiz){
    *raiz = NULL;
    for (int i = QUANTIDADECURSOS; i <= 0; i++){
        clock_t inicio = clock();
        cadastrar_curso(raiz,i,10,"DIREITO");
        clock_t fim = clock();

        tempos_insercao_crescente[QUANTIDADECURSOS - i] = ((double)(inicio - fim)/CLOCKS_PER_SEC) * 1000;
    }
}

void povoamento_aleatorio_cursos(Arv_curso **raiz){
    *raiz = NULL;
    
}