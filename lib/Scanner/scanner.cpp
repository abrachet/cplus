#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "scanner.hpp"

/**
 * 
 * read line. pass line and line number to function construct_token_vec()
 * 
 * construct_token_vec will look at vector in its class and see if 
 * at_back().at_back().token_type is a delim token.
 * 
 * if it is, then it will be first appending a vector to that main vector
 * else it will be appending tokens into the vector inside of the main vector
 * 
 */
typedef uint64_t line_num_t;
typedef std::vector<Tokens::Token> logical_line_vec;
typedef std::vector<logical_line_vec> token_vector;

/*
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

    public:
    

    Scanner(const std::string&);
    Scanner(std::string, std::vector<char>&, std::map<char, Tokens::SpecificToken>&);

    ~Scanner() { delete _file; }

    void print_vector() const;

    void scan_lines();

    const token_vector* get_tv() const { return &_token_vector; }

};
*/
Scanner::Scanner(std::string str, 
                std::vector<char>& operators, 
                std::map<char, Tokens::SpecificToken>& logical_line_delim)
: _known_operators(operators), logical_line_delim(logical_line_delim)
{
    _file = new std::ifstream(str, std::ifstream::in);
    scan_lines();
}



logical_line_vec* __attribute__((always_inline)) Scanner::request_new_line() 
{
    logical_line_vec llv;
    _token_vector.push_back(llv);
    return &_token_vector.back();
}


logical_line_vec* Scanner::check_if_next_logical_line()
{
    if (_token_vector.empty())
        return request_new_line();

    if (_token_vector.back().empty())
        return &_token_vector.back();

    if (_token_vector.back().back().type == Tokens::TokenType::LogicalLineDelim)
        return request_new_line();

    return &_token_vector.back();
}


Tokens::Token* Scanner::is_delim_char(char c, line_num_t ln)
{
    for (auto const& [delim_char, token_enum] : logical_line_delim)
        if (c == delim_char)
            return new Tokens::Token(ln, delim_char, Tokens::TokenType::LogicalLineDelim, token_enum);

    return nullptr;
}

Tokens::Token* Scanner::is_opperator(char c, line_num_t ln)
{
    for (auto const& oper : _known_operators)
        if (c == oper)
            return new Tokens::Token(ln, oper, Tokens::TokenType::Operator, Tokens::SpecificToken::_Unknown);

    return nullptr;
}



void Scanner::scan_line(std::string line, line_num_t ln)
{
    logical_line_vec* current_ll = check_if_next_logical_line();

    Tokens::Token* current_token = new Tokens::Token(ln);

    Tokens::Token* _operator = NULL;
    Tokens::Token* ll_delim = NULL;

    for (char c : line) {
        ll_delim = is_delim_char(c, ln);
        _operator = is_opperator(c, ln);

        if (ll_delim || _operator) {
            if (current_token->literal_token.size() > 0) {
                current_ll->push_back(*current_token);
                delete current_token;
            }

            if (ll_delim) {
                current_ll->push_back(*ll_delim);
                delete ll_delim;

                current_ll = request_new_line();
            } else {
                current_ll->push_back(*_operator);
                delete _operator;

            }

            current_token = new Tokens::Token(ln);

            continue;
        }

        else if (c == ' ' ) {
            if (current_token->literal_token.size() > 0) {
                current_ll->push_back(*current_token);
                delete current_token;
            }
            current_token = new Tokens::Token(ln);
            continue;
        }

        current_token->literal_token += c;

    }
    #if 0
    if (current_token)
        delete current_token;
    if (_operator)
        delete _operator;
    if(ll_delim)
        delete ll_delim;
    #endif
}


void Scanner::print_vector() const
{
    for (auto i : _token_vector) {
        for (auto j : i) 
            std::cout << j.literal_token << ' ';

        std::cout << '\n';
    }
}


void Scanner::scan_lines()
{
    std::string str;
    for (int i = 1; !_file->eof(); i++) {
        std::getline(*_file, str);
        scan_line(str, i);
    }
}

/*

using namespace Tokens;
int main()
{
    static std::vector<char> known_operators = {
        '[', ']', '(', ')',
        ',', '.', '-', '=',
        '+', '-', '*', '/',
        '!', '~', '=', '>', '<', 
        '&', '|', '^',
    };

    static std::map<char, Tokens::SpecificToken> operator_map
    {
        {'[', SpecificToken::OpenSqaureBracket  },
        {']', SpecificToken::CloseSquareBracket },
        {'(', SpecificToken::OpenCurlyBracket   },
        {')', SpecificToken::CloseCurlyBracket  },
        {',', SpecificToken::Comma              },
        {'.', SpecificToken::Dot                },
        {'-', SpecificToken::Minus              },
        {'=', SpecificToken::Equals             },
        
    };


    static std::map<char, SpecificToken> logical_line_delim;

    logical_line_delim[';'] = SpecificToken::SemiColon;
    logical_line_delim['{'] = SpecificToken::OpenCurlyBracket;
    logical_line_delim['}'] = SpecificToken::CloseCurlyBracket;
    //logical_line_delim['('] = SpecificToken::OpeningParenthesis;
    //logical_line_delim[')'] = SpecificToken::ClosingParenthesis;


    std::string str("easy_to_scan.c+");

    Scanner scanner(str, known_operators, logical_line_delim);


    scanner.scan_lines();

    scanner.print_vector();


    auto vec = scanner.get_tv();

    std::cout << "Length of first is: " << vec->at(0).size() << '\n';


    std::cout << '\n';

}
*/