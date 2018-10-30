#include "scanner.hpp"

token_vector_t __tokenized_file;

#ifdef LAZY 
using namespace Tokens;
static std::vector<char> __known_operators__ = {
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
    {'*', SpecificToken::Asteriks           },
    {'<', SpecificToken::_Unknown           },
    {'>', SpecificToken::_Unknown           },
    
};


static std::map<char, SpecificToken> __logical_line_delim
{
    {';', SpecificToken::SemiColon},
    {'{', SpecificToken::OpenCurlyBracket},
    {'}', SpecificToken::CloseCurlyBracket},
};
#endif

/*
class Scanner {
    std::ifstream* _file;
    std::vector<char> _known_operators; // sizeof(std::vector) is 24
    std::map<char, Tokens::SpecificToken> logical_line_delim;
    //modularity will be added later
    //std::vector<char> _ignored_chars; 

    typedef std::vector<std::vector<Tokens::Token> > token_vector;
    token_vector __tokenized_file;

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

    const token_vector* get_tv() const { return &__tokenized_file; }
    //
};
*/
void Scanner::__init(std::string str, std::vector<char> ops, std::map<char, Tokens::SpecificToken> lld)
{
    _known_operators = ops;
    _logical_line_delim = lld;
    _file = new std::ifstream(str, std::ifstream::in);
    scan_lines();
}

Scanner::Scanner(std::string str)
{
    __init(str, __known_operators__, __logical_line_delim);
}

Scanner::Scanner(std::string str, 
                std::vector<char> operators, 
                std::map<char, Tokens::SpecificToken> logical_line_delim)
{
    __init(str, operators, logical_line_delim);
}



Tokens::Token* __attribute__((always_inline)) Scanner::request_new_line(line_num_t ln) const
{
    Tokens::Token tok(ln, Tokens::NEWLINE);
    __tokenized_file.push_back(tok);
    return &__tokenized_file.back();
}


bool __attribute__((always_inline)) 
Scanner::check_if_next_logical_line() const
{
    if (__tokenized_file.back().type == Tokens::NEWLINE)
        return true;

    return false;
}


Tokens::Token* Scanner::is_delim_char(char c, line_num_t ln) const
{
    for (auto const& [delim_char, token_enum] : _logical_line_delim)
        if (c == delim_char)
            return new Tokens::Token(ln, delim_char, Tokens::TokenType::LogicalLineDelim, token_enum);

    return nullptr;
}

Tokens::Token* Scanner::is_opperator(char c, line_num_t ln) const
{
    for (auto const& oper : _known_operators)
        if (c == oper)
            return new Tokens::Token(ln, oper, Tokens::TokenType::Operator, Tokens::SpecificToken::_Unknown);

    return nullptr;
}



void Scanner::scan_line(std::string line, line_num_t ln) const
{
    bool ll_delim_on_line = false;
    if (line[0] == '#') ll_delim_on_line = true;

    Tokens::Token* current_token = new Tokens::Token(ln);

    Tokens::Token* _operator = NULL;
    Tokens::Token* ll_delim = NULL;

    for (char c : line) {
        ll_delim = is_delim_char(c, ln);
        _operator = is_opperator(c, ln);

        if (ll_delim || _operator) {
            if (current_token->literal_token.size() > 0) {
                __tokenized_file.push_back(*current_token);
                delete current_token;
            }

            if (ll_delim) {
                __tokenized_file.push_back(*ll_delim);
                delete ll_delim;

                //request_new_line(ln);

                
            } else {
                __tokenized_file.push_back(*_operator);
                delete _operator;

            }

            current_token = new Tokens::Token(ln);

            continue;
        }

        else if (c == ' ' ) {
            if (current_token->literal_token.size() > 0) {
                __tokenized_file.push_back(*current_token);
                delete current_token;
            }
            current_token = new Tokens::Token(ln);
            continue;
        }

        current_token->literal_token += c;

    }
    
    if (ll_delim_on_line) {
        Tokens::Token newline(ln, Tokens::LogicalLineDelim);
        __tokenized_file.push_back(newline);
    }
    
}



void Scanner::scan_lines() const
{
    std::string str;
    for (int i = 1; !_file->eof(); i++) {
        std::getline(*_file, str);
        scan_line(str, i);
    }
}

void Scanner::print_vector() const 
{
        for (auto i : __tokenized_file) {
            
            
            std::cout << i.literal_token << ' ';

            if (i.type == Tokens::LogicalLineDelim)
                std::cout << '\n';
            
        }
}

token_vector_t& Scanner::get_tv() const
{
    return __tokenized_file;
}

