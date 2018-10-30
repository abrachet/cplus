#pragma once

#include <string>
#include <functional>
#include "./UserTypes.hpp"

#define NULL_KT       -1
#define PRIMITIVE      0
#define ORIG_USER_TYPE 1
#define ALIAS          2

struct KnownType {
    std::string ID;
    int8_t kind;
    union {
        UserTypes* type;
        std::reference_wrapper<KnownType> aliases;
    };
    typedef std::pair<bool, std::vector<Tokens::Token> > _kt_reference_t;
    private:
    std::vector<_kt_reference_t> references;
    public:

    KnownType(std::string ID)
    : ID(ID), kind(PRIMITIVE), type(nullptr)
    {}

    KnownType(std::string ID, KnownType kt)
    : ID(ID), kind(ALIAS), aliases(kt)
    {}
    
    KnownType(std::string ID, UserTypes* ut)
    : ID(ID), kind(ORIG_USER_TYPE), type(ut)
    {}

    static KnownType unknown_alias(std::string ID)
    {
        KnownType kt(ID);
        kt.kind = ALIAS;
        return kt;
    }

    
    _kt_reference_t& get_new_reference(bool ptr_type);
    void add_reference(Tokens::Token, _kt_reference_t&);
    //just pushes back to references.back().second();
    void add_reference(Tokens::Token);

};

std::pair<bool, KnownType&> get_kt(std::string str);

void typedef_add(std::string, Tokens::Token);

void kt_push_back(KnownType);