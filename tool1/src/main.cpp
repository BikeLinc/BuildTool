#include "BuildTool.h"

int main(const int argc, const char** argv) {
    // Generate Symbols
    Parser parser("BuildTool");
    
    // Load Symbols
    Compiler compiler(parser.getRules());
    
    // Execute Symbols
    compiler.execute(argc, argv);

    return 0;
}
