#pragma once

#include <vector>
#include "../Scanner/tokens.hpp"
#include "../Scanner/scanner.hpp"
#include "./UserTypes.hpp"
#include "./KnownTypes.hpp"

#include "../Logger/Logger.hpp"

#include <map>


void lexlines();

typedef token_vector_t::iterator vec_iter_t;

struct LogicalLine {
    vec_iter_t begin;
    vec_iter_t end;

    LogicalLine()
    {}

    LogicalLine(vec_iter_t begin)
    : begin(begin)
    {}

    LogicalLine(vec_iter_t begin, vec_iter_t end)
    : begin(begin), end(end)
    {}
};


struct FuncArg {
    vec_iter_t it;
    LogicalLine ll;

    FuncArg(vec_iter_t it)
    : it(it)
    {}
};

void fm_push_back(std::string, void(*)(FuncArg));

void ut_push_back(UserTypes*);

KnownType known_type(std::string str);

