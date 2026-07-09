#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "via.h"
#include "grafo.h"

int viaLerArquivo(Grafo g, const char* caminho) {
    if (g == NULL || caminho == NULL) return 0;
    FILE* arq = fopen(caminho, "r");
    if (arq == NULL) {
    fprintf(stderr, "Erro: nao foi possivel abrir o arquivo de vias '%s'\n", caminho);
    return 0;
    }
    int nv;
    if (fscanf(arq, "%d", &nv) == EOF) {
        fclose(arq);
        return 0;
    }

    char tipo;
    while (fscanf(arq, " %c", &tipo) != EOF) {
        if (tipo == 'v') {
            char id[64];
            double x, y;
            fscanf(arq, "%s %lf %lf", id, &x, &y);
            adicionarVertice(g, id, x, y);
        } else if (tipo == 'e') {
            char i[64], j[64], ldir[64], lesq[64];
            double cmp, vm;
            char nome[256];
            
            fscanf(arq, "%s %s %s %s %lf %lf", i, j, ldir, lesq, &cmp, &vm);
            
            int c = fgetc(arq);
            while (c == ' ' || c == '\t') {
                c = fgetc(arq);
            }
            
            int idx = 0;
            while (c != '\n' && c != '\r' && c != EOF) {
                nome[idx++] = (char)c;
                c = fgetc(arq);
            }
            nome[idx] = '\0';
            
            adicionarAresta(g, i, j, cmp, vm, nome);
        }
    }

    fclose(arq);
    return 1;
}