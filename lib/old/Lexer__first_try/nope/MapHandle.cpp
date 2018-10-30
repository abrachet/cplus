#include "./MapHandle.hpp"
#include <functional>
#include <iterator>
#include <algorithm>



/**
 * 
 * Iterate through the vector of types and return its type corresponding to 
 * type_map from MapHandle.hpp
 * 
 */ 
std::function<void(LexerFunctionArg&)> get_function(std::string str, Lexer lexer)
{
    std::vector<std::string>& types = lexer._base_map.key[0];

    for (int i = 0; i < types.length(); i++) {
        if (types[i] == str)
            return _type_map[i];
    }
    return null_func;
    
}



void add_type(std::string, std::function<void(LexerFunctionArg&)> = null_func )
{
    
}