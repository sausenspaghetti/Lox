#ifndef SCANNER_CONST
#define SCANNER_CONST 1

#include<string>
#include<list>
#include<list>


#include "Token.h"
#include "TokenType.h"



class Scanner {
public:
    Scanner(std::string source) : source(source), tokens(std::list<Token>()) {}
    Scanner() {}

    std::list<Token> scanTokens();
    void scanToken();


    // support functions
    bool isAtEnd() const { return current >= source.size(); }

    char advance() { return source.at(current++); }

    char peek();
    char peekNext();

    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);

    bool match(char expected);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);

    void readString();
    void readNumber();
    void readIdentifier();


private:
    std::string source; 
    std::list<Token> tokens;

    // start и current - указывают на границы текущей лексемы
    int start = 0;
    int current = 0;

    // номер текущей строки
    int line = 1;

    // Lox & lox;
};

#endif