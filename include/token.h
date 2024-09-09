#pragma once

#include "Tokentype.h"
#include <string>

using namespace std;

struct Token {
    TokenType type;
    string value;
};