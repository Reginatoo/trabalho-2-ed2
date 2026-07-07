#ifndef GEO_H
#define GEO_H

#include "quadra.h"

typedef struct geo* Geo;

/**
 * @brief cria um gerenciador do arquivo de geometria urbana
 * @return a instancia do gerenciador geo criado
 */
Geo criarGeo(void);

/**
 * @brief libera toda a memoria alocada para o gerenciador geo e suas quadras
 * @param g o gerenciador geo a ser destruido
 */
void destruirGeo(Geo g);

/**
 * @brief adiciona uma quadra ao gerenciador geo
 * @param g o gerenciador geo alvo
 * @param q a quadra a ser adicionada
 */
void geoAdicionarQuadra(Geo g, Quadra q);

/**
 * @brief busca uma quadra no gerenciador geo pelo seu cep
 * @param g o gerenciador geo alvo
 * @param cep o identificador cep da quadra procurada
 * @return a instancia da quadra encontrada ou nulo caso nao exista
 */
Quadra geoBuscarQuadra(Geo g, char* cep);

/**
 * @brief processa e le as informacoes de um arquivo ponto geo povoando o gerenciador
 * @param g o gerenciador geo alvo
 * @param caminho o caminho do arquivo ponto geo a ser lido
 * @return um numero inteiro indicando sucesso ou falha na leitura
 */
int geoLerArquivo(Geo g, char* caminho);

void geoDesenhar(Geo g, FILE* svg);

#endif // geo_h