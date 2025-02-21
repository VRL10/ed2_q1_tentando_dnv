#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void menu() {
    printf("|                      ----------                           |\n");
    printf("|--------------------- Menu Geral --------------------------|\n");
    printf("|                      ----------                           |\n");
    printf("|                                                           |\n");
    printf("|     1. Cadastrar Aluno (I)                                |\n");
    printf("|     2. Cadastrar Curso (II)                               |\n");
    printf("|     3. Cadastrar Disciplina (III)                         |\n");
    printf("|     4. Cadastrar Matrícula (IV)                           |\n");
    printf("|     5. Cadastrar Nota (V)                                 |\n");
    printf("|     6. Mostrar Alunos de um Curso (VI)                    |\n");
    printf("|     7. Mostrar Cursos do Campus (VII)                     |\n");
    printf("|     8. Mostrar Disciplinas de um Curso (VIII)             |\n");
    printf("|     9. Mostrar Disciplinas de um Período do curso (IX)    |\n");
    printf("|    10. Mostrar Disciplinas que um determinad aluno está matriculado (X)               |\n");
    printf("|    11. Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno (XI)                     |\n");
    printf("|    12. Mostrar a nota de uma disciplina de um determinado aluno (XII)               |\n");
    printf("|    13. Remover Disciplina de Curso (XIII)                 |\n");
    printf("|    14. Remover Disciplina da Matrícula (XIV)              |\n");
    printf("|    15. Mostrar Histórico do Aluno (XV)                    |\n");
    printf("|    16. Sair                                               |\n");
    printf("|                                                           |\n");
    printf("|-----------------------------------------------------------|\n");
}

int main() {
    Lista_alunos *lista_alunos = NULL;
    Arv_curso *arvore_cursos = NULL;
    int opcao;

    // Variáveis para uso nos cases
    char nome[50];
    int matricula, cod_curso, cod_disciplina, periodo_disciplina, carga_horaria;
    float nota_final;
    int semestre_cursado;

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", nome);
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);

                if (cadastrar_aluno(&lista_alunos, nome, matricula, cod_curso)) {
                    printf("Aluno cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar aluno.\n");
                }
                break;
            }
            case 2: {
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Digite a quantidade de períodos: ");
                scanf("%d", &periodo_disciplina);
                printf("Digite o nome do curso: ");
                scanf(" %[^\n]", nome);

                if (cadastrar_curso(&arvore_cursos, cod_curso, periodo_disciplina, nome)) {
                    printf("Curso cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar curso.\n");
                }
                break;
            }
            case 3: {
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                printf("Digite o período da disciplina: ");
                scanf("%d", &periodo_disciplina);
                printf("Digite a carga horária da disciplina: ");
                scanf("%d", &carga_horaria);
                printf("Digite o nome da disciplina: ");
                scanf(" %[^\n]", nome);

                if (cadastrar_disciplina(&arvore_cursos, cod_disciplina, periodo_disciplina, carga_horaria, nome, cod_curso)) {
                    printf("Disciplina cadastrada com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar disciplina.\n");
                }
                break;
            }
            case 4: {
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                printf("Digite o código da matrícula: ");
                scanf("%d", &matricula);

                if (cadastrar_matricula(&lista_alunos, cod_disciplina, matricula)) {
                    printf("Matrícula cadastrada com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar matrícula.\n");
                }
                break;
            }
            case 5: {
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                printf("Digite a nota final: ");
                scanf("%f", &nota_final);
                printf("Digite o semestre cursado: ");
                scanf("%d", &semestre_cursado);

                if (cadastrar_notas(&lista_alunos, nota_final, cod_disciplina, matricula, semestre_cursado)) {
                    printf("Nota cadastrada com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar nota.\n");
                }
                break;
            }
            case 6: {
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                aluno_por_curso(lista_alunos, cod_curso);
                break;
            }
            case 7: {
                todos_cursos_do_campus(arvore_cursos);
                break;
            }
            case 8: {
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                encontrar_curso_desejado(arvore_cursos, cod_curso);
                break;
            }
            case 9: {
                printf("Digite o período: ");
                scanf("%d", &periodo_disciplina);
                mostrar_todas_disciplinas_periodo_de_um_curso(arvore_cursos, cod_curso, periodo_disciplina);
                break;
            }
            case 10: {
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                exibir_disciplinas_por_aluno(lista_alunos, arvore_cursos, matricula);
                break;
            }
            case 11: {
                printf("Digite o período: ");
                scanf("%d", &periodo_disciplina);
                printf("Digite a o código da matrícula do aluno: ");
                scanf("%d", &matricula);
                exibir_todas_notas_disciplinas_determinado_periodo_aluno(lista_alunos, arvore_cursos->disciplinas, periodo_disciplina, matricula);
                break;
            }
            case 12: {
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                exibir_nota_disciplina_aluno(lista_alunos, arvore_cursos, cod_disciplina, matricula);
                break;
            }
            case 13: {
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                remover_disciplina_de_um_curso_sem_aluno_matriculado(lista_alunos, arvore_cursos, cod_curso, cod_disciplina);
                break;
            }
            case 14: {
                int matricula, cod_disciplina;
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                printf("Digite o código da disciplina a ser removida: ");
                scanf("%d", &cod_disciplina);
                // Encontrar o aluno na lista de alunos
                Lista_alunos *aluno_encontrado = lista_alunos;
                while (aluno_encontrado != NULL) {
                    if (aluno_encontrado->cod_matricula == matricula) {
                        // Aluno encontrado, agora remover a disciplina da árvore de matrícula
                        remover_disciplina_da_arvore_de_matricula_aluno(&aluno_encontrado->matriculas, cod_disciplina);
                        printf("Disciplina removida com sucesso da matrícula %d.\n", matricula);
                        break;
                    }
                    aluno_encontrado = aluno_encontrado->prox;
                }
                if (aluno_encontrado == NULL)
                    printf("Aluno não encontrado.\n");
                break;
            }
            case 15: {
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matricula);
                mostrar_historico_aluno(lista_alunos, arvore_cursos, matricula);
                break;
            }
            case 16: {
                printf("Saindo do programa...\n");
                break;
            }
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 16);

    liberar_lista_alunos(lista_alunos);
    liberar_arvore_cursos(arvore_cursos);
    return 0;
}