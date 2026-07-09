#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include "grafo.h"
#include "via.h"
#include "geo.h"
#include "qry.h"
#include "svg.h"

void concatenarCaminho(char *resultado, const char *dir, const char *arquivo) {
    if (dir && strlen(dir) > 0) {
        if (dir[strlen(dir) - 1] == '/') {
            sprintf(resultado, "%s%s", dir, arquivo);
        } else {
            sprintf(resultado, "%s/%s", dir, arquivo);
        }
    } else {
        strcpy(resultado, arquivo);
    }
}

void obterNomeBase(char *resultado, const char *caminho) {
    const char *ultimoSl = strrchr(caminho, '/');
    const char *inicio = ultimoSl ? ultimoSl + 1 : caminho;
    const char *ponto = strrchr(inicio, '.');
    if (ponto) {
        size_t len = ponto - inicio;
        strncpy(resultado, inicio, len);
        resultado[len] = '\0';
    } else {
        strcpy(resultado, inicio);
    }
}

int main(int argc, char *argv[]) {
    char *bed = NULL;
    char *geo_nome = NULL;
    char *bsd = NULL;
    char *qry_nome = NULL;
    char *via_nome = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "e:f:o:q:v:")) != -1) {
        switch (opt) {
            case 'e': bed = optarg; break;
            case 'f': geo_nome = optarg; break;
            case 'o': bsd = optarg; break;
            case 'q': qry_nome = optarg; break;
            case 'v': via_nome = optarg; break;
            default: return 1;
        }
    }

    if (geo_nome == NULL || bsd == NULL) {
        return 1;
    }

    char caminho_geo[512];
    char caminho_via[512];
    char caminho_qry[512];

    concatenarCaminho(caminho_geo, bed, geo_nome);

    if (via_nome) {
        concatenarCaminho(caminho_via, bed, via_nome);
    }
    if (qry_nome) {
        concatenarCaminho(caminho_qry, bed, qry_nome);
    }

    char geo_base[256];
    obterNomeBase(geo_base, geo_nome);

    Grafo g = criarGrafo(15000);
    Geo geo = criarGeo();

    if (via_nome) {
        if (!viaLerArquivo(g, caminho_via)) {
            destruirGeo(geo);
            liberarGrafo(g);
            return 1;
        }
    }

    if (!geoLerArquivo(geo, caminho_geo)) {
        destruirGeo(geo);
        liberarGrafo(g);
        return 1;
    }

    if (qry_nome == NULL) {
        char svg_inicial[512];
        concatenarCaminho(svg_inicial, bsd, geo_base);
        strcat(svg_inicial, ".svg");

        FILE *f_svg = svgCriar(svg_inicial);
        if (f_svg) {
            geoDesenhar(geo, f_svg);
            svgFechar(f_svg);
        }
    } else {
        char qry_base[256];
        obterNomeBase(qry_base, qry_nome);

        char sufixo[512];
        sprintf(sufixo, "%s-%s", geo_base, qry_base);

        char svg_final[512];
        char txt_final[512];

        concatenarCaminho(svg_final, bsd, sufixo);
        strcat(svg_final, ".svg");

        concatenarCaminho(txt_final, bsd, sufixo);
        strcat(txt_final, ".txt");

        FILE *f_txt = fopen(txt_final, "w");
        FILE *f_svg = svgCriar(svg_final);
        if (f_svg) {
            geoDesenhar(geo, f_svg);
        }

        qryProcessar(caminho_qry, g, geo, f_txt, f_svg);

        if (f_svg) {
            svgFechar(f_svg);
           
        }
        if (f_txt) {
            fclose(f_txt);
        }
    }

    destruirGeo(geo);
    liberarGrafo(g);

    return 0;
}