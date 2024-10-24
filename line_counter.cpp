#include "line_counter.hpp"


LineCounter::LineCounter() : codeLines(0), commentLines(0), emptyLines(0), insideBlockComment(false) {}

void LineCounter::processFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (isEmptyLine(line)) {
                emptyLines++;
                continue;
            }

            bool lineHasComment = false;
            bool lineHasCode = false;

            std::string trimmedLine = line;
            trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t"));  

            if (isComment(trimmedLine, lineHasCode, lineHasComment)) {
                if (lineHasComment) {
                    commentLines++;
                }
                if (lineHasCode) {
                    codeLines++;
                }
            } else if (!line.empty()) {
                codeLines++;
            }
        }
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
    }
}

bool LineCounter::isComment(const std::string& line, bool& lineHasCode, bool& lineHasComment) {
    lineHasCode = false;
    lineHasComment = false;
    std::string trimmedLine = line;
    trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t"));  

    if (insideBlockComment) {
        size_t endBlockPos = trimmedLine.find("*/");
        if (endBlockPos != std::string::npos) {
            insideBlockComment = false;  
            std::string codeAfterComment = trimmedLine.substr(endBlockPos + 2);
            if (!codeAfterComment.empty() && codeAfterComment.find_first_not_of(" \t") != std::string::npos) {
                lineHasCode = true;  
            }
        }
        lineHasComment = true;
        return true;
    }

    size_t singleLineCommentPos = trimmedLine.find("//");
    size_t blockCommentPos = trimmedLine.find("/*");

    if (singleLineCommentPos != std::string::npos) {
        lineHasComment = true;
        if (singleLineCommentPos > 0) {
            std::string codeBeforeComment = trimmedLine.substr(0, singleLineCommentPos);
            if (!codeBeforeComment.empty() && codeBeforeComment.find_first_not_of(" \t") != std::string::npos) {
                lineHasCode = true;  
            }
        }
        return true;
    }

    if (blockCommentPos != std::string::npos) {
        insideBlockComment = true;
        lineHasComment = true;

        if (blockCommentPos > 0) {
            std::string codeBeforeComment = trimmedLine.substr(0, blockCommentPos);
            if (!codeBeforeComment.empty() && codeBeforeComment.find_first_not_of(" \t") != std::string::npos) {
                lineHasCode = true;  
            }
        }

        size_t endBlockPos = trimmedLine.find("*/", blockCommentPos);
        if (endBlockPos != std::string::npos) {
            insideBlockComment = false;  
            std::string codeAfterComment = trimmedLine.substr(endBlockPos + 2);
            if (!codeAfterComment.empty() && codeAfterComment.find_first_not_of(" \t") != std::string::npos) {
                lineHasCode = true;  
            }
        }

        return true;
    }

    lineHasCode = !trimmedLine.empty();
    return false;
}

bool LineCounter::isEmptyLine(const std::string& line) {
    return line.find_first_not_of(" \t") == std::string::npos;
}

int LineCounter::getCodeLines() const {
    return codeLines;
}

int LineCounter::getCommentLines() const {
    return commentLines;
}

int LineCounter::getEmptyLines() const {
    return emptyLines;
}


