#ifndef EQUIPE_H
#define EQUIPE_H

#include <list>

class Equipe {
private:
    const int num_membros;
    std::list<int>* listas_adjacencia;
public:
    Equipe(int n);
    ~Equipe();

    // Imprime todas as arestas do grafo.
    void imprimir_arestas();

    // Insere uma aresta direcionada de `a` até `b`, sem verificar a existência de ciclos, laços ou
    // arestas paralelas.
    void inserir_aresta(int a, int b);
};

#endif
