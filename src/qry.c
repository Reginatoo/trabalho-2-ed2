#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "grafo.h"
#include "geo.h"
#include "svg.h"

typedef struct {
    char id[16];
    double x;
    double y;
    int ativo;
} Registador;

int buscarRegistador(Registador regs[], int num_regs, const char* id) {
    for (int i = 0; i < num_regs; i++) {
        if (regs[i].ativo && strcmp(regs[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

    void qryProcessar(const char* caminho, Grafo g, Geo geo, FILE* txt, FILE* svg) {
    if (caminho == NULL || g == NULL) return;
    
    FILE* arq_qry = fopen(caminho, "r");
   if (arq_qry == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo de consulta '%s'\n", caminho);
        return;
    }
    char comando[32];

    Registador regs[100]; 
    int num_regs = 0;

    while (fscanf(arq_qry, "%31s", comando) != EOF) {

        if (strcmp(comando, "@o?") == 0) {
            char reg[16], cep[64];
            char face;
            double num;
            
            if (fscanf(arq_qry, "%15s %63s %c %lf", reg, cep, &face, &num) == 4) {
                Quadra q = geoBuscarQuadra(geo, cep);
                if (q != NULL) {
                    double exato_x = getQuadraX(q);
                    double exato_y = getQuadraY(q);
                    double larg = getQuadraW(q);
                    double alt = getQuadraH(q);

                    switch (face) {
                        case 'S': 
                            exato_x += num;
                            break;
                        case 'N': 
                            exato_x += num;
                            exato_y += alt;
                            break;
                        case 'L': 
                            exato_y += num;
                            break;
                        case 'O': 
                            exato_x += larg;
                            exato_y += num;
                            break;
                    }
                    
                    strcpy(regs[num_regs].id, reg);
                    regs[num_regs].x = exato_x;
                    regs[num_regs].y = exato_y;
                    regs[num_regs].ativo = 1;
                    num_regs++;
                    
                    if (txt) fprintf(txt, "Endereco %s/%c/%.2f registado em %s (%.2f, %.2f)\n", cep, face, num, reg, exato_x, exato_y);
                
                 if (svg) {
                        svgDesenharLinhaTracejada(svg, exato_x, 0.0, exato_x, exato_y, "red", 1.0);
                        svgDesenharTexto(svg, exato_x + 2, 10.0, reg, "red");
                   }}  else if (txt) {
                    fprintf(txt, "Erro: CEP %s nao encontrado.\n", cep);
                }
            }
        }

        else if (strcmp(comando, "mvm") == 0) {
            double nova_vm, x, y, w, h;
            if (fscanf(arq_qry, "%lf %lf %lf %lf %lf", &nova_vm, &x, &y, &w, &h) == 5) {
                atualizarVelocidadeRegiao(g, x, y, w, h, nova_vm);
            }
        }
        else if (strcmp(comando, "regs") == 0) {
            double vl;
            if (fscanf(arq_qry, "%lf", &vl) == 1) {
                calcularComponentesConexos(g, vl, txt, svg);
            }
        } 
        else if (strcmp(comando, "exp") == 0) {
            double vl;
            if (fscanf(arq_qry, "%lf", &vl) == 1) {
                calcularExpansaoViaria(g, vl, svg);
            }
        } 
       else if (strcmp(comando, "p?") == 0) {
            char reg1[16], reg2[16];
            char cmc[32], cmr[32];
            
            if (fscanf(arq_qry, "%15s %15s %31s %31s", reg1, reg2, cmc, cmr) == 4) {
                int idx1 = buscarRegistador(regs, num_regs, reg1);
                int idx2 = buscarRegistador(regs, num_regs, reg2);
                
                if (idx1 != -1 && idx2 != -1) {
                    double x1 = regs[idx1].x;
                    double y1 = regs[idx1].y;
                    double x2 = regs[idx2].x;
                    double y2 = regs[idx2].y;

                    buscarMelhorTrajeto(g, x1, y1, x2, y2, cmc, cmr, txt, svg);
                } else {
                    if (txt) fprintf(txt, "Erro: Registador de origem ou destino nao encontrado no p?\n");
                }
            }
        } 

    } 
    fclose(arq_qry); 
}