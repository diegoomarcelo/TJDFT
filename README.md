# 📊 Sistema de Consulta de Processos (TJDFT)

> Este programa permite a leitura e análise de dados de processos judiciais a partir de um arquivo CSV. O projeto possui **finalidade estritamente acadêmica**, desenvolvido para estudo de estruturas de dados, manipulação de arquivos e análise básica de informações. Ele realiza consultas interativas, cálculos de métricas e pode gerar relatórios filtrados.
---

## Objetivo

O sistema permite consultar informações de processos do TJDFT a partir de um arquivo CSV, realizar cálculos estatísticos, buscar registros específicos e gerar relatórios filtrados.

---

## Estrutura do Projeto

```
📁 projeto
├── main.c         # Controle do fluxo principal e menu interativo
├── struct.h       # Estrutura DataJUD e protótipos de funções
├── funcoes.c      # Implementação das funções de consulta, contagem e relatórios
└── dados.csv      # Arquivo de entrada contendo os processos (ex.: TJDFT_amostra.csv)
```

---

## Entrada de Dados

O programa utiliza um arquivo CSV contendo os processos. Cada linha representa um procedimento judicial com campos como:

* `id_processo`
* `dt_recebimento`
* `dt_resolvido`
* Indicadores/flags de categorias (ex.: violência doméstica, feminicídio, etc.)

---

## Funcionalidades

| Nº  | Função                             | Descrição                                                                     |
| --- | ---------------------------------- | ----------------------------------------------------------------------------- |
| 1   | Contagem total                     | Conta quantos processos estão presentes na base.                              |
| 2   | Busca por ID                       | Busca `id_ultimo_oj` a partir de um `id_processo`.                            |
| 3   | Processo mais antigo               | Identifica o processo com menor `dt_recebimento`.                             |
| 4–9 | Contagens por categoria            | Conta processos de categorias específicas (ex.: feminicídio, ambiental etc.). |
| 10  | Dias entre recebimento e resolução | Calcula o tempo de tramitação em dias.                                        |
| 11  | Percentual de cumprimento          | Calcula taxa de cumprimento geral.                                            |
| 12  | Geração de CSV filtrado            | Exporta processos com cumprimento > 100%.                                     |
| 13  | Sair                               | Encerra o programa.                                                           |

---

## Saída Gerada

Caso solicitado no menu, o programa cria o arquivo:

```
TJDFT_cumprimento.csv
```

contendo apenas processos cuja taxa de cumprimento é maior que **100%**.

---

## 🎓 Finalidade

Este software foi desenvolvido **exclusivamente para fins acadêmicos**, abordando:

* Manipulação de arquivos CSV
* Uso de estruturas (`struct`) e vetores dinâmicos
* Funções em módulos distintos
* Cálculo de métricas e filtragem de dados


