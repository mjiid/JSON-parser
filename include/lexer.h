#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"

class JSONLexer {
public:
    JSONLexer(const std::string& in);

    Token getNextToken();

private:
    std::string input;
    size_t position;

    Token getStringToken();
    Token getNumberToken();
    Token getLiteralToken();
};

#endif // LEXER_H

