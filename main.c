#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void menu() {
    printf("|                      ----------                     |\n");
    printf("|--------------------- Menu Geral --------------------|\n");
    printf("|                      ----------                     |\n");
    printf("|                                                     |\n");
    printf("|     1. Cadastrar Aluno (I)                          |\n");
    printf("|     2. Cadastrar Curso (II)                         |\n");
    printf("|     3. Cadastrar Disciplina (III)                   |\n");
    printf("|     4. Cadastrar Matrícula (IV)                     |\n");
    printf("|     5. Cadastrar Nota (V)                           |\n");
    printf("|     6. Mostrar Alunos de um Curso (VI)              |\n");
    printf("|     7. Mostrar Cursos do Campus (VII)               |\n");
    printf("|     8. Mostrar Disciplinas de um Curso (VIII)       |\n");
    printf("|     9. Mostrar Disciplinas de um Período (IX)       |\n");
    printf("|    10. Mostrar Disciplinas Matriculadas (X)         |\n");
    printf("|    11. Mostrar Notas por Período (XI)               |\n");
    printf("|    12. Mostrar Nota de uma Disciplina (XII)         |\n");
    printf("|    13. Remover Disciplina de Curso (XIII)           |\n");
    printf("|    14. Remover Disciplina da Matrícula (XIV)        |\n");
    printf("|    15. Mostrar Histórico do Aluno (XV)              |\n");
    printf("|    16. Sair                                         |\n");
    printf("|                                                     |\n");
    printf("|-----------------------------------------------------|\n");
}

int main() {
    Lista_alunos *lista_alunos = NULL;
    Arv_curso *arvore_cursos = NULL;
    int opcao;

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome[50];
                int matricula, cod_curso;

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
                int cod_curso, qtd_periodos;
                char nome[50];

                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Digite a quantidade de períodos: ");
                scanf("%d", &qtd_periodos);
                printf("Digite o nome do curso: ");
                scanf(" %[^\n]", nome);

                if (cadastrar_curso(&arvore_cursos, cod_curso, qtd_periodos, nome)) {
                    printf("Curso cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar curso.\n");
                }
                break;
            }
            case 3: {
                int cod_curso, cod_disciplina, periodo_disciplina, carga_horaria;
                char nome[50];

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
                int cod_disciplina, cod_matricula;

                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                printf ("Digite o código da matrícula: ");
                scanf("%d", &cod_matricula);

                if (cadastrar_matricula(&lista_alunos, cod_matricula, cod_disciplina)) {
                    printf("Matrícula cadastrada com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar matrícula.\n");
                }
                break;
            }
            case 5: {
                int cod_matricula, cod_disciplina, nota;

                printf("Digite o código da matrícula: ");
                scanf("%d", &cod_matricula);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                printf("Digite a nota: ");
                scanf("%d", &nota);

                if (cadastrar_nota(cod_matricula, cod_disciplina, nota)) {
                    printf("Nota cadastrada com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar nota.\n");
                }
                break;
            }
            case 6: {
                int cod_curso;
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
                int cod_curso;
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                disciplinas_do_curso(arvore_cursos, cod_curso);
                break;
            }
            case 9: {
                int periodo;
                printf("Digite o período: ");
                scanf("%d", &periodo);
                disciplinas_por_periodo(arvore_cursos, periodo);
                break;
            }
            case 10: {
                int cod_matricula;
                printf("Digite o código da matrícula: ");
                scanf("%d", &cod_matricula);
                disciplinas_matriculadas(cod_matricula);
                break;
            }
            case 11: {
                int periodo;
                printf("Digite o período: ");
                scanf("%d", &periodo);
                notas_por_periodo(periodo);
                break;
            }
            case 12: {
                int cod_disciplina;
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                nota_disciplina(cod_disciplina);
                break;
            }
            case 13: {
                int cod_curso, cod_disciplina;
                printf("Digite o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                if (remover_disciplina_curso(&arvore_cursos, cod_curso, cod_disciplina)) {
                    printf("Disciplina removida do curso com sucesso!\n");
                } else {
                    printf("Erro ao remover disciplina do curso.\n");
                }
                break;
            }
            case 14: {
                int cod_matricula, cod_disciplina;
                printf("Digite o código da matrícula: ");
                scanf("%d", &cod_matricula);
                printf("Digite o código da disciplina: ");
                scanf("%d", &cod_disciplina);
                if (remover_disciplina_matricula(cod_matricula, cod_disciplina)) {
                    printf("Disciplina removida da matrícula com sucesso!\n");
                } else {
                    printf("Erro ao remover disciplina da matrícula.\n");
                }
                break;
            }
            case 15: {
                int cod_matricula;
                printf("Digite o código da matrícula: ");
                scanf("%d", &cod_matricula);
                historico_aluno(cod_matricula);
                break;
            }
            case 16:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 16);

    // Liberação de memória (se necessário)
    // Aqui você deve liberar a memória alocada para lista_alunos e arvore_cursos

    return 0;
}