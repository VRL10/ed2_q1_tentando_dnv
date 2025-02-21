#include "arvore.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void converter_nome(char *nome) {
    int i = 0;
    while (nome[i] != '\0'){
        nome[i] = toupper(nome[i]);
        i++;
    }
}

/*  I - Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que já tenha sido cadastrado na árvore de cursos.  */

int cadastrar_aluno(Lista_alunos **aluno, char nome[50], int matricula, int cod_curso) {
    converter_nome(nome); // Converte o nome para maiúsculas

    int resultado = 1;

    // Verifica se já existe um aluno com a mesma matrícula
    Lista_alunos *atual = *aluno;
    while (atual != NULL) {
        if (atual->cod_matricula == matricula) {
            printf("Aluno já cadastrado.\n");
            resultado = 0;
            break;
        }
        atual = atual->prox;
    }

    // Se o aluno não foi encontrado, insere o novo aluno
    if (resultado == 1) {
        Lista_alunos *novo = (Lista_alunos *)malloc(sizeof(Lista_alunos));
        if (novo == NULL) {
            printf("Erro na alocação!\n");
            resultado = -1;
        } else {
            novo->cod_curso = cod_curso;
            novo->cod_matricula = matricula;
            strcpy(novo->nome, nome);
            novo->prox = NULL;

            // Insere na posição correta, mantendo a lista ordenada
            if (*aluno == NULL || strcmp((*aluno)->nome, nome) > 0) {
                novo->prox = *aluno;
                *aluno = novo;
            } else {
                atual = *aluno;
                while (atual->prox != NULL && strcmp(atual->prox->nome, nome) < 0) {
                    atual = atual->prox;
                }
                novo->prox = atual->prox;
                atual->prox = novo;
            }
        }
    }

    return resultado;
}

/* II - Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso */

int cadastrar_curso(Arv_curso **curso, int cod_curso, int qtd_peridos, char nome[50]){
    int resultado = 0;
    if (*curso == NULL){
        Arv_curso *novo = (Arv_curso*)malloc(sizeof(Arv_curso));
        if(novo == NULL){
            printf("Erro na alocação para o novo curso!");
            resultado = -1;
        }else{
            novo->cod_curso = cod_curso;
            novo->qtd_periodos = qtd_peridos;
            strcpy(novo->nome, nome);
            novo->esq = NULL;
            novo->dir = NULL;
            *curso = novo;
            resultado = 1;
        }
    }else{
        if ((*curso)->cod_curso == cod_curso)
            printf("Um curso já foi cadastrado com esse codigo!");
        else if ((*curso)->cod_curso > cod_curso)
            resultado = cadastrar_curso(&(*curso)->esq,cod_curso,qtd_peridos,nome);
        else
            resultado = cadastrar_curso(&(*curso)->dir,cod_curso,qtd_peridos,nome);
    }
    return resultado;
}

/* III - Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, uma disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90 */

void validar_carga_horaria(int *validar, int carga_horaria){
    if(carga_horaria / 15 == 0 && (carga_horaria >= 15 && carga_horaria <= 90))
        *validar = 1;
}

void validar_periodo(Arv_curso *curso, int periodo_disciplina, int *validar){
    if(periodo_disciplina >= 1 && curso->qtd_periodos >= periodo_disciplina)
        *validar = 1;
}

void inserir_disciplina(Arv_disciplina **arv_disciplina_curso, Arv_disciplina *novo, int *inseriu){
    if((*arv_disciplina_curso) == NULL){
        novo->dir = NULL;
        novo->esq = NULL;
        *arv_disciplina_curso = novo;
        *inseriu = 1;
    }else{
        if ((*arv_disciplina_curso)->cod_disciplina > novo->cod_disciplina)
            inserir_disciplina(&(*arv_disciplina_curso)->esq, novo, inseriu);
        else
            inserir_disciplina(&(*arv_disciplina_curso)->dir, novo, inseriu);
    }
}

int cadastrar_disciplina(Arv_curso **curso, int cod_disciplina, int periodo_disciplina,int carga_horaria, char nome[50], int cod_curso){
    int resultado = 0, validar_CH = 0, validar_PD = 0;
    validar_carga_horaria(&validar_CH, carga_horaria);
    validar_periodo(*curso, periodo_disciplina, &validar_PD);

    if(validar_CH == 0 || validar_PD == 0){
        if(validar_CH == 0)
            printf("ERRO! Verifique se a carga horária foi digitado corretamente!");
        if(validar_PD == 0)
            printf("ERRO! Verifique se o período da disciplina foi digitado corretamente!");
    }
    else{
        if(*curso == NULL)
            printf("O curso não existe!");
        else if((*curso)->cod_curso == cod_curso){
            Arv_disciplina *novo = (Arv_disciplina*)malloc(sizeof(Arv_disciplina));
            if(novo == NULL){
                printf("Erro na alocação dinâmica!");
                return -1;
            }
            novo->carga_horaria = carga_horaria;
            novo->cod_disciplina = cod_disciplina;
            novo->periodo_disciplina = periodo_disciplina;
            strcpy(novo->nome, nome);
            inserir_disciplina(&(*curso)->disciplinas, novo, &resultado);
        }else if((*curso)->cod_curso > cod_curso)
            resultado = cadastrar_disciplina(&(*curso)->esq, cod_disciplina, periodo_disciplina, carga_horaria, nome, cod_curso);
        else
            resultado = cadastrar_disciplina(&(*curso)->dir, cod_disciplina, periodo_disciplina, carga_horaria, nome, cod_curso);
    }
    return resultado;
}

int contador_cod_disciplina = 0;

void gerar_codigo_disciplina(int *cod_disciplina){
    *cod_disciplina = contador_cod_disciplina;
    contador_cod_disciplina++;
}

/* IV - Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno.  */

void inserir_matricula(Arv_matricula **matricula, Arv_matricula *novo, int *resultado){
    if(*matricula == NULL){
        novo->dir = NULL;
        novo->esq = NULL;
        *matricula = novo;
        *resultado = 1;
    }else{
        if((*matricula)->cod_disciplina > novo->cod_disciplina)
            inserir_matricula(&(*matricula)->esq, novo, resultado);
        else if((*matricula)->cod_disciplina < novo->cod_disciplina)
            inserir_matricula(&(*matricula)->dir, novo, resultado);
        else
            printf("Essa matrícula já foi cadastrada!");
    }
}

int cadastrar_matricula(Lista_alunos **aluno, int cod_disciplina, int cod_matricula){
    int resultado = 0;
    if (*aluno != NULL){
        if ((*aluno)->cod_matricula == cod_matricula){
            Arv_matricula *novo = (Arv_matricula*)malloc(sizeof(Arv_matricula));
            novo->cod_disciplina = cod_disciplina;
            inserir_matricula(&(*aluno)->matriculas, novo, &resultado);
        }
        else
            resultado = cadastrar_matricula(&(*aluno)->prox, cod_disciplina, cod_matricula);
    }
    return resultado;
}

/* V - Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas. */
void remove_disciplina_da_arvore_matricula(Arv_matricula **matricula, int cod_disciplina){
    if (*matricula == NULL){
        printf("Não foi possível remover a disciplina");
        return;
    }
    if ((*matricula)->cod_disciplina == cod_disciplina){
        if ((*matricula)->esq == NULL && (*matricula)->dir == NULL){
            free((*matricula));
            *matricula = NULL;
        }else if((*matricula)->esq == NULL || (*matricula)->dir == NULL){
            Arv_matricula *aux;
            if ((*matricula)->esq == NULL){
                aux = (*matricula)->dir;
                free((*matricula));
                *matricula = aux;
            }else{
                aux = (*matricula)->esq;
                free((*matricula));
                *matricula = aux;
            }
        }else{
            Arv_matricula *aux = (*matricula)->dir;
            while(aux->esq != NULL)
                aux = aux->esq;
            (*matricula)->cod_disciplina = aux->cod_disciplina;
            remove_disciplina_da_arvore_matricula(&(*matricula)->dir, aux->cod_disciplina);
        }
    }else {
        if ((*matricula)->cod_disciplina > cod_disciplina)
            remove_disciplina_da_arvore_matricula(&(*matricula)->esq, cod_disciplina);
        else if ((*matricula)->cod_disciplina < cod_disciplina)
            remove_disciplina_da_arvore_matricula(&(*matricula)->dir, cod_disciplina);
    }
}

int disciplina_existe_na_matricula(Arv_matricula *matricula, int cod_disciplina){
    int existe = 0;
    if(matricula != NULL){
        if(matricula->cod_disciplina == cod_disciplina)
            existe = 1;
        else if(matricula->cod_disciplina > cod_disciplina)
            existe = disciplina_existe_na_matricula(matricula->esq, cod_disciplina);
        else
            existe = disciplina_existe_na_matricula(matricula->dir, cod_disciplina);
    }
    return existe;
}

void inserir_nota(Arv_notas **notas, Arv_notas *novo, int *resultado, int cod_disciplina){
    if (*notas == NULL){
        novo->dir = NULL;
        novo->esq = NULL;
        *notas = novo;
        *resultado = 1;
    }else{
        if((*notas)->cod_disciplina > cod_disciplina)
            inserir_nota(&(*notas)->esq, novo, resultado, cod_disciplina);
        else if((*notas)->cod_disciplina < cod_disciplina)
            inserir_nota(&(*notas)->dir, novo, resultado, cod_disciplina);
        else
            printf("Essa nota já foi cadastrada!");
    }
}

int cadastrar_notas(Lista_alunos **aluno, float nota_final, int cod_disciplina, int cod_matricula, int semestre_cursado){
    int resultado = 0;
    if(*aluno != NULL){
        int existe = disciplina_existe_na_matricula((*aluno)->matriculas, cod_disciplina);
        if (existe == 1){
            Arv_notas *novo = (Arv_notas*)malloc(sizeof(Arv_notas));
            novo->cod_disciplina = cod_disciplina;
            novo->nota_final = nota_final;
            novo->semestre_cursado = semestre_cursado;
            inserir_nota(&(*aluno)->notas, novo, &resultado, cod_disciplina);
            remove_disciplina_da_arvore_matricula(&(*aluno)->matriculas, cod_disciplina);
        }else
            resultado = cadastrar_notas(&(*aluno)->prox, nota_final, cod_disciplina, cod_matricula, semestre_cursado);
    }
    return resultado;
}

// VI -  Mostrar todos os alunos de um determinado curso.
void aluno_por_curso(Lista_alunos *aluno, int cod_curso){
    printf("\nAlunos que cursa o curso:");
    while (aluno != NULL){
        if (aluno->cod_curso == cod_curso)
            printf("\n\nNome: %s\nID da Matricula: %d",aluno->nome,aluno->cod_matricula);
        aluno = aluno->prox;
    }
}

// VII - Mostrar todos os cursos do Campus
void todos_cursos_do_campus(Arv_curso *curso){
    printf("\nTodos os cursos do Campus");
    if(curso != NULL){
        printf("\n\nNome: %s\nID: %d",curso->nome,curso->cod_curso);
        todos_cursos_do_campus(curso->esq);
        todos_cursos_do_campus(curso->dir);
    }
}

// VIII - Mostrar todas as disciplinas de um determinado curso.
void exibir_disciplinas_do_curso(Arv_disciplina *disciplina){
    printf("\nTodas as disciplinas do curso");
    if(disciplina != NULL){
        printf("\n\nNome: %s\nID da disciplina: %d\nPeriodo: %d\nCarga Horaria: %d\n-------------------------------\n",disciplina->nome,disciplina->cod_disciplina,disciplina->periodo_disciplina,disciplina->carga_horaria);
        exibir_disciplinas_do_curso(disciplina->esq);
        exibir_disciplinas_do_curso(disciplina->dir);
    }
}

void encontrar_curso_desejado(Arv_curso *curso, int codigo_curso){
    if (curso != NULL){
        if (curso->cod_curso == codigo_curso)
            exibir_disciplinas_do_curso(curso->disciplinas);
        if (curso->cod_curso > codigo_curso)
            encontrar_curso_desejado(curso->esq, codigo_curso);
        else
            encontrar_curso_desejado(curso->dir, codigo_curso);
    }
}

// IX - Mostrar todas as disciplinas de um determinado período de um curso.
void mostrar_disciplinas_periodo(Arv_disciplina *disciplina, int periodo){
    if(disciplina != NULL){
        if (disciplina->periodo_disciplina == periodo) 
            printf("\n\nNome: %s\nID da disciplina: %d\nPeriodo: %d\nCarga Horaria: %d\n-------------------------------\n",disciplina->nome,disciplina->cod_disciplina,disciplina->periodo_disciplina,disciplina->carga_horaria);
        mostrar_disciplinas_periodo(disciplina->esq, periodo);
        mostrar_disciplinas_periodo(disciplina->dir, periodo);
    }
}

void mostrar_todas_disciplinas_periodo_de_um_curso(Arv_curso *curso, int codigo_curso, int periodo){
    if (curso != NULL){
        if(curso->cod_curso == codigo_curso)
            mostrar_disciplinas_periodo(curso->disciplinas,periodo);
        else if(curso->cod_curso > codigo_curso)
            mostrar_todas_disciplinas_periodo_de_um_curso(curso->esq,codigo_curso,periodo);
        else
            mostrar_todas_disciplinas_periodo_de_um_curso(curso->dir,codigo_curso,periodo);
    }
}

// X - Mostrar todas as disciplinas que um determinado aluno está matriculado
void exibir_disciplinas_aluno_matriculado_recursiva(Arv_matricula *matriculas, Arv_curso *curso){
    if (matriculas != NULL) {
            Arv_disciplina *disciplina = buscar_disciplina(curso->disciplinas, matriculas->cod_disciplina);
            if (disciplina != NULL) {
                exibir_disciplina(disciplina);
            }
        }

        exibir_disciplinas_aluno_matriculado_recursiva(matriculas->esq, curso);
        exibir_disciplinas_aluno_matriculado_recursiva(matriculas->dir, curso);
}


void exibir_disciplinas_aluno_matriculado(Lista_alunos *aluno, Arv_curso *curso) {
    if (aluno != NULL && aluno->matriculas != NULL && curso != NULL) {
        exibir_disciplinas_aluno_matriculado_recursiva(aluno->matriculas, curso);
        if(curso->esq != NULL)
            exibir_disciplinas_aluno_matriculado(aluno, curso->esq);
        if (curso->dir != NULL)
            exibir_disciplinas_aluno_matriculado(aluno, curso->dir);
    }
}

void exibir_disciplinas_por_aluno(Lista_alunos *alunos, Arv_curso *curso, int matricula){
    if (alunos != NULL) {
        if (alunos->cod_matricula == matricula)
            exibir_disciplinas_aluno_matriculado(alunos, curso);
        else 
            exibir_disciplinas_por_aluno(alunos->prox, curso, matricula);
    }
}


// XI -  Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.
void buscar_notas_pertence_periodo(Arv_notas *notas, Arv_disciplina *disciplina, int periodo){
    if(notas != NULL){
        if(notas->semestre_cursado == periodo){
            Arv_disciplina *disciplina_periodo = buscar_disciplina(disciplina ,notas->cod_disciplina);
            if(disciplina_periodo != NULL){
                exibir_disciplina(disciplina_periodo);
                printf("\nNota final:%d",notas->nota_final);
            }
        }
        if(notas->esq != NULL)
            buscar_notas_pertence_periodo(notas->esq, disciplina, periodo);
        if(notas->dir != NULL)
            buscar_notas_pertence_periodo(notas->dir, disciplina, periodo);
    }
}

void exibir_todas_notas_disciplinas_determinado_periodo_aluno(Lista_alunos *aluno, Arv_disciplina *disciplina, int periodo, int matricula){
    if(aluno != NULL){
        if(aluno->cod_matricula == matricula)
            buscar_notas_pertence_periodo(aluno->notas, disciplina, periodo);
    }
}

// XII - Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da disciplina
void exibir_nota_disciplina_aluno(Lista_alunos *aluno, Arv_curso *curso, int codigo_disciplina, int codigo_matricula){
    if (aluno == NULL)
        printf("Não foi possível exibir as informações desse aluno!\n");
    else if (aluno->cod_matricula == codigo_matricula) {
        Arv_curso *curso_aluno = buscar_curso(curso, aluno->cod_curso);
        
        if (curso_aluno != NULL) {
            Arv_disciplina *disciplina_encontrada = buscar_disciplina(curso_aluno->disciplinas, codigo_disciplina);
            
            if (disciplina_encontrada != NULL) {
                int nota_final = achar_nota_final(aluno->notas, codigo_disciplina);
                
                if (nota_final != -1) {
                    printf("Disciplina: %s\n", disciplina_encontrada->nome);
                    printf("Nota: %.2f\n", nota_final);
                    printf("Período: %d\n", disciplina_encontrada->periodo_disciplina);
                    printf("Carga Horária: %d\n", disciplina_encontrada->carga_horaria);
                } else
                    printf("Aluno não tem nota registrada para essa disciplina!\n");
            } else
                printf("Disciplina não encontrada no curso!\n");
        } else
            printf("Curso não encontrado!\n");
    } else
        exibir_nota_disciplina_aluno(aluno->prox, curso, codigo_disciplina, codigo_matricula);
}

// XIII - Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na mesma.
void remover_disciplina_de_um_curso_sem_aluno_matriculado(Lista_alunos *aluno, Arv_curso *curso, int codigo_curso, int codigo_disciplina){
    Arv_curso *achei_curso = buscar_curso(curso, codigo_curso);
    if (achei_curso == NULL || achei_curso->disciplinas == NULL) { 
        printf("\nCurso ou lista de disciplinas inválida.\n");
        return;
    }
    
    Arv_disciplina *achei_disciplina = buscar_disciplina(achei_curso->disciplinas, codigo_disciplina);
    if(achei_disciplina == NULL){
        printf("\nA disciplina não foi encontrada!\n");
        return;
    }

        int var_verificar = aluno_esta_cadastrado_na_disciplina(aluno, achei_disciplina); 
        if (var_verificar == 1)
            printf("\nNão é possível remover a disciplina, pois tem aluno(s) cadastrado(s)");
        else{
            int resultado = remover_disciplina(&(achei_curso->disciplinas), codigo_disciplina); 
            if(resultado == 1)
                printf("\nDisciplina removida com sucesso!");
            else
                printf("\nErro na função de remover disciplina!");
        }
}

int remover_disciplina(Arv_disciplina **disciplina_remover, int codigo_disciplina){
    int resultado = 0;
    if(*disciplina_remover != NULL){
        if((*disciplina_remover)->cod_disciplina == codigo_disciplina){
            resultado = 1;
            if(eh_folha_disciplina(*disciplina_remover)){
                free(*disciplina_remover);
                *disciplina_remover = NULL;
            }else if(so_um_filho_disciplina(*disciplina_remover)){
                Arv_disciplina *aux;
                if((*disciplina_remover)->esq == NULL){
                    aux = (*disciplina_remover)->dir;
                    free((*disciplina_remover));
                    *disciplina_remover = aux;
                }else{
                    aux = (*disciplina_remover)->esq;
                    free((*disciplina_remover));
                    *disciplina_remover = aux;
                }
            }else{
                Arv_disciplina *aux = (*disciplina_remover)->dir;
                while (aux->esq != NULL)
                    aux = aux->esq;
                (*disciplina_remover)->cod_disciplina = aux->cod_disciplina;
                strcpy((*disciplina_remover)->nome, aux->nome);
                (*disciplina_remover)->periodo_disciplina = aux->periodo_disciplina;
                (*disciplina_remover)->carga_horaria = aux->carga_horaria;
                remover_disciplina(&(*disciplina_remover)->dir, aux->cod_disciplina);
            }
        }
    }
    return resultado;
}

// XIV - Permita remover uma disciplina da árvore de matrícula de um determinado aluno.
void remover_disciplina_da_arvore_de_matricula_aluno(Arv_matricula **matriculas, int codigo_disciplina){
    if(*matriculas != NULL){
        if((*matriculas)->cod_disciplina == codigo_disciplina)
            remover_disciplina_arvore_matricula(&(*matriculas), codigo_disciplina);
        else{
            if((*matriculas)->cod_disciplina > codigo_disciplina)
                remover_disciplina_da_arvore_de_matricula_aluno(&(*matriculas)->esq, codigo_disciplina);
            else if((*matriculas)->cod_disciplina < codigo_disciplina)
                remover_disciplina_da_arvore_de_matricula_aluno(&(*matriculas)->dir, codigo_disciplina);
        }
    }
}

int remover_disciplina_arvore_matricula(Arv_matricula **matricula, int codigo_disciplina){
    int resultado = 0;
    if((*matricula)->cod_disciplina == codigo_disciplina){
        if(eh_folha_matricula(*matricula)){
            free(*matricula);
            *matricula = NULL;
            resultado = 1;
        }else if(so_um_filho_matricula(*matricula)){
            Arv_matricula *aux;
            if((*matricula)->esq == NULL){
                aux = (*matricula)->dir;
                free((*matricula));
                *matricula = aux;
            }else{
                aux = (*matricula)->esq;
                free((*matricula));
                *matricula = aux;
            }
            resultado = 1;
        }else{
            Arv_matricula *aux = (*matricula)->dir;
            while (aux->esq != NULL)
                aux = aux->esq;
            (*matricula)->cod_disciplina = aux->cod_disciplina;
            remover_disciplina_arvore_matricula(&(*matricula)->dir, aux->cod_disciplina);
            resultado = 1;
        }
    }
    return resultado;
}

// XV - Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva nota organizadas pelo período que a disciplina está cadastrada no curso.
void disciplinas_cursadas(Arv_matricula *matriculas, Arv_disciplina *disciplinas,Arv_notas *notas, int periodo){ 
    if(matriculas != NULL){
        if(matriculas->cod_disciplina == disciplinas->cod_disciplina && disciplinas->periodo_disciplina == periodo){
            float nota_atual = buscar_nota_atual(notas, disciplinas);
            printf("\nNome: %s",disciplinas->nome);
            if(nota_atual >= 0)
                printf("\nNota final:%.2f", nota_atual);
            else
                printf("A nota final da disciplina não foi encontrada!");
        }
        disciplinas_cursadas(matriculas->esq, disciplinas, notas, periodo);
        disciplinas_cursadas(matriculas->dir, disciplinas, notas, periodo);
    }
}

void aluno_curso_esta_matriculado(Lista_alunos *aluno, Arv_curso *curso,int periodo){
    if(curso != NULL){
        if(aluno->cod_curso == curso->cod_curso){
            printf("\nDisciplinas do %d° periodo:\n%s",periodo, curso->nome);
            disciplinas_cursadas(aluno->matriculas, curso->disciplinas, aluno->notas, periodo);

        }
        aluno_curso_esta_matriculado(aluno, curso->esq, periodo);
        aluno_curso_esta_matriculado(aluno, curso->dir,periodo);
    }
}

void mostrar_historico_aluno(Lista_alunos *aluno, Arv_curso *curso) {
    if (curso == NULL || aluno == NULL) {
        printf("Aluno ou curso não encontrado.\n");
        return;
    }
    printf("\nCursos em que o aluno está matriculado:\n");

    int max_periodo = curso->qtd_periodos;

    for (int periodo = 1; periodo <= max_periodo; periodo++) {
        aluno_curso_esta_matriculado(aluno, curso, periodo);
    }
}










// Funções auxiliares
Arv_disciplina* buscar_disciplina(Arv_disciplina *disciplina, int codigo_disciplina) {
    Arv_disciplina *resultado;
    if (disciplina == NULL || disciplina->cod_disciplina == codigo_disciplina)  
        resultado = disciplina;
    else if (codigo_disciplina < disciplina->cod_disciplina)
        resultado = buscar_disciplina(disciplina->esq, codigo_disciplina);
    else
        resultado = buscar_disciplina(disciplina->dir, codigo_disciplina);
    return resultado;
}

Arv_curso* buscar_curso(Arv_curso *curso, int codigo_curso) {
    Arv_curso *resultado = NULL;
    if (curso != NULL) {
        if (curso->cod_curso == codigo_curso)
            resultado = curso;
        else if (codigo_curso < curso->cod_curso)
            resultado = buscar_curso(curso->esq, codigo_curso);
        else
            resultado = buscar_curso(curso->dir, codigo_curso);
    }
    return resultado;
}

void exibir_disciplina(Arv_disciplina *disciplina){
    printf("\n\nNome: %s\nID da disciplina: %d\nPeriodo: %d\nCarga Horaria: %d\n-------------------------------\n",disciplina->nome,disciplina->cod_disciplina,disciplina->periodo_disciplina,disciplina->carga_horaria);
}

int achar_nota_final(Arv_notas *notas, int codigo_disciplina) {
    int resultado = -1;
    if (notas != NULL){
        if (notas->cod_disciplina == codigo_disciplina)
            resultado = notas->nota_final;
        else if (codigo_disciplina < notas->cod_disciplina)
            resultado = achar_nota_final(notas->esq, codigo_disciplina);
        else
            resultado = achar_nota_final(notas->dir, codigo_disciplina);
    }
    return resultado;
}

int aluno_esta_cadastrado_na_disciplina(Lista_alunos *aluno, Arv_disciplina *disciplina){
    int resultado = (aluno->matriculas->cod_disciplina == disciplina->cod_disciplina) ? 1:0;

    if(resultado == 0 && aluno->prox != NULL)
        resultado = aluno_esta_cadastrado_na_disciplina(aluno->prox, disciplina);
    return resultado;
}

int eh_folha_disciplina(Arv_disciplina *disciplina){
    return(disciplina-> esq == NULL && disciplina->dir == NULL) ? 1 : 0;
}

int eh_folha_matricula(Arv_matricula *matricula) {
    return (matricula->esq == NULL && matricula->dir == NULL) ? 1 : 0;
}

int so_um_filho_disciplina(Arv_disciplina *disciplina){
    return (disciplina->esq == NULL) ^ (disciplina->dir == NULL);
}

int so_um_filho_matricula(Arv_matricula *matricula) {
    return (matricula->esq == NULL) ^ (matricula->dir == NULL) ? 1 : 0;
}

float buscar_nota_atual(Arv_notas *notas, Arv_disciplina *disciplina){
    float nota_atual = -1;
    if(notas != NULL){
        if(disciplina->cod_disciplina == notas->cod_disciplina)
            nota_atual = notas->nota_final;
        else if (notas->cod_disciplina > disciplina->cod_disciplina)
            nota_atual = buscar_nota_atual(notas->esq, disciplina);
        else
            nota_atual = buscar_nota_atual(notas->dir, disciplina);
    }
    return nota_atual;
}