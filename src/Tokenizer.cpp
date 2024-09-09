#include "Tokenizer.h"

// Tokenizer constructor
Tokenizer::Tokenizer(const std::string& input) : input(input), position(0) {}

// Method to skip whitespace characters
void Tokenizer::skipWhiteSpace() {
    while (position < input.length() && isspace(input[position])) {
        position++;
    }
}

// Method to get the next token from the input
Token Tokenizer::getNextToken() {
    skipWhiteSpace();

    if (position >= input.size()) {
        return {TokenType::End, ""};
    }

    char currentChar = input[position];
    switch (currentChar) {
        case '{':
            position++;
            return {TokenType::LeftBrace, "{"};
        case '}':
            position++;
            return {TokenType::RightBrace, "}"};
        case '[':
            position++;
            return {TokenType::LeftBracket, "["};
        case ']':
            position++;
            return {TokenType::RightBracket, "]"};
        case ':':
            position++;
            return {TokenType::Colon, ":"};
        case ',':
            position++;
            return {TokenType::Comma, ","};
        case '"':
            return parseString();
        case 't':
            return parseTrue();
        case 'f':
            return parseFalse();
        case 'n':
            return parseNull();
        default:
            if (isdigit(currentChar) || currentChar == '-') {
                return parseNumber();
            }
    }

    throw std::runtime_error("Unexpected character!");
}

// Method to parse a string token
Token Tokenizer::parseString() {
    size_t start = ++position;
    while (position < input.length() && input[position] != '"') {
        position++;
    }

    if (position >= input.length()) {
        throw std::runtime_error("Unterminated string");
    }

    std::string str_value = input.substr(start, position - start);
    position++; // Move past the closing "
    return {TokenType::String, str_value};
}

// Method to parse a true token
Token Tokenizer::parseTrue() {
    if (input.substr(position, 4) == "true") {
        position += 4;
        return {TokenType::True, "true"};
    }

    throw std::runtime_error("Expected 'true'");
}

// Method to parse a false token
Token Tokenizer::parseFalse() {
    if (input.substr(position, 5) == "false") {
        position += 5;
        return {TokenType::False, "false"};
    }

    throw std::runtime_error("Expected 'false'");
}

// Method to parse a null token
Token Tokenizer::parseNull() {
    if (input.substr(position, 4) == "null") {
        position += 4;
        return {TokenType::Null, "null"};
    }

    throw std::runtime_error("Expected 'null'");
}

// Method to parse a number token
Token Tokenizer::parseNumber() {
    size_t start = position;
    while (position < input.length() && (isdigit(input[position]) || input[position] == '.' || input[position] == 'e' || input[position] == '-')) {
        position++;
    }

    std::string number = input.substr(start, position - start);
    return {TokenType::Number, number};
}