#include <vector>
#include "../tokens.hpp"

struct UserTypes {
    Tokens::Token name;
    Tokens::Token end_of_scope;

    UserTypes(Tokens::Token name)
    : name(name)
    {}
};


void lex_lines(std::vector<std::vector<Tokens::Token> >& token_vec)
{
    std::vector<UserTypes> _current_types;

    
}