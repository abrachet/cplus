#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "../tokens.hpp"

typedef uint64_t line_num_t;
typedef std::vector<Tokens::Token> logical_line_vec;
typedef std::vector<logical_line_vec> token_vector;


class Scanner {
    std::ifstream* _file;
    std::vector<char> _known_operators; // sizeof(std::vector) is 24
    std::map<char, Tokens::SpecificToken> logical_line_delim;
    //modularity will be added later
    //std::vector<char> _ignored_chars; 

    typedef std::vector<std::vector<Tokens::Token> > token_vector;
    token_vector _token_vector;

    std::string read_line() const;

    logical_line_vec* check_if_next_logical_line();
    Tokens::Token* is_opperator(char c, line_num_t ln);

    logical_line_vec* request_new_line();

    void scan_line(std::string, line_num_t);

    Tokens::Token* is_delim_char(char, line_num_t);

    void scan_lines();

    public:
    

    Scanner(const std::string&);
    Scanner(std::string, std::vector<char>&, std::map<char, Tokens::SpecificToken>&);

    ~Scanner() { delete _file; }

    void print_vector() const;

    

    const token_vector* get_tv() const { return &_token_vector; }

};

#endif /* SCANNER_H */
