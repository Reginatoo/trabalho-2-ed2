#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "quadra.h"

struct geo {
    Quadra* quadras;
    int capacidade;
    int quantidade;
    char cor_preenchimento[64];
    char cor_borda[64];
    double espessura_borda;
};

Geo criarGeo(void) {
    Geo g = (Geo)malloc(sizeof(struct geo));
    g->capacidade = 10;
    g->quantidade = 0;
    g->quadras = (Quadra*)malloc(g->capacidade * sizeof(Quadra));
    strcpy(g->cor_preenchimento, "white");
    strcpy(g->cor_borda, "black");
    g->espessura_borda = 1.0;
    return g;
}

void destruirGeo(Geo g) {
    if (g == NULL) return;
    for (int i = 0; i < g->quantidade; i++) {
        destruirQuadra(g->quadras[i]);
    }
    free(g->quadras);
    free(g);
}

void geoAdicionarQuadra(Geo g, Quadra q) {
    if (g == NULL || q == NULL) return;
    if (g->quantidade >= g->capacidade) {
        g->capacidade *= 2;
        g->quadras = (Quadra*)realloc(g->quadras, g->capacidade * sizeof(Quadra));
    }
    g->quadras[g->quantidade] = q;
    g->quantidade++;
}

Quadra geoBuscarQuadra(Geo g, char* cep) {
    if (g == NULL || cep == NULL) return NULL;
    for (int i = 0; i < g->quantidade; i++) {
        if (strcmp(getQuadraCep(g->quadras[i]), cep) == 0) {
            return g->quadras[i];
        }
    }
    return NULL;
}

int geoLerArquivo(Geo g, char* caminho) {
    if (g == NULL || caminho == NULL) return 0;
    FILE* arq = fopen(caminho, "r");
    if (arq == NULL) return 0;
    char comando[32];
    while (fscanf(arq, "%s", comando) != EOF) {
        if (strcmp(comando, "cq") == 0) {
            fscanf(arq, "%s %s %lf", g->cor_preenchimento, g->cor_borda, &g->espessura_borda);
        } else if (strcmp(comando, "q") == 0) {
            char cep[64];
            double x, y, w, h;
            fscanf(arq, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criarQuadra(cep, x, y, w, h);
            setQuadraCores(q, g->cor_preenchimento, g->cor_borda, g->espessura_borda);
            geoAdicionarQuadra(g, q);
        }
    }
    fclose(arq);
    return 1;
}