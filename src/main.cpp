#include <iostream>

#include "equipe.h"

int main(int argc, char* argv[]) {
    Equipe eq = Equipe(10);
    
    eq.inserir_aresta(5, 6);
    eq.inserir_aresta(2, 3);
    eq.inserir_aresta(3, 4);
    eq.inserir_aresta(4, 2); // Não estamos checando ciclos
    eq.inserir_aresta(8, 8); // ...laços
    eq.inserir_aresta(5, 6); // ...ou arestas paralelas.

    eq.imprimir_arestas();
    return 0;
}
