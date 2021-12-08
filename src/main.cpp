#include "Fakefile.h"

int main(const int argc, const char** argv) {
    // Generate Symbols
    Parser parser("Fakefile");
    
    // Load Symbols
    Compiler compiler(parser.getRules());
    
    // Execute Symbols
    compiler.execute(argc, argv);

    return 0;
}
