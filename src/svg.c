#include "svg.h"
#include <stdio.h>

FILE* svgCriar(const char* caminho) {
    if (caminho == NULL) return NULL;
    FILE* f = fopen(caminho, "w");
    if (f == NULL) return NULL;
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%%\" height=\"100%%\">\n");
    return f;
}

void svgFechar(FILE* f) {
    if (f == NULL) return;
    fprintf(f, "</svg>\n");
    fclose(f);
}

void svgDesenharQuadra(FILE* f, double x, double y, double w, double h, const char* cor_preenchimento, const char* cor_borda, double espessura_borda) {
    if (f == NULL) return;
    fprintf(f, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%f\" />\n",
            x, y, w, h, cor_preenchimento, cor_borda, espessura_borda);
}

void svgDesenharRetanguloOpaco(FILE* f, double x, double y, double w, double h, const char* cor, double opacidade) {
    if (f == NULL) return;
    fprintf(f, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" fill-opacity=\"%f\" />\n",
            x, y, w, h, cor, opacidade);
}

void svgDesenharLinha(FILE* f, double x1, double y1, double x2, double y2, const char* cor, double espessura) {
    if (f == NULL) return;
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%f\" />\n",
                x1, y1, x2, y2, cor, espessura);
}

void svgDesenharCaminho(FILE* f, const char* id, const char* dados_d, const char* cor, double espessura) {
    if (f == NULL || dados_d == NULL) return;
    if (id != NULL && id[0] != '\0') {
        fprintf(f, "<path id=\"%s\" d=\"%s\" stroke=\"%s\" stroke-width=\"%lf\" fill=\"none\" />\n",
                id, dados_d, cor, espessura);
    } else {
        fprintf(f, "<path d=\"%s\" stroke=\"%s\" stroke-width=\"%lf\" fill=\"none\" />\n",
                dados_d, cor, espessura);
    }
}

void svgDesenharCirculoAnimado(FILE* f, const char* id_caminho, const char* cor, double raio) {
    if (f == NULL || id_caminho == NULL) return;
    fprintf(f, "<circle r=\"%lf\" fill=\"%s\">\n", raio, cor);
    fprintf(f, "    <animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n");
    fprintf(f, "        <mpath href=\"#%s\" />\n", id_caminho);
    fprintf(f, "    </animateMotion>\n");
    fprintf(f, "</circle>\n");
}

void svgDesenharTexto(FILE* f, double x, double y, const char* texto, const char* cor) {
    if (f == NULL || texto == NULL) return;
    fprintf(f, "<text x=\"%lf\" y=\"%lf\" fill=\"%s\" font-family=\"sans-serif\" font-size=\"10\">%s</text>\n",
            x, y, cor, texto);
}