#include <stdlib.h>
#include <string.h>
#include "vertice.h"

struct vertice {
    char* id;
    double x;
    double y;
};

Vertice criarVertice(char* id, double x, double y) {
    Vertice v = (Vertice)malloc(sizeof(struct vertice));
    if (v == NULL) {
        return NULL;
    }
    
    v->id = (char*)malloc((strlen(id) + 1) * sizeof(char));
    if (v->id == NULL) {
        free(v);
        return NULL;
    }
    strcpy(v->id, id);
    
    v->x = x;
    v->y = y;
    return v;
}

void destruirVertice(Vertice v) {
    if (v != NULL) {
        if (v->id != NULL) {
            free(v->id);
        }
        free(v);
    }
}

char* getVerticeId(Vertice v) {
    if (v == NULL) return NULL;
    return v->id;
}

double getVerticeX(Vertice v) {
    if (v == NULL) return 0.0;
    return v->x;
}

double getVerticeY(Vertice v) {
    if (v == NULL) return 0.0;
    return v->y;
}