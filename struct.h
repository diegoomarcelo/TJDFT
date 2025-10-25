#ifndef STRUCT_H
#include <stdbool.h>
#define STRUCT_H

typedef struct{
    char id_processo[20];
    char numero_sigilo[30];
    char sigla_grau[15];
    char procedimento[30];
    char ramo_justica[20];
    char sigla_tribunal[20];
    char id_tribunal[15];
    int recurso;
    char id_ultimo_oj[20];
    char dt_recebimento[20];
    char id_ultima_classe[20];
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;
    char decisao[20];
    char dt_resolvido[20];
    float cnm1;
    float primeirasentm1;
    float baixm1;
    float decm1;
    float mpum1;
    float julgadom1;
    float desm1;
    float susm1;
    float cumprimento;
} DataJUD;

DataJUD * LerDados(char * NomeArquivo, int tamanho);
int NumeroLinhas(char * NomeArquivo);
bool linha_tem_dados(char * linha);
int dias_entre_recebimento_e_resolvido(DataJUD * p, int * ok);
int contar_processos_infancia(DataJUD * v, int n);
int contar_processos_quilombolas(DataJUD * v, int n);
int contar_processos_indigenas(DataJUD * v, int n);
float Cumprimento(DataJUD * X, int repeticoes);
void gerar_csv(DataJUD * X,int z);
int contar_numero_processos_presentes_na_base_dados(DataJUD * v, int n);
void buscar_id_ultimo_oj_a_partir_do_id_processos(DataJUD *v, int n, const char *id_processo);
void buscar_processo_mais_antigo_a_partir_do_id_processo(DataJUD *v, int n);
int contar_processos_violencia_domestica(DataJUD * v, int n);
int contar_processos_feminicicio(DataJUD * v, int n);
int contar_processos_ambientais(DataJUD * v, int n);
#endif