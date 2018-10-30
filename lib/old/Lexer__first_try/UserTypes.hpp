#ifndef USERTYPES_H
#define USERTYPES_H

#include "../tokens.hpp"

struct UserTypes {
    Tokens::Token name;
    Tokens::Token end_of_scope;

    UserTypes(Tokens::Token name)
    : name(name)
    {}
};

#endif
