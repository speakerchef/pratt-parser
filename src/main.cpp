#include "parser.hpp"
#include <cstdlib>


int main(int argc, char **argv) {
    std::string path = argv[1];
    Lexer lexer(path);
    Parser parser(lexer.tokenize());
    auto res = parser.parse_expr(0);
    res->print(0);
    if (!res) exit(EXIT_FAILURE);


    return 0;
}
