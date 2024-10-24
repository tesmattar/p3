#include <iostream>
#include "file_processor.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo ou diretório>" << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    FileProcessor processor;
    processor.processPath(inputPath);

    std::cout << "Total de linhas de código: " << processor.getTotalCodeLines() << std::endl;
    std::cout << "Total de linhas de comentários: " << processor.getTotalCommentLines() << std::endl;
    std::cout << "Total de linhas vazias: " << processor.getTotalEmptyLines() << std::endl;

    return 0;
}
