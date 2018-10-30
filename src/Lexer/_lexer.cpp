#include "./_lexer.hpp"

extern token_vector_t __tokenized_file;

/**
 * This approach was chosen because the assumtion is that
 * logical lines are not very long so even if our iterator 
 * is at the end of the line, causing many iterator hops,
 * this is still more ideal than creating an extra 
 * vec_iter_t. We are more starved for memory than we are
 * for cpu time in a lexer.
 */ 
LogicalLine find_lines(vec_iter_t start)
{
    for(; start->type != Tokens::TokenType::LogicalLineDelim; start--); //find start
    LogicalLine ret(start++); 
    for(; start->type != Tokens::TokenType::LogicalLineDelim; start++);
    ret.end = start;
    return ret;
}


/**
 * This function returns the scope in which
 * 'current_token' is in
 * 
 * not at all finished. complicated function
 */ 
const std::pair<ScopeType, Tokens::Token> get_scope(vec_iter_t current_token) 
{
    vec_iter_t i = current_token; 
    while(i != __tokenized_file.begin()) 
    {
        if (i->type == Tokens::TokenType::FunctionDefinition)
            return std::pair(ScopeType::Function, *i);

        i--;
    }
    return std::pair(ScopeType::Global, *i);
}
