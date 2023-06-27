#ifndef TOKEN_CONST 
#define TOKEN_CONST 1

#include <string>

#include "TokenType.h"


class Token {
public:

    Token (
        TokenType type, 
        std::string lexeme, 
        std::string literal,
        int line
    ) : type(type), lexeme(lexeme), line(line), literal(literal) {}


  std::string toString() {
    return type + " " + lexeme + " " + literal;
  }

private:
    TokenType type;
    std::string lexeme;
    std::string literal;
    
    int line;
};

#endif