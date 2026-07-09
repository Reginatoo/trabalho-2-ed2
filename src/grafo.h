#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo* Grafo;
/**
 * @brief cria um grafo direcionado vazio com um numero inicial de vertices
 * @param numVertices numero inicial de vertices para dimensionar a estrutura
 * @return ponteiro para o grafo inicializado
 */
Grafo criarGrafo(int numVertices);

/**
 * @brief adiciona um vertice ao grafo
 * @param g ponteiro para o grafo
 * @param id identificador unico do vertice
 * @param x coordenada x da posicao do vertice
 * @param y coordenada y da posicao do vertice
 */
void adicionarVertice(Grafo g, const char* id, double x, double y);

/**
 * @brief adiciona uma aresta direcionada entre dois vertices
 * @param g ponteiro para o grafo
 * @param v_origem id do vertice de origem
 * @param v_destino id do vertice de destino
 * @param ldir cep da quadra ao lado direito
 * @param lesq cep da quadra ao lado esquerdo
 * @param cmp comprimento do segmento em metros
 * @param vm velocidade media em metros por segundo
 * @param nome nome da rua
 */
void adicionarAresta(Grafo g, const char* v_origem, const char* v_destino, double cmp, double vm, const char* nome);
/**
 * @brief atualiza a velocidade media das arestas dentro de uma regiao retangular
 * @param g ponteiro para o grafo
 * @param x coordenada x do inicio da regiao
 * @param y coordenada y do inicio da regiao
 * @param w largura da regiao
 * @param h altura da regiao
 * @param nova_vm nova velocidade media para as vias internas
 */
void atualizarVelocidadeRegiao(Grafo g, double x, double y, double w, double h, double nova_vm);

/**
 * @brief calcula as componentes conexas do grafo
 * @details desconsidera trechos com velocidade inferior ao limiar determinado
 * @param g ponteiro para o grafo
 * @param vl limiar de velocidade media
 * @param arqTxt ponteiro para o arquivo txt de saida
 * @param arqSvg ponteiro para o arquivo svg de saida
 */
void calcularComponentesConexos(Grafo g, double vl, void* arqTxt, void* arqSvg);

/**
 * @brief calcula a arvore geradora minima para expansao viaria
 * @details seleciona as vias lentas e aumenta a velocidade media
 * @param g ponteiro para o grafo
 * @param vl limiar de velocidade media para selecao
 * @param arqSvg ponteiro para o arquivo svg de saida
 */
void calcularExpansaoViaria(Grafo g, double vl, void* arqSvg);

/**
 * @brief encontra o caminho mais curto e o mais rapido usando dijkstra
 * @details escreve as instrucoes no txt e gera o percurso no svg
 * @param g ponteiro para o grafo
 * @param x_origem coordenada x de origem
 * @param y_origem coordenada y de origem
 * @param x_destino coordenada x de destino
 * @param y_destino coordenada y de destino
 * @param cor_curto cor do caminho mais curto
 * @param cor_rapido cor do caminho mais rapido
 * @param arqTxt ponteiro para o arquivo txt de destino
 * @param arqSvg ponteiro para o arquivo svg de destino
 */
void buscarMelhorTrajeto(Grafo g, double x_origem, double y_origem, double x_destino, double y_destino, const char* cor_curto, const char* cor_rapido, void* arqTxt, void* arqSvg);

/**
 * @brief libera a memoria alocada para o grafo
 * @param g ponteiro para o grafo
 */
void liberarGrafo(Grafo g);

#endif 