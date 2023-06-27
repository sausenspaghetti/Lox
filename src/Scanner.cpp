#include<string>
#include<list>
#include<map>

#include "Token.h"
#include "TokenType.h"
#include "Lox.h"
#include "Scanner.h"


std::map<std::string, TokenType> keywords = {
    {"and",    AND},
    {"or",     OR},
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE}
};


void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
}


std::list<Token> Scanner::scanTokens() {
    while(!this->isAtEnd()){ 
        start = current;
        scanToken();
    }

    // TODO: check difference
    addToken(EOF_);
    //this->tokens.push_back(Token(EOF_, "", "", line));
}

void Scanner::scanToken() { 
    char c = advance();
    switch(c) {
        case ')': this->addToken(LEFT_PAREN);   break;
        case '(': this->addToken(RIGHT_PAREN);  break;
        case '{': this->addToken(LEFT_BRACE);   break;
        case '}': this->addToken(RIGHT_BRACE); break;
        case ',': this->addToken(COMMA); break;
        case '.': this->addToken(DOT); break;
        case ';': this->addToken(SEMICOLON); break;
        case '-': this->addToken(MINUS); break;
        case '+': this->addToken(PLUS); break;
        case '*': this->addToken(STAR); break;

        // One or two character operators
        case '!': 
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;

        case '/':
            if (match('/')) {
                // start comment line
                while(peek() != '\n' && !isAtEnd()) 
                    advance();
            }
            else {
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;

        // string literals
        case '"':
            readString();
            break;

        default:
            if(isDigit(c)) {
                readNumber();
            } else if (isAlpha(c)) {
                readIdentifier();
            } 
            else {
                // TODO: add errors!
                // Lox.error(line, "Unexpected character");
            }

    }
}




bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    current++;
    return true;
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
}

void Scanner::addToken(TokenType type) {
    this->addToken(type, "");
}

char Scanner::peek() { 
    if(isAtEnd()) 
        return '\0';
    return source.at(current); 
}


char Scanner::peekNext(){
    if(current + 1 >= source.size()) return '\0';
    return source.at(current + 1); 
}

bool Scanner::isDigit(char c){
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || 
        (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isDigit(c) || isAlpha(c);
}


void Scanner::readNumber() {
    while(isDigit(peek())) advance();

    // check fractional part
    if(peek() == '.' && isDigit(peekNext())) {
        advance();

        while(isDigit(peek())) advance();
    }

    // double value = std::stof(source.substr(start, current) );
    std::string value = source.substr(start, current);
    addToken(NUMBER, value);
}

void Scanner::readString() {
    while (peek() != '"' && peek() != '\0') {
        if(peek() == '\n') line++;
        
        advance();
    }
    if(isAtEnd()) {
        // TODO: add error
        // Lox.error(line, "Unterminated string.");
        return;
    }

    // the closing "
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - 1);
    addToken(STRING, value);
}

void Scanner::readIdentifier() {
    while(isAlphaNumeric(peek())) advance();


    // check that identifier, not keywords
    std::string text = source.substr(start, current);
    TokenType type;
    if (keywords.count(text) == 0) {
        type = IDENTIFIER;
    } else {
        type = keywords[text];
    }

    addToken(type);
}
