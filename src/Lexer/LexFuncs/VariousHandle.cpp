#include "../_lexer.hpp"

void NullFunc(FuncArg arg) { }

void IntegralTypeHandle(FuncArg arg)
{
    assert(find_in_vector<std::string>(Tokens::integral_types, arg.it->literal_token));

    arg.it->type = Tokens::TokenType::Keyword;
    arg.it->token = Tokens::SpecificToken::IntegralType;

}

void TypeSpecifierHandle(FuncArg arg)
{
    assert( find_in_vector<std::string>(Tokens::type_specifiers, arg.it->literal_token) );

    arg.it->type = Tokens::TokenType::Keyword;
    arg.it->token = Tokens::SpecificToken::TypeSpecifer;
    
}

