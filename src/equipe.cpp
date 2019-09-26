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

        // Passamos `nullptr` para indicar ao método `Equipe::busca_em_profundidade` que não
        // estamos interessados na ordenação topológica.
        if (busca_em_profundidade(i, visitado, nullptr))
            return true; // Ciclo encontrado!
    }

    delete[] visitado;
    return false;
}

bool Equipe::busca_em_profundidade(int atual, int* visitado, std::stack<int>* ordenacao) {
    visitado[atual] = 1; // 1 indica que o vértice atual está sendo processado

    for (const int& vizinho : this->listas_adjacencia[atual]) {
        // Se encontrarmos um vértice marcado com 1, isso significa que existe um ciclo no grafo
        if (visitado[vizinho] == 1)
            return true;
        else if (visitado[vizinho] == 0)
            this->busca_em_profundidade(vizinho, visitado, ordenacao);
    }

    visitado[atual] = 2; // 2 indica que o vértice atual já foi completamente processado
    if (ordenacao != nullptr)
        ordenacao->push(atual);
    return false;
}

bool Equipe::trocar_aresta(int a, int b) {
    auto& lista_a = this->listas_adjacencia[a];
    auto& lista_b = this->listas_adjacencia[b];

    auto tamanho_original = lista_a.size();
    lista_a.remove(b);

    // Como `std::list::remove` não retornar se a remoção pôde ser realizada ou não, checamos se o
    // tamanho da lista mudou. Caso tenha mudado, o elemento foi removido.
    if (lista_a.size() != tamanho_original) {
        lista_b.push_front(a);
        return true;
    }

    return false;
}

void Equipe::comando_swap(int a, int b) {
    // Tenta trocar a direção de uma aresta de A para B
    bool encontrada = this->trocar_aresta(a, b);
    if (encontrada) {
        // Se a troca da direção da aresta causou a formação de um ciclo, devemos revertê-la
        if (this->detectar_ciclos()) {
            this->trocar_aresta(b, a);
        }
        return;
    }

    // Se não existia uma aresta de A para B, fazemos o mesmo, procurando uma aresta de B para A
    encontrada = this->trocar_aresta(b, a);
    if (encontrada) {
        if (this->detectar_ciclos()) {
            this->trocar_aresta(a, b);
        }
    }

}

void Equipe::comando_meeting() {
    std::stack<int> ordenacao;

    // Para mais detalhes sobre como esse método funciona, vide `Equipe::detectar_ciclos`
    int* visitado = new int[this->num_membros];
    for (int i = 0; i < this->num_membros; i++)
        visitado[i] = 0;

    for (int i = 0; i < this->num_membros; i++) {
        if (visitado[i] == 0)
            this->busca_em_profundidade(i, visitado, &ordenacao);
    }

    delete[] visitado;

    while (ordenacao.size() > 0) {
        std::cout << ordenacao.top() << " ";
        ordenacao.pop();
    }

    std::cout << std::endl;
}

std::list<int>* Equipe::revertido() {
    auto grafo_revertido = new std::list<int>[this->num_membros];

    for (int i = 0; i < this->num_membros; i++) {
        for (int j : this->listas_adjacencia[i]) {
            grafo_revertido[j].push_back(i);
        }
    }

    return grafo_revertido;
}

int Equipe::comando_commander(int a) {
    auto grafo_revertido = this->revertido();
    int menor_idade = this->menor_idade(grafo_revertido, a);
    delete[] grafo_revertido;

    if (menor_idade == this->idades[a])
        return -1;
    return menor_idade;
}

int Equipe::menor_idade(std::list<int>* revertido, int a) {
    int menor = this->idades[a];
    for (int i : revertido[a]) {
        int r = this->menor_idade(revertido, i);
        if (r < menor)
            menor = r;
    }

    return menor;
}
