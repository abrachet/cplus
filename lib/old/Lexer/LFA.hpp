#include <vector>
#include "../tokens.hpp"

struct LexerFunctionArg {
    std::vector<Tokens::Token> current_line;

    std::vector<Tokens::Token>::iterator iterator;
    Tokens::Token current_token;

    std::vector<std::vector<Tokens::Token> > token_vec;

    LexerFunctionArg(std::vector<Tokens::Token>& cl)
    : current_line(cl)
    {}

    LexerFunctionArg(std::vector<Tokens::Token> cl, std::vector<Tokens::Token>::iterator ct)
    : current_line(cl), iterator(ct)
    {}

    LexerFunctionArg(std::vector<Tokens::Token> cl, Tokens::Token ct) 
    : current_line(cl), current_token(ct)
    {}

    LexerFunctionArg(std::vector<Tokens::Token> cl, Tokens::Token ct, std::vector<std::vector<Tokens::Token> >& token_vec) 
    : current_line(cl), current_token(ct), token_vec(token_vec)
    {}

    
};