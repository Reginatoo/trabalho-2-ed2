#ifndef VERTICE_H
#define VERTICE_H

typedef struct vertice* Vertice;

/**
 * @brief cria um novo vertice representando uma esquina ou ponto medio
 * @param id o identificador unico do vertice
 * @param x a coordenada x geométrica do ponto
 * @param y a coordenada y geométrica do ponto
 * @return a instancia do vertice criado
 */
Vertice criarVertice(char* id, double x, double y);

/**
 * @brief libera a memoria alocada para o vertice
 * @param v o vertice a ser destruido
 */
void destruirVertice(Vertice v);

/**
 * @brief retorna o identificador do vertice
 * @param v o vertice alvo
 * @return a string com o id do vertice
 */
char* getVerticeId(Vertice v);

/**
 * @brief retorna a coordenada x do vertice
 * @param v o vertice alvo
 * @return o valor de x
 */
double getVerticeX(Vertice v);

/**
 * @brief retorna a coordenada y do vertice
 * @param v o vertice alvo
 * @return o valor de y
 */
double getVerticeY(Vertice v);

#endif