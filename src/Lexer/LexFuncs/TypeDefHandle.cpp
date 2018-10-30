#include <vector>
#include "../_lexer.hpp"
#include "../KnownTypes.hpp"

extern std::vector<UserTypes> user_types;
extern std::vector<KnownType> known_types;

extern std::map<std::string, void(*)(FuncArg)> function_map;

void TypeDefHandle(FuncArg arg)
{
    
    auto it = arg.it;
    int num = 0;
    for (; it->type != Tokens::TokenType::LogicalLineDelim; it++){
        num++;
    }
    it--;

    Tokens::Token token = *it;
    typedef_add((it--)->literal_token, token);

    
}