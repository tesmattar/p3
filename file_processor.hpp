#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <string>
#include <filesystem>
#include "line_counter.hpp"

namespace fs = std::filesystem;

class FileProcessor {
public:
    FileProcessor();  // Declaração do construtor
    void processPath(const std::string& path);
    int getTotalCodeLines() const;
    int getTotalCommentLines() const;
    int getTotalEmptyLines() const;

private:
    int totalCodeLines;
    int totalCommentLines;
    int totalEmptyLines;

    void processFile(const fs::path& filePath);
};

#endif // FILE_PROCESSOR_HPP
