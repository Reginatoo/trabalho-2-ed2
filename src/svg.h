#ifndef SVG_H
#define SVG_H

#include <stdio.h>

/**
 * @brief abre um arquivo para escrita no formato svg
 * @param caminho o caminho completo do arquivo a ser criado
 * @return o ponteiro para o arquivo aberto ou null se falhar
 */
FILE* svgCriar(const char* caminho);

/**
 * @brief fecha o arquivo svg adicionando a tag de fechamento
 * @param f o arquivo svg ativo
 */
void svgFechar(FILE* f);

/**
 * @brief desenha um retangulo que representa uma quadra no svg
 * @param f o arquivo svg ativo
 * @param x a coordenada x do canto superior esquerdo
 * @param y a coordenada y do canto superior esquerdo
 * @param w a largura da quadra
 * @param h a altura da quadra
 * @param cor_preenchimento a cor de fundo do retangulo
 * @param cor_borda a cor do contorno do retangulo
 * @param espessura_borda a espessura da linha de contorno
 */
void svgDesenharQuadra(FILE* f, double x, double y, double w, double h, const char* cor_preenchimento, const char* cor_borda, double espessura_borda);

/**
 * @brief desenha um retangulo generico com opacidade usado para componentes conexos
 * @param f o arquivo svg ativo
 * @param x a coordenada x inicial
 * @param y a coordenada y inicial
 * @param w a largura do retangulo
 * @param h a altura do retangulo
 * @param cor a cor de preenchimento do retangulo
 * @param opacidade o valor de opacidade variando de zero a um
 */
void svgDesenharRetanguloOpaco(FILE* f, double x, double y, double w, double h, const char* cor, double opacidade);

/**
 * @brief desenha uma linha simples entre dois pontos no mapa viario
 * @param f o arquivo svg ativo
 * @param x1 coordenada x inicial
 * @param y1 coordenada y inicial
 * @param x2 coordenada x final
 * @param y2 coordenada y final
 * @param cor a cor da linha
 * @param espessura a espessura da linha
 */
void svgDesenharLinha(FILE* f, double x1, double y1, double x2, double y2, const char* cor, double espessura);

/**
 * @brief desenha uma linha tracejada entre dois pontos usada na marcacao de enderecos
 * @param f o arquivo svg ativo
 * @param x1 coordenada x inicial
 * @param y1 coordenada y inicial
 * @param x2 coordenada x final
 * @param y2 coordenada y final
 * @param cor a cor da linha
 * @param espessura a espessura da linha
 */
void svgDesenharLinhaTracejada(FILE* f, double x1, double y1, double x2, double y2, const char* cor, double espessura);

/**
 * @brief desenha um caminho complexo para guiar a animacao de percurso
 * @param f o arquivo svg ativo
 * @param id o identificador unico do path correspondente
 * @param dados_d a string formatada contendo os comandos m e l do percurso
 * @param cor a cor da linha do caminho
 * @param espessura a espessura da linha do caminho
 */
void svgDesenharCaminho(FILE* f, const char* id, const char* dados_d, const char* cor, double espessura);

/**
 * @brief desenha um circulo com animacao ao longo de um caminho svg
 * @param f o arquivo svg ativo
 * @param id_caminho o identificador unico do path correspondente
 * @param cor a cor do circulo animado
 * @param raio o raio do circulo animado
 */
void svgDesenharCirculoAnimado(FILE* f, const char* id_caminho, const char* cor, double raio);

/**
 * @brief adiciona uma tag de texto simples ou placa de identificacao no mapa
 * @param f o arquivo svg ativo
 * @param x a coordenada x de ancoragem do texto
 * @param y a coordenada y de ancoragem do texto
 * @param texto o conteudo textual a ser exibido
 * @param cor a cor do texto
 */
void svgDesenharTexto(FILE* f, double x, double y, const char* texto, const char* cor);

#endif