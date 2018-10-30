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


// To implement:
// kt_push_back()
// is_currently_known()
// ut_push_back() which will also call kt_push_back()


/**
 * kt_push_back()
 * 
 * who calls this:
 *  TypeDefHandle() should
 *   ut_push_back() should
 * 
 * For TypeDefHandle() it shouldnt have to worry about anything other than giving KnownType functions
 * the proper tokens to deal with
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
    for (std::string str : Tokens::integral_types)
        function_map[str] = IntegralTypeHandle;

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
