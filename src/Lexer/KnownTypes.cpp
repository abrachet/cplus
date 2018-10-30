#include "./lexer.hpp"
#include "./_lexer.hpp"
#include "./KnownTypes.hpp"
#include <vector>
#include <string>
#include <iostream>


extern std::vector<KnownType> known_types;


std::pair<bool, KnownType&> get_kt(std::string str)
{
    typedef std::pair<bool, KnownType&> return_type;
    for (auto& i : known_types)
        if (i.ID == str)
            return return_type(true, i); //problem here

    return return_type(false, known_types[0]); 
    //doesnt matter what known type is, nothing was found
}

/**
 * resolves aliases 
 * typedef uint32_t u32_t;
 * u32_t gets added to known types with aliasing unsigned int
 * not uint32_t already an alias.
 * 
 * import to note lexer doesnt yet care about primitive types only structs
 */ 
void typedef_add(std::string aliases, Tokens::Token token)
{
    auto found = get_kt(aliases);
    if (!found.first) {
        //some kind of error
        std::cerr << aliases << " was not found\n";
    }
    
    kt_push_back( KnownType(token.literal_token, found.second) );
}

/**
 *  std::string ID;
    int8_t kind;
    union {
        UserTypes* type;
        KnownType& aliases;
    };
 * 
 */ 

//will currently go only 2 frames deep
//because every type is added with its primitive found
static KnownType& find_primitive(KnownType& kt)
{
    if (kt.kind == PRIMITIVE || kt.kind == ORIG_USER_TYPE)
        return kt;

    return find_primitive(kt.aliases);
}



void kt_push_back(KnownType kt)
{
    if (kt.kind == ORIG_USER_TYPE) {
        if(kt.ID.length() > 0)
            assert(0);
        assert(kt.type);

        ut_push_back(kt.type);

        
    } else if (kt.kind == ALIAS) {
        // find alias. not yet implemented
        // for now just warn
        if (!kt.type) 
            ERROR_MSG("NULL reference");
        
        // currently resolves where it ultimately points to
        // may change that later
        kt.aliases = find_primitive(kt);
        
    }

    known_types.push_back(kt);
    fm_push_back(kt.ID, UserTypeHandle);
}

KnownType::_kt_reference_t& KnownType::get_new_reference(bool ptr_type)
{
    _kt_reference_t pair;
    pair.first = ptr_type;
    references.push_back(pair);
    return references.back();

}


void KnownType::add_reference(Tokens::Token token, _kt_reference_t& vec)
{
    vec.second.push_back(token);
}

//just pushes back to references.back().second();
void KnownType::add_reference(Tokens::Token tk)
{
    references.back().second.push_back(tk);
}