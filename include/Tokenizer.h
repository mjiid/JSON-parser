#pragma once

#include "Token.h"
#include "Tokentype.h"
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class Tokenizer{
private:
    const string& input;
    size_t position;

public:
    Tokenizer(const string& input) : input(input) {};
    Token getNextToken();

private:
    Token parseString();
    Token parseTrue();
    Token parseFalse();
    Token parseNull();
    Token parseNumber();
    void skipWhiteSpace();
};