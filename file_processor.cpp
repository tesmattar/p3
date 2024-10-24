#include "file_processor.hpp"

FileProcessor::FileProcessor() : totalCodeLines(0), totalCommentLines(0), totalEmptyLines(0) {}

void FileProcessor::processPath(const std::string& path) {
    fs::path inputPath(path);

    if (fs::is_regular_file(inputPath)) {
        processFile(inputPath);
    } else if (fs::is_directory(inputPath)) {
        for (const auto& entry : fs::recursive_directory_iterator(inputPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
                processFile(entry.path());
            }
        }
    } else {
        std::cerr << "O caminho fornecido não é válido." << std::endl;
    }
}

void FileProcessor::processFile(const fs::path& filePath) {
    LineCounter lineCounter;
    lineCounter.processFile(filePath.string());
    
    totalCodeLines += lineCounter.getCodeLines();
    totalCommentLines += lineCounter.getCommentLines();
    totalEmptyLines += lineCounter.getEmptyLines();

    std::cout << "Arquivo: " << filePath << std::endl;
    std::cout << "Linhas de código: " << lineCounter.getCodeLines() 
              << ", Linhas de comentários: " << lineCounter.getCommentLines()
              << ", Linhas vazias: " << lineCounter.getEmptyLines() << std::endl;
}

int FileProcessor::getTotalCodeLines() const {
    return totalCodeLines;
}

int FileProcessor::getTotalCommentLines() const {
    return totalCommentLines;
}

int FileProcessor::getTotalEmptyLines() const {
    return totalEmptyLines;
}


