#include <stdlib.h>
#include <string.h>
#include "quadra.h"

struct quadra {
    char* cep;
    double x;
    double y;
    double w;
    double h;
    char* cfill;
    char* cstrk;
    double sw;
};

QQuadra criarQuadra(char* cep, double x, double y, double w, double h) {
    Quadra q = (Quadra)malloc(sizeof(struct quadra));
    if (q == NULL) {
        return NULL;
    }
    
    q->cep = (char*)malloc((strlen(cep) + 1) * sizeof(char));
    if (q->cep == NULL) {
        free(q);
        return NULL;
    }
    strcpy(q->cep, cep);
    
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    
    q->cfill = NULL;
    q->cstrk = NULL;
    q->sw = 1.0;
    
    return q;
}

void destruirQuadra(Quadra q) {
    if (q != NULL) {
        if (q->cep != NULL) free(q->cep);
        if (q->cfill != NULL) free(q->cfill);
        if (q->cstrk != NULL) free(q->cstrk);
        free(q);
    }
}

char* getQuadraCep(Quadra q) {
    if (q == NULL) return NULL;
    return q->cep;
}

double getQuadraX(Quadra q) {
    if (q == NULL) return 0.0;
    return q->x;
}

double getQuadraY(Quadra q) {
    if (q == NULL) return 0.0;
    return q->y;
}

double getQuadraW(Quadra q) {
    if (q == NULL) return 0.0;
    return q->w;
}

double getQuadraH(Quadra q) {
    if (q == NULL) return 0.0;
    return q->h;
}

void setQuadraCores(Quadra q, char* cfill, char* cstrk, double sw) {
    if (q == NULL) return;
    
    if (q->cfill != NULL) free(q->cfill);
    if (q->cstrk != NULL) free(q->cstrk);
    
    if (cfill != NULL) {
        q->cfill = (char*)malloc((strlen(cfill) + 1) * sizeof(char));
        if (q->cfill != NULL) strcpy(q->cfill, cfill);
    } else {
        q->cfill = NULL;
    }
    
    if (cstrk != NULL) {
        q->cstrk = (char*)malloc((strlen(cstrk) + 1) * sizeof(char));
        if (q->cstrk != NULL) strcpy(q->cstrk, cstrk);
    } else {
        q->cstrk = NULL;
    }
    
    q->sw = sw;
}

char* getQuadraCfill(Quadra q) {
    if (q == NULL) return NULL;
    return q->cfill;
}

char* getQuadraCstrk(Quadra q) {
    if (q == NULL) return NULL;
    return q->cstrk;
}

double getQuadraSw(Quadra q) {
    if (q == NULL) return 1.0;
    return q->sw;
}