#include <iostream>
#include <fstream>
#include <sstream>

#include "equipe.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Número errado de argumentos da linha de comando!" << std::endl;
        return 1;
    }

    auto arquivo_entrada = std::ifstream(std::string(argv[1]));
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
        // Por enquanto, estamos ignorando a idade lida
        // @TODO: Armazenar as idades dos alunos.
        sstream_linha >> idade;
    }

    for (int i = 0; i < num_arestas; i++) {
        std::getline(arquivo_entrada, linha);
        sstream_linha = std::stringstream(linha);
        int x, y;
        sstream_linha >> x >> y;
        equipe.inserir_aresta(x, y);
    }

    equipe.imprimir_arestas();

    return 0;
}
