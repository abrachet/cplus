#pragma once

#include <string>
#include <vector>
#include <functional>
#include <map>
//#include <cstdlib>

namespace Tokens {

typedef unsigned long long line_num_t;
typedef std::vector<std::string> vec_string;

enum TokenType {
    Unknown,
    Keyword,
    Operator,
    Literal,
    IdentifierObject,
    IdentifierFunction,
    Seperator,
    LogicalLineDelim,
    Preprocessor,

    ObjectDefinition,

    FunctionDefinition,


    GLOBAL_SCOPE, //should not be used by get_scope() from _lexer.cpp
    NEWLINE,
};

enum SpecificToken {
    _Unknown,

    OpenSqaureBracket,
    CloseSquareBracket,

    OpenCurlyBracket,
    CloseCurlyBracket,

    SemiColon,

    OpeningParenthesis,
    ClosingParenthesis,

    Asteriks,
    Ampersand,

    Equals,

    Comma, // ','
    Dot,   // '.'
    Minus, // '-'


    IntegralType,
    TypeSpecifer,
    
    
};

static std::map<SpecificToken, std::string> token_to_literal;

struct Token {
    TokenType type;
    SpecificToken token;
    std::string literal_token;
    uint64_t line;

    Token()
    {}

    Token(uint64_t line) : type(Unknown), token(_Unknown), line(line)
    {}

    Token(uint64_t line, TokenType type) : type(type), token(_Unknown), line(line) 
    {}

    Token(uint64_t line, std::string literal_token, TokenType type)
    : type(type), token(SpecificToken::_Unknown), literal_token(literal_token), line(line)
    {}

    Token(uint64_t line, const char literal_token, TokenType type, SpecificToken token)
    : type(type), token(token), line(line)
    {
        char* c_str = new char[2];
        c_str[0] = literal_token;
        c_str[1] = 0;
        std::string str(c_str);
        delete[] c_str;
        Token::literal_token = str;
        
    }

    ~Token() 
    {}

};


// TokenType::keyword
const static vec_string integral_types {
    "void",
    "char",
    "short",
    "int",
    "float",
    "double",
};


// TokenType::keyword
const static vec_string type_specifiers {
    "signed",
    "unsigned",

    "long",

    "register",

    "extern",

    "static",

    "const",
    "volatile",

    "restrict"   
};



// TokenType::Keyword
const static vec_string objects {
    "struct",
    "class",
    "union",
    "enum",
};

// TokenType::Keyword
const static vec_string logical_constructs {
    "for",

    "do",
    "while",

    "switch",
    "case",
    "default",

    "break",
    "continue",

    "if",
    "else",

    "goto",

    "return"

};


// TokenType::Operator
const static vec_string known_operators {
    "[", "]",
    ",", ".", "-", "="
    "+", "-", "*", "/",
    "!", "~", "=", ">", "<", 
    "&", "|", "^",

    //"sizeof",

};

// TokenType::Seperator
const static vec_string seperator {
    "{", "}", ";", "(", ")",
};

// TokenType::Preprocessor
const static vec_string preprocessor {
    "#"
};

#ifdef TARGET_PP
const static vec_string preprocessor {
    "#",
    "ifdef",
    "ifndef",
    "define",
    "include",
};
#endif
#ifdef TARGET_CPP
const static vec_string cpp_only {
    "class",
    "public",
    "private",
};
#endif


//vector<vector<string> >
const static std::vector<vec_string> vec {
    integral_types,
    type_specifiers,
    objects,
    logical_constructs,
    known_operators,
    seperator,
    preprocessor,
};

}
