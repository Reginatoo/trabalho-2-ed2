#include <stdlib.h>
#include <float.h>
#include "filaprioridade.h"

typedef struct {
    int v_idx;
    double prioridade;
    int presente;
} Elemento;

struct filaprioridade {
    Elemento* itens;
    int capacidade;
    int tamanho;
};

FilaPrioridade criarFilaPrioridade(int capacidade) {
    if (capacidade <= 0) capacidade = 10;
    
    FilaPrioridade fp = (FilaPrioridade)malloc(sizeof(struct filaprioridade));
    if (fp == NULL) return NULL;
    
    fp->capacidade = capacidade;
    fp->tamanho = 0;
    fp->itens = (Elemento*)malloc(capacidade * sizeof(Elemento));
    
    if (fp->itens == NULL) {
        free(fp);
        return NULL;
    }
    
    for (int i = 0; i < capacidade; i++) {
        fp->itens[i].v_idx = -1;
        fp->itens[i].prioridade = DBL_MAX;
        fp->itens[i].presente = 0;
    }
    
    return fp;
}

void inserirFilaPrioridade(FilaPrioridade fp, int v_idx, double prioridade) {
    if (fp == NULL || v_idx < 0 || v_idx >= fp->capacidade) return;
    
    fp->itens[v_idx].v_idx = v_idx;
    fp->itens[v_idx].prioridade = prioridade;
    
    if (fp->itens[v_idx].presente == 0) {
        fp->itens[v_idx].presente = 1;
        fp->tamanho++;
    }
}

int extrairMinimoFilaPrioridade(FilaPrioridade fp) {
    if (fp == NULL || fp->tamanho == 0) return -1;
    
    int idx_minimo = -1;
    double menor_prioridade = DBL_MAX;
    
    for (int i = 0; i < fp->capacidade; i++) {
        if (fp->itens[i].presente && fp->itens[i].prioridade < menor_prioridade) {
            menor_prioridade = fp->itens[i].prioridade;
            idx_minimo = i;
        }
    }
    
    if (idx_minimo != -1) {
        fp->itens[idx_minimo].presente = 0;
        fp->tamanho--;
        return fp->itens[idx_minimo].v_idx;
    }
    
    return -1;
}

void diminuirPrioridadeFilaPrioridade(FilaPrioridade fp, int v_idx, double nova_prio) {
    if (fp == NULL || v_idx < 0 || v_idx >= fp->capacidade) return;
    
    if (fp->itens[v_idx].presente && nova_prio < fp->itens[v_idx].prioridade) {
        fp->itens[v_idx].prioridade = nova_prio;
    }
}

int filaPrioridadeVazia(FilaPrioridade fp) {
    if (fp == NULL) return 1;
    return fp->tamanho == 0;
}

int estaNaFilaPrioridade(FilaPrioridade fp, int v_idx) {
    if (fp == NULL || v_idx < 0 || v_idx >= fp->capacidade) return 0;
    return fp->itens[v_idx].presente;
}

void destruirFilaPrioridade(FilaPrioridade fp) {
    if (fp == NULL) return;
    free(fp->itens);
    free(fp);
}