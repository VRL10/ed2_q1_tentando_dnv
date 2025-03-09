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
    int i = 1;
    while (i <= QUANTIDADECURSOS){
        int codigo_curso = rand() % QUANTIDADECURSOS + 1;
        clock_t inicio = clock();
        if(cadastrar_curso(raiz,i,10,"DIREITO") == 1)
            i++;
        clock_t fim = clock();

        tempos_insercao_aleatorio[i - 1] = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    }
}

// -----------------------------------  POVOAMENTO DISCIPLINAS -------------------------------
int codigo_disciplina_global_crescente = 1;
void povoamento_crescente_disciplinas(Arv_curso **raiz, Arv_curso **curso){
    if (*raiz != NULL){
        Arv_disciplina* disciplina = (Arv_disciplina*) malloc(sizeof(Arv_disciplina));
        strcpy(disciplina->nome, "Direitos Trabalhistas I");
        disciplina->carga_horaria = 60;
        disciplina->periodo_disciplina = 3;
        disciplina->cod_disciplina = codigo_disciplina_global_crescente++;

        cadastrar_disciplina(curso, disciplina->cod_disciplina, disciplina->periodo_disciplina, disciplina->carga_horaria, disciplina->nome,(*curso)->cod_curso);

        povoamento_crescente_disciplinas(&(*raiz)->esq, curso);
        povoamento_crescente_disciplinas(&(*raiz)->dir, curso);
    }
}

int codigo_disciplina_global_decrescente = QUANTIDADEDISCIPLINAS;
void povoamento_decrescente_disciplinas(Arv_curso **raiz, Arv_curso **curso){
    if(*raiz !=NULL){
        Arv_disciplina* disciplina = (Arv_disciplina*) malloc(sizeof(Arv_disciplina));
        strcpy(disciplina->nome, "Direitos Trabalhistas I");
        disciplina->carga_horaria = 60;
        disciplina->periodo_disciplina = 3;
        disciplina->cod_disciplina = codigo_disciplina_global_decrescente--;

        cadastrar_disciplina(curso, disciplina->cod_disciplina, disciplina->periodo_disciplina, disciplina->carga_horaria, disciplina->nome,(*curso)->cod_curso);

        povoamento_decrescente_disciplinas(&(*raiz)->esq, curso);
        povoamento_decrescente_disciplinas(&(*raiz)->dir, curso);
    }
}

void povoamento_disciplinas_aleatorio(Arv_curso **raiz, Arv_curso **curso){
    if (*raiz != NULL){
        srand(time(NULL));

        Arv_disciplina* disciplina = (Arv_disciplina*) malloc(sizeof(Arv_disciplina));
        strcpy(disciplina->nome, "Direitos Trabalhistas I");
        disciplina->carga_horaria = (rand() % 5 + 2) * 15;
        disciplina->periodo_disciplina = rand() % (*raiz)->qtd_periodos + 1;
        disciplina->cod_disciplina = (rand() % QUANTIDADEDISCIPLINAS) + 1;

        cadastrar_disciplina(curso, disciplina->cod_disciplina, disciplina->periodo_disciplina, disciplina->carga_horaria, disciplina->nome, (*curso)->cod_curso);

        povoamento_disciplinas_aleatorio(&(*raiz)->esq, curso);
        povoamento_disciplinas_aleatorio(&(*raiz)->dir, curso);
    }
}

// -----------------------------------  POVOAMENTO ALUNOS --------------------------------
void povoamento_crescente_alunos(Lista_alunos **aluno){
    char *nomes[5] = {"Daniel", "Rodrigues", "Cristina", "Sousa", "Juliana"};
    for (int i = 1; i <= QUANTIDADEALUNOS; i++){
        int cod_matricula = i;
        int cod_curso = i;
        char nome = nomes[range() % 5];
    
        cadastrar_aluno(*aluno, nome, cod_matricula, cod_curso);
    }
}

void povoamento_decrescente_alunos(Lista_alunos **aluno){
    char *nomes[5] = {"Daniel", "Rodrigues", "Cristina", "Sousa", "Juliana"};
    for (int i = 1; i <= QUANTIDADEALUNOS; i++){
        int cod_matricula = i;
        int cod_curso = i;
        char nome = nomes[range() % 5];
    
        cadastrar_aluno(*aluno, nome, cod_matricula, cod_curso);
    }
}