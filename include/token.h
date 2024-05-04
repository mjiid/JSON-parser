#include <string>

enum class TokenType {
        None,
        String,
        Number,
        True,
        False,                                                                  Null,
        LeftBrace,
        RightBrace,
        LeftBracket,                                                            RightBracket,
        Colon,
        Comma,                                                          };


struct Token {
        TokenType type;
        std::string value;
}                                                                       ~   
