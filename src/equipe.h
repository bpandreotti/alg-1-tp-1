#ifndef EQUIPE_H
#define EQUIPE_H

#include <list>
#include <stack>

class Equipe {
private:
    const int num_membros;
    int* idades;
    std::list<int>* listas_adjacencia;

    bool busca_em_profundidade(int atual, int* visitado, std::stack<int>* ordenacao);

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

    // Procura por ciclos no grafo usando busca em profundidade. Caso algum ciclo seja encontrado,
    // retorna `true`.
    bool detectar_ciclos();

    // Executa o comando "SWAP". `a` e `b` são os índices, começando em 0, dos alunos A e B.
    void comando_swap(int a, int b);

    void comando_meeting();
};

#endif
