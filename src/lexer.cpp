#include "lexer.h"
#include <string>
#include <vector>
#include <cctype>  // For std::isdigit, std::isspace

JSONLexer::JSONLexer(const std::string& in) : input(in), position(0) {}
size_t position;


Token JSONLexer::getNextToken() {
        while (position < input.length()) {
            char current = input[position];

            switch (current) {
                case '{': position++; return Token(TokenType::LBrace);
                case '}': position++; return Token(TokenType::RBrace);
                case '[': position++; return Token(TokenType::LBracket);
                case ']': position++; return Token(TokenType::RBracket);
                case ':': position++; return Token(TokenType::Colon);
                case ',': position++; return Token(TokenType::Comma);
                case '"': return getStringToken();
                case ' ': case '\t': case '\n': case '\r':
                    position++; break; // Ignore whitespace
                default:
                    if (std::isdigit(current) || current == '-') {
                        return getNumberToken();
                    } else if (std::isalpha(current)) {
                        return getLiteralToken();
                    } else {
                        position++; return Token(TokenType::Unknown);
                    }
            }
        }
        return Token(TokenType::EndOfFile);
}

Token JSONLexer::getStringToken() {
        size_t start = ++position; // Skip initial quote
        while (position < input.length() && input[position] != '"') {
            if (input[position] == '\\' && (position + 1 < input.length())) {
                // Skip escaped character
                position++;
            }
            position++;
        }
        std::string value = input.substr(start, position - start);
        position++; // Skip closing quote
        return Token(TokenType::String, value);
  
}

Token JSONLexer::getNumberToken() {
        size_t start = position;
        while (position < input.length() && (std::isdigit(input[position]) || input[position] == '.' || input[position] == '-')) {
            position++;
        }
        return Token(TokenType::Number, input.substr(start, position - start));
 
}

Token JSONLexer::getLiteralToken() {
        size_t start = position;
        while (position < input.length() && std::isalpha(input[position])) {
            position++;
        }
        std::string value = input.substr(start, position - start);
        if (value == "true") {
            return Token(TokenType::True);
        } else if (value == "false") {
            return Token(TokenType::False);
        } else if (value == "null") {
            return Token(TokenType::Null);
        }
        return Token(TokenType::Unknown, value);
 
}

