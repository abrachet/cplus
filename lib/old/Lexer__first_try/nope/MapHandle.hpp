#ifndef MAP_HANDLE_H
#define MAP_HANDLE_H

#include <vector>
#include <map>
#include <string>
#include <functional>

#include "./lexer.hpp"

/////////////////////
//                 //
//    type map     //
//                 //
/////////////////////

/**
 * the _map_ is a actually a vector but whos index corresponds with _base_map[0].key's vector
 * 
 * for reference the type vector starts out with:
 *   "void",
 *   "char",
 *   "short",
 *   "int",
 *   "float",
 *   "double",
 * 
 */

static std::vector<std::string>& _type_vec;

static std::vector<std::function<void(LexerFunctionArg&)> > _type_map {

};

void MapHandleInit()
{
    
}


void null_func(LexerFunctionArg& lfa) 
{ 
    return;
}

//map to an already existing function in the map, useful for typedef
std::function<void(LexerFunctionArg&)> get_function(std::string, Lexer);

void add_type(std::string, std::function<void(LexerFunctionArg&)>);


#endif /* MAP_HANDLE_H */