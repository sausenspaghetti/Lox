#include <iostream>

#include "Lox.h"


int main(int argc, char * argv[]) {
    Lox lox = Lox();

    int result = lox.entry_point(argc, argv);

    return result;
}