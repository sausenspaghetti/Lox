#include<iostream>
#include<fstream>
#include<string>
#include<list>

#include "Lox.h"
#include "Scanner.h"
#include "Token.h"


int Lox::entry_point(int argc, char * argv[]) {
    if (argc > 2) {
        std::cout << "Pattern usage jlox [script]\n";
        return 1;
    } 
    else if (argc == 2) {
        std::string filename = std::string(argv[1]);
        runFile(filename);
    }
    else {
        runPrompt();
    }

    return 0;
}


void Lox::runFile(std::string filename) {
    // TODO:check that filename is path  ???
    std::ifstream os_file;
    std::string code_text;
    std::string line;

    os_file.open(filename);

    while(std::getline(os_file, line)) {
        code_text += line + '\n';
    }
    os_file.close();

    run(code_text);

    if(hadError) {
        exit(65);
    }
}


void Lox::run(std::string source) {
    Scanner scanner(source);
    std::list<Token> tokens = scanner.scanTokens();

    for(auto token: tokens) {
        std::cout << "\"" + token.toString() + "\"";
    }

}

void Lox::runPrompt() {
    std::cout << "Interactive mode\n\n";

    std::string next_command;
    for(;;) {
        std::cout << "> ";
        std::getline(std::cin, next_command);
        if(next_command.size() == 0) {
            break;
        }
        else {
            // next_command =  next_command;
            run(next_command);
            hadError = false;
        }
    }

}


void Lox::error(int line, std::string message) {
    report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message) {
    std::cout << "[line] " << line << "Error " << where << ": " << message << "\n";
    hadError = true;
}







// #include<iostream>
// #include<fstream>
// #include<string>
// #include<list>
// using std::cout, std::cin, 
//     std::string, std::ifstream;

// #include "Scanner.cpp"
// #include "Token.cpp"
// #define LOX_CONST 1;


// class Lox {
// public:
//     Lox() : hadError(false) {}

//     // int main(int argc, char* argv[]);
    
//     void runFile(std::string filename);
//     void runPrompt();
//     void run(std::string source_code);


//     void error(int line, std::string message);
//     void report(int line, string where, string message);


// private:
//     bool hadError = false;
// };


// int main(int argc, char * argv[]) {
//     Lox lox = Lox();

//     if (argc > 2) {
//         cout << "Pattern usage jlox [script]\n";
//         return 1;
//     } 
//     else if (argc == 2) {
//         string filename = string(argv[1]);
//         lox.runFile(filename);
//     }
//     else {
//         lox.runPrompt();
//     }


//     return 0;
// }


// void Lox::runFile(string filename) {
//     // check that filename is path 
//     ifstream os_file;
//     string code_text;
//     string line;

//     os_file.open(filename);
//     while(std::getline(os_file, line)) {
//         code_text += line + '\n';
//     }
//     os_file.close();

//     run(code_text);

//     if(hadError) {
//         exit(65);
//     }
// }


// void Lox::run(string source) {
//     Scanner scanner(source);
//     std::list<Token> tokens = scanner.scanTokens();

//     for(auto token: tokens) {
//         cout << "\"" + token.toString() + "\"";
//     }

// }

// void Lox::runPrompt() {
//     cout << "Interactive mode\n\n";

//     string next_command;
//     for(;;) {
//         cout << "> ";
//         std::getline(std::cin, next_command);
//         if(next_command.size() == 0) {
//             break;
//         }
//         else {
//             // next_command =  next_command;
//             run(next_command);
//             hadError = false;
//         }
//     }

// }


// void Lox::error(int line, std::string message) {
//     report(line, "", message);
// }

// void Lox::report(int line, string where, string message) {
//     cout << "[line] " << line << "Error " << where << ": " << message << "\n";
//     hadError = true;
// }