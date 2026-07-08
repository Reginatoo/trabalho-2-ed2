#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

typedef struct filaprioridade* FilaPrioridade;

/**
 * @brief cria uma fila de prioridade vazia com uma capacidade inicial
 * @param capacidade capacidade maxima inicial da fila
 * @return ponteiro para a fila de prioridade inicializada
 */
FilaPrioridade criarFilaPrioridade(int capacidade);

/**
 * @brief insere um elemento associado a uma prioridade na fila
 * @param fp ponteiro para a fila de prioridade
 * @param v_idx indice ou identificador do vertice/elemento
 * @param prioridade valor da prioridade do elemento
 */
void inserirFilaPrioridade(FilaPrioridade fp, int v_idx, double prioridade);

/**
 * @brief extrai o elemento que possui a menor prioridade na fila
 * @param fp ponteiro para a fila de prioridade
 * @return o indice do elemento de menor prioridade
 */
int extrairMinimoFilaPrioridade(FilaPrioridade fp);

/**
 * @brief diminui ou atualiza a prioridade de um elemento ja existente
 * @param fp ponteiro para a fila de prioridade
 * @param v_idx indice do elemento a ser atualizado
 * @param nova_prio novo valor menor de prioridade
 */
void diminuirPrioridadeFilaPrioridade(FilaPrioridade fp, int v_idx, double nova_prio);

/**
 * @brief verifica se a fila de prioridade esta vazia
 * @param fp ponteiro para a fila de prioridade
 * @return um numero inteiro indicando verdadeiro se vazia ou falso caso contrario
 */
int filaPrioridadeVazia(FilaPrioridade fp);

/**
 * @brief verifica se um determinado elemento ainda esta presente na fila
 * @param fp ponteiro para a fila de prioridade
 * @param v_idx indice do elemento procurado
 * @return um numero inteiro indicando verdadeiro se esta na fila ou falso caso contrario
 */
int estaNaFilaPrioridade(FilaPrioridade fp, int v_idx);

/**
 * @brief libera toda a memoria alocada para a estrutura da fila
 * @param fp ponteiro para a fila de prioridade a ser destruida
 */
void destruirFilaPrioridade(FilaPrioridade fp);

#endif