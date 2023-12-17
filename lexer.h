#ifndef LEXER_H
#define LEXER_H

enum TokenType{
    H,
    C,
    Ne,
    au,
    Hg,
    fe,
    si,
    w,
    zn,
    p,
    cu,
    fluorine,
    kr,
    oxy,
    k,
    FRANCIUM,
    StringLiteral,
    ca,
    cl,
    ReactBody,
    ReactCond,
    LINE,
    Expr,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    FLOATDIV,
    ENDLINE,
    EQ,
    READIN,
    UNKNOWN,
    BASIC,
    TERM,
    PRINT,
    PRED,
    LIST,
    LISTELEMENTS,
    LISTEXPRESSION,
    FRACTION,
    NUM,
    OBJ,
    VAR,
    STRING,
    NEQ,
    LT,
    LEQ,
    GT,
    GEQ,
    AND,
    OR,
    NOT,
    Lbrack,
    Rbrack,
    Comma,
    Lpar,
    Rpar,
    Lcurly,
    Rcurly,
    Percent,
    Pow,
    Dot,
    react, 
    unreact,
    intermediate,
    molecular, 
    periodic,
    protons,
    electrons, 
    neutrons, 
    cloud,
    alkali,
    halogens,
    nobles,
    transition,
    WS,
};

const char* type2char (enum TokenType t);

struct Token{
    char* lexeme;
    enum TokenType type;
};

struct TokenList{
    struct Token* token;
    struct TokenList* next;
};



void print_Token(struct Token* p);

void print_TokenList(struct TokenList* p);

void free_Token(struct Token* tok);

void free_TokenList(struct TokenList* tok);

struct Token* new_Token(char* lexeme, enum TokenType tok);

struct TokenList* new_TokenList(struct Token* tok);

struct TokenList* build_TokenList(const char* fp);

struct TokenList* strip_WS(struct TokenList* list);

#endif