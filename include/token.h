#include <string> // Include necessary header for std::string

enum class TokenType {
    LBrace, RBrace,   // { }
    LBracket, RBracket,  // [ ]
    Colon, Comma,   // : ,
    String, Number,
    True, False, Null,
    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, std::string v = "") : type(t), value(v) {}  // Corrected parameter names
};

