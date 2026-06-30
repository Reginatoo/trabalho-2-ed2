#ifndef VIA_H
#define VIA_H

#include "grafo.h"

/**
 * @brief processa e le as informacoes de um arquivo ponto via povoando o grafo
 * @param g o grafo alvo
 * @param caminho o caminho do arquivo ponto via a ser lido
 * @return um numero inteiro indicando sucesso ou falha na leitura
 */
int viaLerArquivo(Grafo g, const char* caminho);

#endif