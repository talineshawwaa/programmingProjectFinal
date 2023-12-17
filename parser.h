#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

struct ParseTree {
    struct Token* data;
    struct ParseTree* child;
    struct ParseTree* sibling;
};


#define PARSING_ERROR -1
#define SUBTREE_OK 0
#define MEMORY_ERROR 1

struct ParseTree* new_ParseTree(struct Token* c);

struct ParseTree* alloc_ParseTree();

void print_ParseTree(struct ParseTree* tree);

void free_ParseTree(struct ParseTree* tree);

int build_ParseTree (struct TokenList* head, struct ParseTree** tree);

int build_ParseTree_FromFile (const char *fileName, struct ParseTree **tree);

#endif 