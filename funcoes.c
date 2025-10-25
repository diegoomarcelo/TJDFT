#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "struct.h"

#define TAM_BUFFER 8192

//Função para ler os dados do arquivo
DataJUD * LerDados(char * NomeArquivo, int tamanho) {
    
    FILE *arq = fopen(NomeArquivo, "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    char linha[1024];
    fgets(linha, sizeof(linha), arq); // descarta cabeçalho

    
    DataJUD * X = malloc(tamanho * sizeof(DataJUD));

    
    int i = 0;

    while (i < tamanho && fgets(linha, sizeof(linha), arq)) {
    // tira quebra de linha
    linha[strcspn(linha, "\r\n")] = 0;

    int c = 0;
    char *p = linha;
    char *start = linha;

    while (1) {
        if (*p == ';' || *p == '\0') {
            int len = p - start;
            char campo[256]; // buffer temporário
            if (len > 0) {
                strncpy(campo, start, len);
                campo[len] = '\0';
            } else {
                // campo vazio
                campo[0] = '\0';
            }

            // agora faz o tratamento do campo
            if (c == 0) strcpy(X[i].id_processo, campo);
            if (c == 1) strcpy(X[i].numero_sigilo, campo);
            if (c == 2) strcpy(X[i].sigla_grau, campo);
            if (c == 3) strcpy(X[i].procedimento, campo);
            if (c == 4) strcpy(X[i].ramo_justica, campo);
            if (c == 5) strcpy(X[i].sigla_tribunal, campo);
            if (c == 6) strcpy(X[i].id_tribunal, campo);
            if (c == 7) X[i].recurso = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 8) strcpy(X[i].id_ultimo_oj, campo);
            if (c == 9) strcpy(X[i].dt_recebimento, campo);
            if (c == 10) strcpy(X[i].id_ultima_classe, campo);
            if (c == 11) X[i].flag_violencia_domestica = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 12) X[i].flag_feminicidio = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 13) X[i].flag_ambiental = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 14) X[i].flag_quilombolas = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 15) X[i].flag_indigenas = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 16) X[i].flag_infancia = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 17) strcpy(X[i].decisao, campo);
            if (c == 18) strcpy(X[i].dt_resolvido, campo);
            if (c == 19) X[i].cnm1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 20) X[i].primeirasentm1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 21) X[i].baixm1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 22) X[i].decm1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 23) X[i].mpum1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 24) X[i].julgadom1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 25) X[i].desm1 = (campo[0] == '\0') ? 0 : atoi(campo);
            if (c == 26) X[i].susm1 = (campo[0] == '\0') ? 0 : atoi(campo);

            c++;

            if (*p == '\0') break; // fim da linha
            start = p + 1;
        }
        p++;
    }

    int den = X[i].cnm1 + X[i].desm1 - X[i].susm1;
    if (den > 0)
        X[i].cumprimento = ((double)X[i].julgadom1 / den) * 100.0;
    else
        X[i].cumprimento = 0;

    i++;
}

    fclose(arq);
    return X;
}
//Função para verificar se a linha possui dados
bool linha_tem_dados(char *linha) {
    while (*linha) {
        if (!isspace((unsigned char)*linha) && *linha != ';') {
            return true;
        }
        linha++;
    }
    return false;
}
// Função para checar o numero de linhas vindas do arquivo
int NumeroLinhas(char * NomeArquivo) {
    FILE *arq = fopen(NomeArquivo, "r");
    bool dentro_de_aspas = false;
    bool primeira_linha = true;
    int total_linhas = 0;
    char buffer[TAM_BUFFER];
    char linha_logica[TAM_BUFFER * 4];// suporta linhas com quebras

    if (!arq) {
        printf("Erro ao abrir arquivo");
        exit(1);
    }
     
    linha_logica[0] = '\0';


    while (fgets(buffer, sizeof(buffer), arq)) {
        strcat(linha_logica, buffer);

        size_t len = strlen(buffer);
        if (len == 0) continue;

        // Verifica se tem número ímpar de aspas duplas (linha ainda não terminou logicamente)
        for (size_t i = 0; i < len; i++) {
            if (buffer[i] == '\"') {
                dentro_de_aspas = !dentro_de_aspas;
            }
        }

        // Se ainda está dentro de aspas, continua acumulando
        if (dentro_de_aspas) {
            continue;
        }

        // Linha lógica completa
        if (primeira_linha) {
            // Ignora cabeçalho
            primeira_linha = false;
        } else {
            // Remove \r\n do final
            linha_logica[strcspn(linha_logica, "\r\n")] = 0;

            if (linha_tem_dados(linha_logica)) {
                total_linhas++;
            }
        }

        // Limpa para a próxima linha lógica
        linha_logica[0] = '\0';
    }

    fclose(arq);
    return total_linhas;
}


//Função 1 -  o número de processos presentes na base de dados;
int contar_numero_processos_presentes_na_base_dados(DataJUD * v, int n){
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].id_processo != 0) cont++;
    }
    return cont;
}

//Função 2 - o id_ultimo_oj a partir de id_processo;

void buscar_id_ultimo_oj_a_partir_do_id_processos(DataJUD *v, int n, const char *id_processo) {
    if (!v || n <= 0 || !id_processo) {
        printf("Dados inválidos.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].id_processo, id_processo) == 0) {
            printf("[2] id_processo=%s - id_ultimo_oj=%s\n",
                   v[i].id_processo,
                   v[i].id_ultimo_oj);
            return;
        }
    }

    printf("[2] id_processo %s não foi encontrado.\n", id_processo);
}

// Função 3 - retorna o id_processo do mais antigo (menor dt_recebimento)
void buscar_processo_mais_antigo_a_partir_do_id_processo(DataJUD *v, int n){
    if (!v || n <= 0) {
        printf("Dados inválidos.\n");
        return;
    }

    int indice_min = -1;
    struct tm t_min, t_atual;
    time_t tempo_min, tempo_atual;

    for (int i = 0; i < n; i++) {
        if (strlen(v[i].dt_recebimento) < 10) continue; // ignora datas vazias

        int ano, mes, dia;
        if (sscanf(v[i].dt_recebimento, "%d-%d-%d", &ano, &mes, &dia) != 3) continue;

        memset(&t_atual, 0, sizeof(t_atual));
        t_atual.tm_year = ano - 1900;
        t_atual.tm_mon  = mes - 1;
        t_atual.tm_mday = dia;

        tempo_atual = mktime(&t_atual);

        if (indice_min == -1) {
            indice_min = i;
            t_min = t_atual;
            tempo_min = tempo_atual;
        } else if (tempo_atual < tempo_min) {
            indice_min = i;
            t_min = t_atual;
            tempo_min = tempo_atual;
        }
    }

    if (indice_min != -1) {
        printf("[3] Processo mais antigo: id_processo=%s | dt_recebimento=%s\n",
               v[indice_min].id_processo,
               v[indice_min].dt_recebimento);
    } else {
        printf("[3] Nenhuma data válida encontrada.\n");
    }
}

//Função 4 - quantos processos estão relacionadas a causas de violência doméstica
int contar_processos_violencia_domestica(DataJUD * v, int n) {
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].flag_violencia_domestica != 0) cont++;
    }
    return cont;
}

//Função 5 - quantos processos estão relacionadas a causas de feminicídio
int contar_processos_feminicicio(DataJUD * v, int n) {
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].flag_feminicidio != 0) cont++;
    }
    return cont;
}
//Função 6 - quantos processos estão relacionadas a causas ambientais
int contar_processos_ambientais(DataJUD * v, int n) {
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].flag_ambiental != 0) cont++;
    }
    return cont;
}

//Função 7 - quantos processos estão relacionadas a causas de quilombolas
int contar_processos_quilombolas(DataJUD * v, int n) {
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].flag_quilombolas != 0) cont++;
    }
    return cont;
}
// Função 8
int contar_processos_indigenas(DataJUD * v, int n) {
    int cont = 0;
    if (!v || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        if (v[i].flag_indigenas != 0) cont++;
    }
    return cont;
}
// Função 9
int contar_processos_infancia(DataJUD * v, int n) {
    int cont = 0;
    int i;
    if (!v || n <= 0) return 0;

    for (i = 0; i < n; i++) {
        if (v[i].flag_infancia != 0) cont++;
    }
    return cont;
}
// Função 10
int dias_entre_recebimento_e_resolvido(DataJUD *p, int *ok) {
    int y1, m1, d1, y2, m2, d2;
    struct tm t1, t2;
    time_t time1, time2;

    if (ok) *ok = 0;
    if (!p || strlen(p->dt_recebimento) < 10 || strlen(p->dt_resolvido) < 10)
        return -1;

    if (sscanf(p->dt_recebimento, "%d-%d-%d", &y1, &m1, &d1) != 3) return -1;
    if (sscanf(p->dt_resolvido,   "%d-%d-%d", &y2, &m2, &d2) != 3) return -1;

    memset(&t1, 0, sizeof(t1));
    memset(&t2, 0, sizeof(t2));

    t1.tm_year = y1 - 1900;
    t1.tm_mon  = m1 - 1;
    t1.tm_mday = d1;

    t2.tm_year = y2 - 1900;
    t2.tm_mon  = m2 - 1;
    t2.tm_mday = d2;

    time1 = mktime(&t1);
    time2 = mktime(&t2);
    if (time1 == (time_t)-1 || time2 == (time_t)-1) return -1;

    if (ok) *ok = 1;
    return (int)(difftime(time2, time1) / (60 * 60 * 24)); // converte para dias
}
// Função 11
float Cumprimento(DataJUD * X, int repeticoes){
    float cumprimento=0;
    float cnm1=0, julgadom1=0, desm1=0, susm1=0;

    for(int i=0 ;i < repeticoes ; i++){
        
        cnm1 += X[i].cnm1;
        julgadom1 += X[i].julgadom1;
        desm1 += X[i].desm1;
        susm1 += X[i].susm1;
        
    }

    float den = cnm1 + desm1 - susm1;
    cumprimento = (julgadom1/den) * 100;

    return cumprimento;
}
// Função 12
void gerar_csv(DataJUD * X,int z){
    FILE * f = fopen("TJDFT_cumprimento.csv", "w");
    if(f == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }
    
fprintf(f, "id_processo;numero_sigilo;sigla_grau;procedimento;ramo_justica;sigla_tribunal;id_tribunal;recurso;id_ultimo_oj;dt_recebimento;id_ultima_classe;flag_violencia_domestica;flag_feminicidio;flag_ambiental;flag_quilombolas;flag_indigenas;flag_infancia;decisao;dt_resolvido;cnm1;primeirasentm1;baixm1;decm1;mpum1;julgadom1;desm1;susm1;cumprimento\n");

    for(int i = 0; i < z; i++){
            if (X[i].cumprimento > 100.0) {
                fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%d;%s;%s;%s;%d;%d;%d;%d;%d;%d;%s;%s;%f;%f;%f;%f;%f;%f;%f;%f;%f\n",
                    X[i].id_processo,
                    X[i].numero_sigilo,
                    X[i].sigla_grau,
                    X[i].procedimento,
                    X[i].ramo_justica,
                    X[i].sigla_tribunal,
                    X[i].id_tribunal,
                    X[i].recurso,
                    X[i].id_ultimo_oj,
                    X[i].dt_recebimento,
                    X[i].id_ultima_classe,
                    X[i].flag_violencia_domestica,
                    X[i].flag_feminicidio,
                    X[i].flag_ambiental,
                    X[i].flag_quilombolas,
                    X[i].flag_indigenas,
                    X[i].flag_infancia,
                    X[i].decisao,
                    X[i].dt_resolvido,
                    X[i].cnm1,
                    X[i].primeirasentm1,
                    X[i].baixm1,
                    X[i].decm1,
                    X[i].mpum1,
                    X[i].julgadom1,
                    X[i].desm1,
                    X[i].susm1,
                    X[i].cumprimento
                );
            }
    }
    fclose(f);
}