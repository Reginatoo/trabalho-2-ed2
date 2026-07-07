#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "grafo.h"
#include "geo.h"
.
void qryProcessar(const char* caminho, Grafo g, Geo geo, FILE* txt, FILE* svg) {
    if (caminho == NULL || g == NULL) return;

    FILE* arq_qry = fopen(caminho, "r");
    if (arq_qry == NULL) return;

    char comando[32];

    while (fscanf(arq_qry, "%31s", comando) != EOF) {
        if (strcmp(comando, "v") == 0) {
            double x, y, w, h, nova_vm;
            if (fscanf(arq_qry, "%lf %lf %lf %lf %lf", &x, &y, &w, &h, &nova_vm) == 5) {
                atualizarVelocidadeRegiao(g, x, y, w, h, nova_vm);
            }
        } 
        else if (strcmp(comando, "regs") == 0) {
            double vl;
            char lixo_txt[256];
            char lixo_svg[256];
            if (fscanf(arq_qry, "%lf %255s %255s", &vl, lixo_txt, lixo_svg) == 3) {
                calcularComponentesConexos(g, vl, txt, svg);
            }
        } 
        else if (strcmp(comando, "exp") == 0) {
            double vl;
            char lixo_svg[256];
            if (fscanf(arq_qry, "%lf %255s", &vl, lixo_svg) == 2) {
                calcularExpansaoViaria(g, vl, svg);
            }
        } 
        else if (strcmp(comando, "p?") == 0) {
            double x1, y1, x2, y2;
            char cmc[32], cmr[32];
            char lixo_txt[256];
            char lixo_svg[256];
            if (fscanf(arq_qry, "%lf %lf %lf %lf %31s %31s %255s %255s", 
                       &x1, &y1, &x2, &y2, cmc, cmr, lixo_txt, lixo_svg) == 8) {
                buscarMelhorTrajeto(g, x1, y1, x2, y2, cmc, cmr, txt, svg);
            }
        }
    }

    fclose(arq_qry);
}