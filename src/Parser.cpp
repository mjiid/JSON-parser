#include "Parser.h"

Parser::Parser(const string& input) {
    tokenizer.input = input;
    currentToken = tokenizer.getNextToken();
}

JsonValue Parser::parse() {
    JsonValue result = parseValue();
    if (currentToken != TokenType::End) {
        throw runtime_error("Unexpected token after JSON");
    }
    return result;
}

void Parser::nextToken(){
    currentToken = tokenizer.getNextToken();    
}

JsonValue Parser::parseValue() {
    switch(currentToken.type) {
        case TokenType::LeftBrace: return parseObject();
        case TokenType::LeftBracket: return parseArray();
        case TokenType::String: return parseString();
        case TokenType::Number: return parseNumber();
        case TokenType::True: return parseTrue();
        case TokenType::False: return parseFalse();
        case TokenType::Null: return parseNull();
        default:
            throw runtime_error("Unexpected token");
    }
}

JsonValue Parser::parseObject() {
    JsonValue::Object obj;
    nextToken(); // Consume '{'

    if (currentToken.type == TokenType::RightBrace) {
        nextToken();
        return JsonValue(obj);
    }

    while (true) {
        if (currentToken.type != TokenType::String) {
            throw runtime_error("Expected key to be a string in the object");
        }
        string key = currentToken.value;
        if (currentToken.type != TokenType::Colon) {
            throw runtime_error("Expected ':' in object");
        }
        nextToken();
        obj[key] = parseValue();
        if (currentToken.type == TokenType::RightBrace) {
            nextToken();
            return JsonValue(obj);
        }

        if (currentToken.type != TokenType::Comma) {
            throw runtime_error("Expected ',' or '}' in Object");
        }
        nextToken();
    }

}

JsonValue Parser::parseArray() {
    JsonValue::Array arr;
    nextToken(); // Consume '['
    if (currentToken.type == TokenType::RightBracket) {
        nextToken(); // Consume ']'
        return JsonValue(arr);
    }
    while (true) {
        arr.push_back(parseValue());
        nextToken();

        if (currentToken.type == TokenType::RightBracket) {
            nextToken(); // Consume ']'
            return JsonValue(arr);
        }

        if (currentToken.type != TokenType::Comma) {
            throw runtime_error("Expected ',' or ']' in Array");
        }
        nextToken();
    }
}

JsonValue Parser::parseString() {
    JsonValue value(currentToken.value);
    nextToken();
    return value;
}

JsonValue Parser::parseNumber() {
    JsonValue value(stod(currentToken.value));
    nextToken();
    return value;
}

JsonValue Parser::parseTrue() {
    JsonValue value(true);
    nextToken();
    return value;
}

JsonValue Parser::parseFalse() {
    JsonValue value(false);
    nextToken();
    return value;
}

JsonValue Parser::parseNull() {
    JsonValue value;
    nextToken();
    return value;
}