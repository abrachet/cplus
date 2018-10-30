#include <vector>
#include <string>
#include <functional>

#include "./lexer.hpp"


template <class T>
bool _in_vec(const std::vector<T>& vec, T to_find)
{
    for (auto i : vec)
        if (i == to_find)
            return true;

    return false;
}


std::function<void(Lexer::LexerFunctionArg&)>
Lexer::find_handle_func(std::string str)
{
    for (auto pair : _base_map)
        if ( _in_vec<std::string>(pair.first, str) )
            return pair.second;

    return null_func; //maybe throw?
}

void Lexer::lexlines()
{
    for (auto line : _token_vec) {
        LexerFunctionArg arg(line);
        for (auto token : line) {
            arg.current_token = token;
            find_handle_func(token.literal_token) (arg);
        }
    }

}

void Lexer::add_to_types(UserTypes ut)
{
    _current_types.push_back(ut);
}


Tokens::Token Lexer::find_end_of_struct(Lexer::LexerFunctionArg& lfa)
{
    int stack = 0;
    auto tv = _token_vec;

    for (auto i : tv) {
        for (auto token : i) {
            std::string lt = token.literal_token;
            if (lt == "{")
                stack++;
            if (lt == "}")
                stack--;

            if (stack == 0)
                return token;
        }
    }

    return * new Tokens::Token();
}

void Lexer::object_type_handle(LexerFunctionArg& lfa)
{
    // typedefing anonymous struct not currently
    // supported. I'll do that later
    // currently 
    UserTypes ut(*(lfa.current_token++));
    ut.end_of_scope = find_end_of_struct(lfa);
    add_to_types(ut);
}

void Lexer::ObjectsHandle(LexerFunctionArg& lfa)
{
    std::string name = lfa.current_token->literal_token;

    if (name == "struct" || "class")
        object_type_handle(lfa);
}

