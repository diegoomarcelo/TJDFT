#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int main() {
    int linhas = NumeroLinhas("TJDFT_amostra.csv");   // quantidade de processos lidos
    DataJUD * dados = LerDados("TJDFT_amostra.csv", linhas);
    int funcao;
    float cumprimento;   //resultado da função 11
    int ok;             // flag da função 10
    int dias;           // resultado da função 10
    int qtd_violencia_domestrica; // resultado da função 4
    int qtd_feminicio; // resultado da função 5
    int qtd_ambientais; // resultado da função 6
    int qtd_infancia_e_juventude;   // resultado da função 9
    int qtd_indigenas;   // resultado da função 8
    int qtd_quilombolas;   // resultado da função 7
    int qtd_numeros_processos_presentes; //resultado da função 1
    char alvo[20];

    if (!dados || linhas<=0) {
        printf("Erro ao abrir arquivo ou arquivo vazio\n");
        exit(1);
    }
    printf("Bem vindo ao nosso programa, digite o numero antes do texto para realizar aquela opção\n");
    do{
        printf("1-Checar o numero de processos presente na base de dados\n");
        printf("2-Checar o id ultimo orgão julgador que atuou no precesso informado\n");
        printf("3-Ver o id do processo com a data de recebimento mais antiga presente no banco de dados\n");
        printf("4-Ver quantos processos estão relacionadas a causas de violência doméstica\n");
        printf("5-Ver quantos processos estão relacionadas a causas de feminicídio\n");
        printf("6-Ver quantos processos estão relacionadas a causas ambientais\n");
        printf("7-Ver quantos processos estão relacionadas a causas de quilombolas\n");
        printf("8-Ver quantos processos estão relacionadas a causas indígenas\n");
        printf("9-Ver quantos processos envolve causas relacionadas a infância e juventude\n");
        printf("10-Ver o numero de dias entre a data de recebimento e a data de resolução dos dados presentes no banco de dados\n");
        printf("11-Ver o percentual de cumprimento da meta 1 dos casos\n");
        printf("12-Gerar um arquivo CSV com todos os  processos julgados (mérito) na Meta 1\n");
        printf("13-Sair\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &funcao);
        // system("cls");

        switch (funcao){
            case 1:
                qtd_numeros_processos_presentes = contar_numero_processos_presentes_na_base_dados(dados, linhas);
                printf("[1] Quantidade de processos presentes na base de dados: %d\n", qtd_numeros_processos_presentes);
                break;
            case 2:
                printf("Digite o id_processo: ");
                scanf("%19s", alvo);
                buscar_id_ultimo_oj_a_partir_do_id_processos(dados, linhas, alvo);
                
                break;
            case 3:
                // Função 3 - retorna o id_processo do mais antigo (menor dt_recebimento)
                buscar_processo_mais_antigo_a_partir_do_id_processo(dados, linhas);    
                break;
            case 4:
                qtd_violencia_domestrica = contar_processos_violencia_domestica(dados, linhas);
                printf("[4] Quantidade de processos envolvendo violência domêstica: %d\n", qtd_violencia_domestrica);
                break;
            case 5:
                qtd_feminicio = contar_processos_violencia_domestica(dados, linhas);
                printf("[5] Quantidade de processos envolvendo feminicídio: %d\n", qtd_feminicio);
                break;
            case 6:
                qtd_ambientais = contar_processos_violencia_domestica(dados, linhas);
                printf("[6] Quantidade de processos envolvendo ambientais: %d\n", qtd_ambientais);
                break;
            case 7:
                qtd_quilombolas = contar_processos_quilombolas(dados, linhas);
                printf("[7] Quantidade de processos envolvendo cominidades quilombolas: %d\n", qtd_quilombolas);
                break;
            case 8:
                qtd_indigenas = contar_processos_quilombolas(dados, linhas);
                printf("[8] Quantidade de processos envolvendo povos indigenas: %d\n", qtd_indigenas);
                break;
            case 9:
                qtd_infancia_e_juventude = contar_processos_infancia(dados, linhas);
                printf("[9] Quantidade de processos envolvendo infância e juventude(ECA): %d\n", qtd_infancia_e_juventude);
                break;
            case 10:
                for (int i = 0; i < linhas; i++) {
                    ok = 0;
                    dias = dias_entre_recebimento_e_resolvido(&dados[i], &ok);
                    if (ok) {
                        printf("[10] id=%s | receb=%s | resolv=%s | dias=%d\n",
                            dados[i].id_processo,
                            dados[i].dt_recebimento,
                            dados[i].dt_resolvido,
                            dias);
                    }
                }
                break;
            case 11:
                cumprimento = Cumprimento(dados, linhas);
                printf("Percentual de cumprimento da meta 1: %.2f\n", cumprimento);
                break;
            case 12:
                gerar_csv(dados, linhas);
                printf("Verifique a pasta de arquivos para ver o arquivo pedido, o nome do arquivo está como TJDFT_cumprimento.csv\n");
                break;
            case 13:
                break;
            default:
                break;
        }
    } while (funcao != 13);

    return 0;
}


   