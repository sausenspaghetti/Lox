#ifndef LOX_CONST
#define LOX_CONST 1;

#include<string>


class Lox {
public:
    Lox() : hadError(false) {}

    
    void runFile(std::string filename);
    void runPrompt();
    void run(std::string source_code);

    int entry_point(int argc, char * argv []);

    void error(int line, std::string message);
    void report(int line, std::string where, std::string message);


private:
    bool hadError = false;
};

#endif