#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "grafo.h"
#include "geo.h"

/**
 * @brief processa o arquivo de consultas qry aplicando os comandos no grafo e no geo
 * @param caminho o caminho completo do arquivo qry a ser lido
 * @param g o grafo da malha viaria
 * @param geo a estrutura com as quadras da cidade
 * @param txt o arquivo de texto para escrita dos relatorios das consultas
 * @param svg o arquivo svg para renderizacao visual das consultas
 */
void qryProcessar(const char* caminho, Grafo g, Geo geo, FILE* txt, FILE* svg);

#endif