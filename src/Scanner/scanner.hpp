#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "./tokens.hpp"

/**
 * 
 * TODO:
 * change token_vector_t into a single vector<Token> where tokens have LOGICAL_LINE type
 * this lets us easily use an iterator to iterate through multiple lines
 * 
 */ 

typedef uint64_t line_num_t;
//typedef std::vector<std::vector<Tokens::Token> > token_vector_t;
//typedef std::vector<Tokens::Token> logical_line_vec;

typedef std::vector<Tokens::Token> token_vector_t;

//#define LAZY


class Scanner {
    std::ifstream* _file;
    std::vector<char> _known_operators; // sizeof(std::vector) is 24
    std::map<char, Tokens::SpecificToken> _logical_line_delim;
    //modularity will be added later
    //std::vector<char> _ignored_chars; 

    std::string read_line() const;

    //logical_line_vec* check_if_next_logical_line() const;
    bool check_if_next_logical_line() const; //?
    Tokens::Token* is_opperator(char c, line_num_t ln) const;

    //logical_line_vec* request_new_line() const;
    Tokens::Token* request_new_line(line_num_t) const;

    void scan_line(std::string, line_num_t) const;

    Tokens::Token* is_delim_char(char, line_num_t) const;

    void scan_lines() const;

    void __init(std::string, std::vector<char>, std::map<char, Tokens::SpecificToken>);
    public:
    
    Scanner(std::string);
    Scanner(std::string, std::vector<char>, std::map<char, Tokens::SpecificToken>);

    ~Scanner() { delete _file; }

    void print_vector() const;

    token_vector_t& get_tv() const;

};
