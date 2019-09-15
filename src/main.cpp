#include <iostream>
#include <fstream>
#include <sstream>

#include "equipe.h"

Equipe construir_equipe(std::ifstream& arquivo_entrada) {
    std::string linha;
    std::getline(arquivo_entrada, linha);
    auto sstream_linha = std::stringstream(linha);

    int num_alunos, num_arestas, num_instrucoes;
    sstream_linha >> num_alunos >> num_arestas >> num_instrucoes;

    Equipe equipe = Equipe(num_alunos);

    std::getline(arquivo_entrada, linha);
    sstream_linha = std::stringstream(linha);

    for (int i = 0; i < num_alunos; i++) {
        int idade;
        sstream_linha >> idade;
        equipe.set_idade(i, idade);
    }

    for (int i = 0; i < num_arestas; i++) {
        std::getline(arquivo_entrada, linha);
        sstream_linha = std::stringstream(linha);
        int x, y;
        sstream_linha >> x >> y;
        // Subtraindo 1 pois os índices no arquivo começam em 1
        equipe.inserir_aresta(x - 1, y - 1);
    }

    return equipe;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Número errado de argumentos da linha de comando!" << std::endl;
        return 1;
    }

    auto arquivo_entrada = std::ifstream(std::string(argv[1]));
    Equipe equipe = construir_equipe(arquivo_entrada);

    equipe.imprimir_idades();
    equipe.imprimir_arestas();
    std::cout
        << (equipe.detectar_ciclos() ? "Ciclo encontrado" : "Nenhum ciclo encontrado")
        << std::endl;

    return 0;
}
