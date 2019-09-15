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

bool Equipe::detectar_ciclos() {
    // Array que indica o estado de cada vértice. 0 indica que que o vértice não foi visitado; 1
    // indica que ele foi descoberto, mas ainda está sendo processado; 2 indica que o vértice já
    // foi visitado e seu processamento foi concluído.
    int* visitado = new int[this->num_membros];

    // No início, nenhum vértice foi visitado
    for (int i = 0; i < this->num_membros; i++)
        visitado[i] = 0;

    for (int i = 0; i < this->num_membros; i++) {
        if (visitado[i] != 0)
            continue;

        if (busca_em_profundidade(i, visitado))
            return true; // Ciclo encontrado!
    }

    return false;
}

bool Equipe::busca_em_profundidade(int atual, int* visitado) {
    // @WIP: Por ora, a busca em profundidade só está sendo usada para procurar ciclos. Futuramente
    // esse método fará mais coisas, então o tipo de retorno pode mudar.

    visitado[atual] = 1; // 1 indica que o vértice atual está sendo processado

    for (const int& vizinho : this->listas_adjacencia[atual]) {
        // Se encontrarmos um vértice marcado com 1, isso significa que existe um ciclo no grafo
        if (visitado[vizinho] == 1)
            return true;
        else if (visitado[vizinho] == 0)
            this->busca_em_profundidade(vizinho, visitado);
    }

    visitado[atual] = 2; // 2 indica que o vértice atual já foi completamente processado

    return false;
}
