#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore_disciplina Arv_disciplina;
typedef struct arvore_curso Arv_curso;
typedef struct arvore_notas Arv_notas;
typedef struct arvore_matricula Arv_matricula;
typedef struct lista_alunos Lista_alunos;

typedef struct lista_alunos {
    int cod_matricula,cod_curso;
    char nome[50];
    Arv_notas *notas;
    Arv_matricula *matriculas;
    Lista_alunos *prox;
}Lista_alunos;

typedef struct arvore_curso {
    int cod_curso,qtd_periodos;
    char nome[50];
    Arv_disciplina *disciplinas;
    Arv_curso *esq, *dir;
}Arv_curso;

typedef struct arvore_disciplina {
    int cod_disciplina,periodo_disciplina,carga_horaria;
    char nome[50];
    Arv_disciplina *esq, *dir;
}Arv_disciplina;

typedef struct arvore_notas {
    int cod_disciplina,semestre_cursado;
    float nota_final;
    Arv_notas *esq, *dir;
}Arv_notas;

typedef struct arvore_matricula {
    int cod_disciplina;
    Arv_matricula *esq, *dir;
}Arv_matricula;


int cadastrar_aluno(Lista_alunos **aluno, char nome[50], int matricula, int cod_curso);

int cadastrar_curso(Arv_curso **curso, int cod_curso, int qtd_peridos, char nome[50]);
void validar_carga_horaria(int *validar, int carga_horaria);
void validar_periodo(Arv_curso *curso,int periodo_disciplina, int *validar);
void inserir_disciplina(Arv_disciplina **arv_disciplina_curso, Arv_disciplina *novo, int *inseriu);
int cadastrar_disciplina(Arv_curso **curso, int cod_disciplina, int periodo_disciplina,int carga_horaria, char nome[50], int cod_curso);
void gerar_codigo_disciplina(int *cod_disciplina);
void inserir_matricula(Arv_matricula **matricula, Arv_matricula *novo, int *resultado);
int cadastrar_matricula(Lista_alunos **aluno, int cod_disciplina, int cod_matricula);
void remove_disciplina_da_arvore_matricula(Arv_matricula **matricula, int cod_disciplina);
int disciplina_existe_na_matricula(Arv_matricula *matricula, int cod_disciplina);
void inserir_nota(Arv_notas **notas, Arv_notas *novo, int *resultado, int cod_disciplina);
int cadastrar_notas(Lista_alunos **aluno, float nota_final, int cod_disciplina, int cod_matricula, int semestre_cursado);
void aluno_por_curso(Lista_alunos *aluno, int cod_curso);
void todos_cursos_do_campus(Arv_curso *curso);
void exibir_disciplinas_do_curso(Arv_disciplina *disciplina);
void encontrar_curso_desejado(Arv_curso *curso, int codigo_curso);
void mostrar_disciplinas_periodo(Arv_disciplina *disciplina, int periodo);
void mostrar_todas_disciplinas_periodo_de_um_curso(Arv_curso *curso, int codigo_curso, int periodo);
void exibir_disciplinas_aluno_matriculado_recursiva(Arv_matricula *matriculas, Arv_curso *curso);
void exibir_disciplinas_aluno_matriculado(Lista_alunos *aluno, Arv_curso *curso);
void exibir_disciplinas_por_aluno(Lista_alunos *alunos, Arv_curso *curso, int matricula);
void buscar_notas_pertence_periodo(Arv_notas *notas, Arv_disciplina *disciplina, int periodo);
void exibir_todas_notas_disciplinas_determinado_periodo_aluno(Lista_alunos *aluno, Arv_disciplina *disciplina, int periodo, int matricula);
void exibir_nota_disciplina_aluno(Lista_alunos *aluno, Arv_curso *curso, int codigo_disciplina, int codigo_matricula);
void remover_disciplina_de_um_curso_sem_aluno_matriculado(Lista_alunos *aluno, Arv_curso *curso, int codigo_curso, int codigo_disciplina);
int remover_disciplina(Arv_disciplina **disciplina_remover, int codigo_disciplina);
void remover_disciplina_da_arvore_de_matricula_aluno(Arv_matricula **matriculas, int codigo_disciplina);
int remover_disciplina_arvore_matricula(Arv_matricula **matricula, int codigo_disciplina);
void disciplinas_cursadas(Arv_matricula *matriculas, Arv_disciplina *disciplinas,Arv_notas *notas, int periodo);
void aluno_curso_esta_matriculado(Lista_alunos *aluno, Arv_curso *curso,int periodo);
void mostrar_historico_aluno(Lista_alunos *aluno, Arv_curso *curso);


// funções auxiliares
void converternome(char *nome);
Arv_disciplina* buscar_disciplina(Arv_disciplina *disciplina, int codigo_disciplina);
Arv_curso* buscar_curso(Arv_curso *curso, int codigo_curso);
void exibir_disciplina(Arv_disciplina *disciplina);
int achar_nota_final(Arv_notas *notas, int codigo_disciplina);
int aluno_esta_cadastrado_na_disciplina(Lista_alunos *aluno, Arv_disciplina *disciplina);
int eh_folha_disciplina(Arv_disciplina *disciplina);
int eh_folha_matricula(Arv_matricula *matricula);
int so_um_filho_disciplina(Arv_disciplina *disciplina);
int so_um_filho_matricula(Arv_matricula *matricula);
float buscar_nota_atual(Arv_notas *notas, Arv_disciplina *disciplina);

#endif