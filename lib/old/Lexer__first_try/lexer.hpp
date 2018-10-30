#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <map>
#include <functional>


#include "./LFA.hpp"


#include "UserTypes.hpp"




// Jessie is the best hehe Jessie power allows bae to finish coding fast and have fun with Jessie =.= :3

class Lexer 
{
    public:

    struct LexerFunctionArg {
        std::vector<Tokens::Token> current_line;
        std::vector<Tokens::Token>::iterator iterator;
        Tokens::Token current_token;


        LexerFunctionArg(std::vector<Tokens::Token>& cl)
        : current_line(cl)
        {}

        LexerFunctionArg(std::vector<Tokens::Token> cl, std::vector<Tokens::Token>::iterator ct)
        : current_line(cl), iterator(ct)
        {}

        LexerFunctionArg(std::vector<Tokens::Token> cl, Tokens::current_token ct) 
        : current_line(cl), current_token(ct)
        {}
        
    };

    static void null_func(LexerFunctionArg& lfa) { return; }

    static std::map<std::vector<std::string>, std::function<void(LexerFunctionArg&)> > _base_map;

    private:

    Tokens::Token find_end_of_struct(Lexer::LexerFunctionArg&);
    void object_type_handle(LexerFunctionArg& lfa);
    void ObjectsHandle(LexerFunctionArg&);

    private:

    /**
     * data members
     */ 
    std::vector<std::vector<Tokens::Token> > _token_vec;

    std::vector<UserTypes> _current_types;

    /**
     * member functions
     */ 
    std::function<void(LexerFunctionArg&)> find_handle_func(std::string);

    const std::vector<std::string>& type_vec() { return _base_map.begin()->first; }

    void lexlines();

    public:
    Lexer(std::vector<std::vector<Tokens::Token> > token_vec) 
    : _token_vec(token_vec) 
    {}

    void add_to_types(UserTypes ut) { _current_types.push_back(ut); }
    std::vector<std::vector<Tokens::Token> >& get_token_vec() { return _token_vec; }


}; /* class lexer */


#endif /* LEXER_H */
