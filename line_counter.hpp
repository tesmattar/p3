#ifndef LINE_COUNTER_HPP
#define LINE_COUNTER_HPP

#include <string>
#include <fstream>
#include <iostream>

class LineCounter {
public:
    LineCounter();
    void processFile(const std::string& filePath);
    int getCodeLines() const;
    int getCommentLines() const;
    int getEmptyLines() const;

private:
    int codeLines;
    int commentLines;
    int emptyLines;
    bool insideBlockComment;

    bool isComment(const std::string& line, bool& lineHasCode, bool& lineHasComment);
    bool isEmptyLine(const std::string& line);
};

#endif // LINE_COUNTER_HPP

