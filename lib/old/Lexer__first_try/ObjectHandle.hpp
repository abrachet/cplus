#pragma once
#include "../tokens.hpp"
#include "./LFA.hpp"
#include "UserTypes.hpp"
#include "./lexer.hpp"

void ObjectsHandle(LexerFunctionArg&);
Tokens::Token find_end_of_struct(LexerFunctionArg&);
void object_type_handle(LexerFunctionArg&);


