#pragma once

#include <vector>
#include "./lexer.hpp"
#include <unordered_map>

typedef std::vector<Tokens::Token>::iterator vec_iter_t;

struct UserTypes {
    #ifndef MEMCONCERN
    std::string _ID; // not needed because it can be found from the iterator
    #endif

    vec_iter_t start;
    vec_iter_t end;

    std::unordered_map<std::string, std::string> member_funcs;
};

void ut_push_back(UserTypes ut);
void ut_push_back(UserTypes* ut);