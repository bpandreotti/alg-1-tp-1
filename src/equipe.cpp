#include "equipe.h"

#include <iostream>

Equipe::Equipe(int n) : num_membros(n) {
    this->listas_adjacencia = new std::list<int>[n];
}

Equipe::~Equipe() {
    delete[] this->listas_adjacencia;
}

void Equipe::imprimir_arestas() {
    for (int i = 0; i < this->num_membros; i++) {
        for (int j : this->listas_adjacencia[i]) {
            std::cout << "(" << i << ", " << j << ")" << std::endl;
        }
    }
}

void Equipe::inserir_aresta(int a, int b) {
    this->listas_adjacencia[a].push_back(b);
}
