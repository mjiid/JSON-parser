#pragma once 

#include "JsonValue.h"
#include "Tokenizer.h"

using namespace std;

class Parser {
public:
    Parser(const string& input);
    JsonValue parse();
private:
    Tokenizer tokenizer;
    Token currentToken;

    void nextToken();
    JsonValue parseValue();
    JsonValue parseObject();
    JsonValue parseArray();
    JsonValue parseString();
    JsonValue parseNumber();
    JsonValue parseTrue();
    JsonValue parseFalse();
    JsonValue parseNull();
}