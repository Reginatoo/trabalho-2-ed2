#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "grafo.h"
#include "filaprioridade.h"

typedef struct aresta {
    char* v_destino;
    double cmp;
    double vm;
    double vm_original;
    char* nome;
    struct aresta* proximo;
}* Aresta;

typedef struct {
    char* id;
    double x;
    double y;
    Aresta adjacentes;
} VerticeInterno;

struct grafo {
    VerticeInterno* vertices;
    int capacidade;
    int quantidade;
};

typedef struct {
    int u, v;
    double peso;
    Aresta ref;
} ArestaAux;

int compararArestasAux(const void* a, const void* b) {
    double diff = ((ArestaAux*)a)->peso - ((ArestaAux*)b)->peso;
    return (diff > 0) - (diff < 0);
}

typedef struct {
    int* pai;
    int* rank;
} UnionFind;

static UnionFind* criarUF(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->pai = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) { 
        uf->pai[i] = i; 
        uf->rank[i] = 0; 
    }
    return uf;
}

static int encontrarUF(UnionFind* uf, int i) {
    if (uf->pai[i] == i) return i;
    return uf->pai[i] = encontrarUF(uf, uf->pai[i]);
}

static void uniaoUF(UnionFind* uf, int x, int y) {
    int raiz_x = encontrarUF(uf, x);
    int raiz_y = encontrarUF(uf, y);
    if (raiz_x != raiz_y) {
        if (uf->rank[raiz_x] < uf->rank[raiz_y]) uf->pai[raiz_x] = raiz_y;
        else if (uf->rank[raiz_x] > uf->rank[raiz_y]) uf->pai[raiz_y] = raiz_x;
        else { 
            uf->pai[raiz_y] = raiz_x; 
            uf->rank[raiz_x]++; 
        }
    }
}

static void destruirUF(UnionFind* uf) { 
    free(uf->pai); 
    free(uf->rank); 
    free(uf); 
}

Grafo criarGrafo(int numVertices) {
    if (numVertices <= 0) numVertices = 10;
    
    Grafo g = (Grafo)malloc(sizeof(struct grafo));
    if (g == NULL) return NULL;
    
    g->capacidade = numVertices;
    g->quantidade = 0;
    g->vertices = (VerticeInterno*)malloc(g->capacidade * sizeof(VerticeInterno));
    
    if (g->vertices == NULL) {
        free(g);
        return NULL;
    }
    
    return g;
}

void adicionarVertice(Grafo g, const char* id, double x, double y) {
    if (g == NULL || id == NULL) return;
    
    if (g->quantidade >= g->capacidade) {
        int nova_cap = g->capacidade * 2;
        VerticeInterno* temp = (VerticeInterno*)realloc(g->vertices, nova_cap * sizeof(VerticeInterno));
        if (temp == NULL) return;
        g->vertices = temp;
        g->capacidade = nova_cap;
    }
    
    char* id_copia = (char*)malloc((strlen(id) + 1) * sizeof(char));
    if (id_copia == NULL) return;
    strcpy(id_copia, id);
    
    g->vertices[g->quantidade].id = id_copia;
    g->vertices[g->quantidade].x = x;
    g->vertices[g->quantidade].y = y;
    g->vertices[g->quantidade].adjacentes = NULL;
    g->quantidade++;
}

static int buscarIndiceVertice(Grafo g, const char* id) {
    for (int i = 0; i < g->quantidade; i++) {
        if (strcmp(g->vertices[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void adicionarAresta(Grafo g, const char* v_origem, const char* v_destino, double cmp, double vm, const char* nome) {
    if (g == NULL || v_origem == NULL || v_destino == NULL) return;
    
    int idx_origem = buscarIndiceVertice(g, v_origem);
    if (idx_origem == -1) return;
    
    Aresta nova = (Aresta)malloc(sizeof(struct aresta));
    if (nova == NULL) return;
    
    nova->v_destino = (char*)malloc((strlen(v_destino) + 1) * sizeof(char));
    nova->nome = nome ? (char*)malloc((strlen(nome) + 1) * sizeof(char)) : NULL;
    
    if (nova->v_destino == NULL) {
        if (nova->nome) free(nova->nome);
        free(nova);
        return;
    }
    
    strcpy(nova->v_destino, v_destino);
    if (nome) strcpy(nova->nome, nome);
    
    nova->cmp = cmp;
    nova->vm = vm;
    nova->vm_original = vm;
    
    nova->proximo = g->vertices[idx_origem].adjacentes;
    g->vertices[idx_origem].adjacentes = nova;
}

void atualizarVelocidadeRegiao(Grafo g, double x, double y, double w, double h, double nova_vm) {
    if (g == NULL) return;
    
    for (int i = 0; i < g->quantidade; i++) {
        double vx = g->vertices[i].x;
        double vy = g->vertices[i].y;
        
        if (vx >= x && vx <= (x + w) && vy >= y && vy <= (y + h)) {
            Aresta atual = g->vertices[i].adjacentes;
            while (atual != NULL) {
                atual->vm = nova_vm;
                atual = atual->proximo;
            }
        }
    }
}

void liberarGrafo(Grafo g) {
    if (g == NULL) return;
    
    for (int i = 0; i < g->quantidade; i++) {
        if (g->vertices[i].id) free(g->vertices[i].id);
        
        Aresta aerial = g->vertices[i].adjacentes;
        while (aerial != NULL) {
            Aresta prox = aerial->proximo;
            if (aerial->v_destino) free(aerial->v_destino);
            if (aerial->nome) free(aerial->nome);
            free(aerial);
            aerial = prox;
        }
    }
    free(g->vertices);
    free(g);
}

static void tarjanDFS(Grafo g, int u, double vl, int* discovery, int* low, int* pilha, int* topo_pilha, int* no_stack, int* tempo, int* componentes, FILE* fSvg) {
    discovery[u] = low[u] = ++(*tempo);
    pilha[++(*topo_pilha)] = u;
    no_stack[u] = 1;

    Aresta atual = g->vertices[u].adjacentes;
    while (atual != NULL) {
        if (atual->vm >= vl) {
            int v = buscarIndiceVertice(g, atual->v_destino);
            if (v != -1) {
                if (discovery[v] == -1) {
                    tarjanDFS(g, v, vl, discovery, low, pilha, topo_pilha, no_stack, tempo, componentes, fSvg);
                    if (low[v] < low[u]) low[u] = low[v];
                } else if (no_stack[v]) {
                    if (discovery[v] < low[u]) low[u] = discovery[v];
                }
            }
        }
        atual = atual->proximo;
    }

    if (low[u] == discovery[u]) {
        (*componentes)++;
        
        double min_x = DBL_MAX, min_y = DBL_MAX;
        double max_x = -DBL_MAX, max_y = -DBL_MAX;
        int contem_nos = 0;

        int w = -1;
        while (w != u) {
            w = pilha[(*topo_pilha)--];
            no_stack[w] = 0;
            
            double wx = g->vertices[w].x;
            double wy = g->vertices[w].y;
            if (wx < min_x) min_x = wx;
            if (wy < min_y) min_y = wy;
            if (wx > max_x) max_x = wx;
            if (wy > max_y) max_y = wy;
            contem_nos = 1;
        }

        if (fSvg && contem_nos) {
            const char* cores[] = {"red", "green", "blue", "orange", "purple", "cyan", "magenta"};
            const char* cor_atual = cores[*componentes % 7];
            double bb_w = (max_x - min_x) < 10 ? 15 : (max_x - min_x + 10);
            double bb_h = (max_y - min_y) < 10 ? 15 : (max_y - min_y + 10);
            
            fprintf(fSvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" fill-opacity=\"0.5\" stroke=\"%s\" stroke-width=\"1\" />\n",
                    min_x - 5, min_y - 5, bb_w, bb_h, cor_atual, cor_atual);
        }
    }
}

void calcularComponentesConexos(Grafo g, double vl, void* arqTxt, void* arqSvg) {
    if (g == NULL) return;
    FILE* fTxt = (FILE*)arqTxt;
    FILE* fSvg = (FILE*)arqSvg;

    int* discovery = (int*)malloc(g->quantidade * sizeof(int));
    int* low = (int*)malloc(g->quantidade * sizeof(int));
    int* no_stack = (int*)malloc(g->quantidade * sizeof(int));
    int* pilha = (int*)malloc(g->quantidade * sizeof(int));
    int topo_pilha = -1;
    
    for (int i = 0; i < g->quantidade; i++) { 
        discovery[i] = -1; 
        low[i] = -1; 
        no_stack[i] = 0; 
    }

    int tempo = 0;
    int componentes_totais = 0;

    for (int i = 0; i < g->quantidade; i++) {
        if (discovery[i] == -1) {
            tarjanDFS(g, i, vl, discovery, low, pilha, &topo_pilha, no_stack, &tempo, &componentes_totais, fSvg);
        }
    }

    if (fTxt) {
        fprintf(fTxt, "Componentes conexos: %d\n", componentes_totais);
    }

    free(discovery); 
    free(low); 
    free(no_stack); 
    free(pilha);
}

void calcularExpansaoViaria(Grafo g, double vl, void* arqSvg) {
    if (g == NULL || arqSvg == NULL) return;
    FILE* fSvg = (FILE*)arqSvg;

    int total_arestas = 0;
    for (int i = 0; i < g->quantidade; i++) {
        Aresta atual = g->vertices[i].adjacentes;
        while (atual != NULL) {
            if (atual->vm < vl) total_arestas++;
            atual = atual->proximo;
        }
    }

    if (total_arestas == 0) return;

    ArestaAux* lista = (ArestaAux*)malloc(total_arestas * sizeof(ArestaAux));
    int idx = 0;
    for (int i = 0; i < g->quantidade; i++) {
        Aresta atual = g->vertices[i].adjacentes;
        while (atual != NULL) {
            if (atual->vm < vl) {
                lista[idx].u = i;
                lista[idx].v = buscarIndiceVertice(g, atual->v_destino);
                lista[idx].peso = atual->cmp;
                lista[idx].ref = atual;
                idx++;
            }
            atual = atual->proximo;
        }
    }

    qsort(lista, total_arestas, sizeof(ArestaAux), compararArestasAux);

    UnionFind* uf = criarUF(g->quantidade);

    for (int i = 0; i < total_arestas; i++) {
        int u = lista[i].u;
        int v = lista[i].v;
        if (v != -1 && encontrarUF(uf, u) != encontrarUF(uf, v)) {
            uniaoUF(uf, u, v);
            
            if (lista[i].ref) {
                lista[i].ref->vm *= 1.5;
            }
            
            fprintf(fSvg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"4\" />\n",
                    g->vertices[u].x, g->vertices[u].y, g->vertices[v].x, g->vertices[v].y);
        }
    }

    destruirUF(uf);
    free(lista);
}

static int encontrarVerticeMaisProximo(Grafo g, double x, double y) {
    int idx_min = -1;
    double dist_min = DBL_MAX;
    for (int i = 0; i < g->quantidade; i++) {
        double dx = g->vertices[i].x - x;
        double dy = g->vertices[i].y - y;
        double d = sqrt(dx * dx + dy * dy);
        if (d < dist_min) { 
            dist_min = d; 
            idx_min = i; 
        }
    }
    return idx_min;
}

static int executarDijkstra(Grafo g, int origem, int destino, int* antecessor, double* custo, int modo_tempo) {
    for (int i = 0; i < g->quantidade; i++) { 
        custo[i] = DBL_MAX; 
        antecessor[i] = -1; 
    }
    custo[origem] = 0.0;

    FilaPrioridade fp = criarFilaPrioridade(g->quantidade);
    for (int i = 0; i < g->quantidade; i++) {
        inserirFilaPrioridade(fp, i, custo[i]);
    }

    while (!filaPrioridadeVazia(fp)) {
        int u = extrairMinimoFilaPrioridade(fp);
        if (u == -1 || custo[u] == DBL_MAX) break;
        if (u == destino) break;

        Aresta atual = g->vertices[u].adjacentes;
        while (atual != NULL) {
            int v = buscarIndiceVertice(g, atual->v_destino);
            if (v != -1 && estaNaFilaPrioridade(fp, v)) {
                double peso = modo_tempo ? (atual->cmp / (atual->vm > 0 ? atual->vm : 1.0)) : atual->cmp;
                if (custo[u] + peso < custo[v]) {
                    custo[v] = custo[u] + peso;
                    antecessor[v] = u;
                    diminuirPrioridadeFilaPrioridade(fp, v, custo[v]);
                }
            }
            atual = atual->proximo;
        }
    }
    
    int alcancavel = (antecessor[destino] != -1 || origem == destino);
    destruirFilaPrioridade(fp);
    return alcancavel;
}

static void gravarCaminho(Grafo g, int* antecessor, int origem, int destino, FILE* fTxt, FILE* fSvg, const char* cor, int id_animacao) {
    if (destino == -1 || antecessor[destino] == -1) return;

    int* caminho = (int*)malloc(g->quantidade * sizeof(int));
    int tam = 0;
    int atual = destino;
    while (atual != -1) { 
        caminho[tam++] = atual; 
        atual = antecessor[atual]; 
    }

    if (fTxt) fprintf(fTxt, "Trajeto:\n");
    
    if (fSvg) {
        fprintf(fSvg, "<path id=\"caminhoAnimado%d\" d=\"M %f,%f", id_animacao, g->vertices[caminho[tam-1]].x, g->vertices[caminho[tam-1]].y);
    }

    for (int i = tam - 1; i > 0; i--) {
        int u = caminho[i];
        int v = caminho[i - 1];
        
        if (fSvg) {
            fprintf(fSvg, " L %f,%f", g->vertices[v].x, g->vertices[v].y);
        }

        Aresta a = g->vertices[u].adjacentes;
        const char* rua = "Via compartilhada";
        while (a != NULL) {
            if (buscarIndiceVertice(g, a->v_destino) == v) { 
                rua = a->nome ? a->nome : rua; 
                break; 
            }
            a = a->proximo;
        }
        
        if (fTxt) {
            fprintf(fTxt, "Siga por %s de %s ate %s\n", rua, g->vertices[u].id, g->vertices[v].id);
        }
    }

    if (fSvg) {
        fprintf(fSvg, "\" fill=\"none\" stroke=\"%s\" stroke-width=\"3\" />\n", cor);
        
        fprintf(fSvg, "<circle cx=\"0\" cy=\"0\" r=\"5\" fill=\"%s\">\n", cor);
        fprintf(fSvg, "  <animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n");
        fprintf(fSvg, "    <mpath xlink:href=\"#caminhoAnimado%d\"/>\n", id_animacao);
        fprintf(fSvg, "  </animateMotion>\n");
        fprintf(fSvg, "</circle>\n");
    }

    free(caminho);
}

void buscarMelhorTrajeto(Grafo g, double x_origem, double y_origem, double x_destino, double y_destino, const char* cor_curto, const char* cor_rapido, void* arqTxt, void* arqSvg) {
    if (g == NULL) return;
    FILE* fTxt = (FILE*)arqTxt;
    FILE* fSvg = (FILE*)arqSvg;

    int origem = encontrarVerticeMaisProximo(g, x_origem, y_origem);
    int destino = encontrarVerticeMaisProximo(g, x_destino, y_destino);

    if (origem == -1 || destino == -1) {
        if (fTxt) fprintf(fTxt, "Destino inacessivel\n");
        return;
    }

    int* antecessor = (int*)malloc(g->quantidade * sizeof(int));
    double* custo = (double*)malloc(g->quantidade * sizeof(double));

    if (fTxt) fprintf(fTxt, "--- CAMINHO MAIS CURTO ---\n");
    int possivel_curto = executarDijkstra(g, origem, destino, antecessor, custo, 0);
    if (possivel_curto) {
        gravarCaminho(g, antecessor, origem, destino, fTxt, fSvg, cor_curto ? cor_curto : "blue", 1);
    } else if (fTxt) {
        fprintf(fTxt, "Destino inacessivel\n");
    }

    if (fTxt) fprintf(fTxt, "\n--- CAMINHO MAIS RAPIDO ---\n");
    int possivel_rapido = executarDijkstra(g, origem, destino, antecessor, custo, 1);
    if (possivel_rapido) {
        gravarCaminho(g, antecessor, origem, destino, fTxt, fSvg, cor_rapido ? cor_rapido : "red", 2);
    } else if (fTxt && !possivel_curto) {
        fprintf(fTxt, "Destino inacessivel\n");
    }

    if (fSvg && (possivel_curto || possivel_rapido)) {
        fprintf(fSvg, "<circle cx=\"%f\" cy=\"%f\" r=\"10\" fill=\"white\" stroke=\"black\" stroke-width=\"2\" />\n", x_origem, y_origem);
        fprintf(fSvg, "<text x=\"%f\" y=\"%f\" font-size=\"12\" text-anchor=\"middle\" dy=\"4\" font-weight=\"bold\">I</text>\n", x_origem, y_origem);
        
        fprintf(fSvg, "<circle cx=\"%f\" cy=\"%f\" r=\"10\" fill=\"white\" stroke=\"black\" stroke-width=\"2\" />\n", x_destino, y_destino);
        fprintf(fSvg, "<text x=\"%f\" y=\"%f\" font-size=\"12\" text-anchor=\"middle\" dy=\"4\" font-weight=\"bold\">F</text>\n", x_destino, y_destino);
    }

    free(antecessor); 
    free(custo);
}