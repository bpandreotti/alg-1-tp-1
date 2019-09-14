#include "equipe.h"

#include <iostream>

Equipe::Equipe(int n) : num_membros(n) {
    this->idades = new int[n];
    this->listas_adjacencia = new std::list<int>[n];
}

Equipe::~Equipe() {
    delete[] this->idades;
    delete[] this->listas_adjacencia;
}

void Equipe::imprimir_idades() {
    std::cout << "[";
    for (int i = 0; i < this->num_membros - 1; i++) {
        std::cout << this->idades[i] << ", ";
    }
    std::cout << this->idades[this->num_membros - 1] << "]" << std::endl;
}

void Equipe::imprimir_arestas() {
    for (int i = 0; i < this->num_membros; i++) {
        for (int j : this->listas_adjacencia[i]) {
            std::cout << "(" << i << ", " << j << ")" << std::endl;
        }
    }
}

void Equipe::set_idade(int i, int n) {
    this->idades[i] = n;
}

void Equipe::inserir_aresta(int a, int b) {
    this->listas_adjacencia[a].push_back(b);
}
