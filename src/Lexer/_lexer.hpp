#pragma once

#include "./lexer.hpp"
#include "./KnownTypes.hpp"
#include "../../lib/vector_operations.hpp"

enum class ScopeType {
    Global,
    Function,
};
const std::pair<ScopeType, Tokens::Token> get_scope(vec_iter_t);

LogicalLine find_lines(vec_iter_t);




/////////////////
//             //
// Lexer Funcs //
//             //
/////////////////

void NullFunc(FuncArg);

void ObjectHandle(FuncArg);

void IntegralTypeHandle(FuncArg);

void TypeSpecifierHandle(FuncArg);

void TypeDefHandle(FuncArg);

void UserTypeHandle(FuncArg);

void AutoHandle(FuncArg);