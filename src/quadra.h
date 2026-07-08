#ifndef QUADRA_H
#define QUADRA_H

typedef struct quadra* Quadra;

/**
 * @brief cria uma nova quadra com os parametros especificados
 * @param cep o identificador unico da quadra
 * @param x a coordenada x do canto sudeste ponto de ancoragem
 * @param y a coordenada y do canto sudeste ponto de ancoragem
 * @param w a largura da quadra
 * @param h a altura da quadra
 * @return a instancia da quadra criada
 */
Quadra criarQuadra(char* cep, double x, double y, double w, double h);

/**
 * @brief libera a memoria alocada para a quadra
 * @param q a quadra a ser destruida
 */
void destruirQuadra(Quadra q);

/**
 * @brief retorna o cep da quadra
 * @param q a quadra alvo
 * @return a string contendo o cep
 */
char* getQuadraCep(Quadra q);

/**
 * @brief retorna a coordenada x da quadra
 * @param q a quadra alvo
 * @return o valor de x
 */
double getQuadraX(Quadra q);

/**
 * @brief retorna a coordenada y da quadra
 * @param q a quadra alvo
 * @return o valor de y
 */
double getQuadraY(Quadra q);

/**
 * @brief retorna a largura da quadra
 * @param q a quadra alvo
 * @return o valor da largura
 */
double getQuadraW(Quadra q);

/**
 * @brief retorna a altura da quadra
 * @param q a quadra alvo
 * @return o valor da altura
 */
double getQuadraH(Quadra q);

/**
 * @brief define as cores e espessura da borda da quadra
 * @param q a quadra alvo
 * @param cfill a cor de preenchimento
 * @param cstrk a cor da borda
 * @param sw a espessura da borda
 */
void setQuadraCores(Quadra q, char* cfill, char* cstrk, double sw);

/**
 * @brief retorna a cor de preenchimento da quadra
 * @param q a quadra alvo
 * @return a string com a cor de preenchimento
 */
char* getQuadraCfill(Quadra q);

/**
 * @brief retorna a cor da borda da quadra
 * @param q a quadra alvo
 * @return a string com a cor da borda
 */
char* getQuadraCstrk(Quadra q);

/**
 * @brief retorna a espessura da borda da quadra
 * @param q a quadra alvo
 * @return o valor da espessura da borda
 */
double getQuadraSw(Quadra q);

#endif