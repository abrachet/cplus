#include "../_lexer.hpp"
#include <iostream>

using namespace Tokens;

extern std::vector<KnownType> known_types;

extern std::vector<UserTypes> user_types;

std::pair<bool, KnownType&> get_kt(std::string str);


static void
assign_all_in_scope(vec_iter_t it, KnownType& kt)
{
    std::string orig = it->literal_token;
    LOG("aais with orig: " + orig);
     
    //add 1 for the first '{' in the scope
    for (int stack = 1; stack > 0; it++) {
        if (it->token == SpecificToken::CloseCurlyBracket)
            stack--;
        if (it->token == SpecificToken::OpenCurlyBracket)
            stack++;
        if (it->literal_token == orig)
            kt.add_reference(*it);
    }
}


void UserTypeHandle(FuncArg arg)
{
    std::string _typename = arg.it->literal_token;
    LOG("Called with: " + _typename);
    std::pair<bool, KnownType&> known = get_kt(_typename);
    if (!known.first) {
        USER_ERROR("" + _typename + " not found");
        return;
    }

    auto it = arg.it;

    //type * variable
    //type variable
    //type * function()
    //type function()
    bool pointer_type = false;

    auto current_type = (it++)->token;
    if ( current_type == SpecificToken::Asteriks ) {
        pointer_type = true;
        it++; //now we are on the variable name
    }
    else if (current_type == SpecificToken::_Unknown ) { //for ::
        if ( (it++)->token == SpecificToken::_Unknown )
            ;
        //not yet implemented
    }
    //if we get here it is on variable name

    auto kt_references = known.second.get_new_reference(pointer_type);

    for (int i = 0; i < 10; i++)
        std::cout << (it++)->literal_token << '\n';
    
    std::cout << "==================\n\n";
    LOG("" + it->literal_token);
    assign_all_in_scope(it, known.second);
    
}

