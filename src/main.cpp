#include <iostream>
#include <string>
#include "lexer.h" 

int main() {
    std::string json = R"({"key": "value", "array": [true, null, 123]})";
    JSONLexer lexer(json); 

    Token token = lexer.getNextToken();
    while (token.type != TokenType::EndOfFile) {
        std::cout << "Token Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
        token = lexer.getNextToken();
    }
    return 0;
}

