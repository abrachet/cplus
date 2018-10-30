#include "./lexer.hpp"
#include "./_lexer.hpp"
#include <iostream>

extern token_vector_t __tokenized_file;

std::vector<KnownType> known_types;

std::vector<UserTypes> user_types;



static std::map<std::string, void(*)(FuncArg)> function_map {
    {"struct", ObjectHandle},
    {"class",  ObjectHandle},
    {"typedef", TypeDefHandle},
};


void fm_push_back(std::string str, void(*func)(FuncArg))
{
    function_map[str] = func;
}


void ut_push_back(UserTypes* ut)
{
    user_types.push_back(*ut);

    known_types.push_back(KnownType(ut->_ID, ut));

    function_map[ut->_ID] = UserTypeHandle;

    LOG("pushed to known types");
    //std::cout << "pushed to known types. Size is: " << known_types.size() << std::endl;
}

/*
const KnownType nullkt()
{
    //KnownTypes("NULL");

}
*/
typedef void(*func_t)(FuncArg);

func_t __attribute__((always_inline)) in_map(std::string str)
{
    auto found = function_map.find(str);
    if (found != function_map.end())
        return found->second;
    
    return nullptr;
}



void map_init()
{
    for (std::string str : Tokens::integral_types) {
        function_map[str] = IntegralTypeHandle;
        known_types.push_back(KnownType(str));
    }

    for (std::string str : Tokens::type_specifiers)
        function_map[str] = TypeSpecifierHandle;

}

/**
 * 
 * Currently the lexer/parser only labels what it needs 
 * entry point for other files
 */ 
void lexlines()
{
    map_init();
    for (auto it = __tokenized_file.begin(); it != __tokenized_file.end(); it++) {
        auto func = in_map(it->literal_token);

        if (func) {
            FuncArg current(it);
            func(current);
        }
    }
}
