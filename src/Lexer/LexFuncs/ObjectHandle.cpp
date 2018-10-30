/**
 * Alex Brachet-Mialot
 * 
 * ObjectHandle() gets invoked upon seeing the 'struct' or 'class' keywords
 * 
 */ 


#include "../_lexer.hpp"

#include <vector>
#include <string>

extern std::vector<UserTypes> user_types;
extern std::vector<KnownType> known_types;


token_vector_t::iterator find_end_of_struct(FuncArg);


std::string get_name(vec_iter_t it)
{
    it++;
    return it->literal_token;
}

void ObjectHandle(FuncArg arg)
{
    UserTypes* ut = new UserTypes;
    ut->_ID = get_name(arg.it);
    ut->start = arg.it; // at keyword "struct"
    ut->end = find_end_of_struct(arg);
    
    //std::string msg = "ObjectHandle called with object: " + ut->ID;
    INFO_MSG("ObjectHandle called with object: " + ut->_ID);


    //void ut_push_back(UserTypes*);
    ut_push_back(ut);


    //known_types.push_back(KnownTypes(ut._ID, ut));
    //user_types.push_back(*ut);
    

}


token_vector_t::iterator find_end_of_struct(FuncArg arg)
{
    int stack = 0;

    //finding first '{'
    auto& token = arg.it;
    for (; token->literal_token != "{"; token++);
    
    for (; ; token++) {
        std::string lt = token->literal_token;
        if (lt == "{")
            stack++;
        else if (lt == "}")
            stack--;

        if (stack == 0) {
            return token;
        }

    }
}


/***
 * 
 * When Object handle. Push back the name of the object to function map with function UserTypeHandle
 * 
 * 
 */
