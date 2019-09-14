#ifndef EQUIPE_H
#define EQUIPE_H

#include <list>

class Equipe {
private:
    const int num_membros;
    int* idades;
    std::list<int>* listas_adjacencia;
public:
    Equipe(int n);
    ~Equipe();

    // Imprime o vetor de idades dos alunos da equipe.
    void imprimir_idades();

    // Imprime todas as arestas do grafo.
    void imprimir_arestas();

    // Atualiza a idade do aluno no índice `i`.
    void set_idade(int i, int n);

    // Insere uma aresta direcionada de `a` até `b`, sem verificar a existência de ciclos, laços ou
    // arestas paralelas.
    void inserir_aresta(int a, int b);
};

#endif
