#include <vector>
#include <string>
#include <cctype>
#include "token.h"

class JSONLexer {
public:
	JSONLexer(const std::string& input) : input(input), position(0) {}
	
	std::vector<Token> tokenize() {
		std::vector<Token> tokens;
		
		while (position < input.length()) {
			char currentChar = input[position];
			
			// Skip whitespace
			if (isspace(currentChar)) {
                position++;
                continue;
            }
            
            switch (currentChar) {
                case '{':
                    tokens.push_back({TokenType::LeftBrace, "{"});
              break;
                case '}':
                    tokens.push_back({TokenType::RightBrace, "}"});
              break;
                case '[':
                    tokens.push_back({TokenType::LeftBracket, "["});
              break;
              case ']':
                    tokens.push_back({TokenType::RightBracket, "]"});
              break;
              case ':':
                    tokens.push_back({TokenType::Colon, ":"});
              break;
              case ',':
                    tokens.push_back({TokenType::Comma, ","});
              break;
              case '"':
                    tokens.push_back({TokenType::String, parseString()});
              break;
              default:
                // Treat everything else as a separate token:
                tokens.push_back({TokenType::None, std::string(1, currentChar)});
                break;
            }

            position++;
		}

        return tokens;
	}	
}

