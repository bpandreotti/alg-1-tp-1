#include <iostream>
#include <fstream>
#include <sstream>

#include "equipe.h"

Equipe construir_equipe(std::ifstream& arquivo_entrada, int num_alunos, int num_arestas) {
    Equipe equipe = Equipe(num_alunos);

    std::string linha;
    std::getline(arquivo_entrada, linha);
    auto sstream_linha = std::stringstream(linha);

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

void executar_comandos(std::ifstream& arquivo_entrada, Equipe& equipe, int num_instrucoes) {
    std::string linha;
    for (int i = 0; i < num_instrucoes; i++) {
        std::getline(arquivo_entrada, linha);
        auto sstream_linha = std::stringstream(linha);
        char tipo;
        sstream_linha >> tipo;


        if (tipo == 'S') {
            // Comando "SWAP"
            int a, b;
            sstream_linha >> a >> b;
            bool sucesso = equipe.comando_swap(a - 1, b - 1);
            std::cout << "S " << (sucesso ? "T" : "N") << std::endl;

        } else if (tipo == 'C') {
            // Comando "COMMANDER"

            int a;
            sstream_linha >> a;
            int idade = equipe.comando_commander(a - 1);
            if (idade == INT32_MAX)
                std::cout << "C *" << std::endl;
            else
                std::cout << "C " << idade << std::endl;

        } else if (tipo == 'M') {
            // Comando "MEETING"
            auto ordenacao = equipe.comando_meeting();
            std::cout << "M ";
            while (ordenacao.size() > 0) {
                // Somando 1 pois os índices da saída devem começar em 1
                std::cout << ordenacao.top() + 1 << " ";
                ordenacao.pop();
            }
            std::cout << std::endl;

        } else
            std::cerr << "Comando \'" << tipo << "\' não reconhecido" << std::endl;
    }
}

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

    Equipe equipe = construir_equipe(arquivo_entrada, num_alunos, num_arestas);

    // @DEBUG
    equipe.imprimir_idades();
    equipe.imprimir_arestas();

    executar_comandos(arquivo_entrada, equipe, num_instrucoes);

    return 0;
}
