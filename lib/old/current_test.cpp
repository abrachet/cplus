#include "./tokens.hpp"
#include "./Scanner/scanner.hpp"
#include "./Lexer/lexer.hpp"


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

    std::string str("easy_to_scan.c+");

    Scanner scanner(str, known_operators, logical_line_delim);

    //scanner.scan_lines();

}