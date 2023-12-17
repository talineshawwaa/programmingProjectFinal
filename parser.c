#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#include "parser.h"

#define NULL  __DARWIN_NULL
#define __DARWIN_NULL ((void *)0)

int is_Obj (struct TokenList** tok, struct ParseTree** tree);

int is_List (struct TokenList** tok, struct ParseTree** tree);

int is_ListExpr (struct TokenList** tok, struct ParseTree** tree);

int is_Line(struct TokenList** tok, struct ParseTree** tree);

int is_Program(struct TokenList** head, struct ParseTree** tree);

int is_Expr(struct TokenList** head, struct ParseTree** tree);

int is_BaseExpr(struct TokenList** head, struct ParseTree** tree);

int is_Term(struct TokenList** head, struct ParseTree** tree);


struct ParseTree* alloc_ParseTree() {
    struct ParseTree* tree;
    tree = malloc(sizeof(struct ParseTree));
    if (tree == NULL)
        return NULL;
    tree->data = NULL;
    tree->child = NULL;
    tree->sibling = NULL;
    return tree;
}


struct ParseTree* new_ParseTree(struct Token* c) {
    struct ParseTree* tree;
    tree = alloc_ParseTree();
    if (tree == NULL)
        return NULL;
    tree->data = new_Token(c->lexeme, c->type);
    if (tree->data == NULL) {
        free(tree);
        return NULL;
    }
    tree->child = NULL;
    tree->sibling = NULL;
    return tree;
}


void print_PT(struct ParseTree* tree, int indent) {
    if (tree == NULL)
        return;
    if (indent > 0) {
        char space[indent + 1];
        memset(space, ' ', indent * sizeof(char));
        memset(space+indent, '\0', sizeof(char));
        printf("%s", space);
    }
    print_Token(tree->data);
    struct ParseTree* sibling;
    struct ParseTree* child;
    sibling = tree->sibling;
    child = tree->child;
    print_PT(child, indent + 2);
    print_PT(sibling, indent);
}

void print_ParseTree(struct ParseTree* tree) {
    print_PT(tree, 0);
}


void free_ParseTree(struct ParseTree* tree) {
    struct ParseTree* sibling;
    struct ParseTree* child;
    sibling = tree->sibling;
    child = tree->child;
    free_Token(tree->data);
    free(tree);
    if (sibling != NULL)
        free_ParseTree(sibling);
    if (child != NULL)
        free_ParseTree(child);
}

int __single_Token_template (struct TokenList** tok, struct ParseTree** new, enum TokenType type, char* lexeme, int hasEndline) {
    if (*tok == NULL)
        return PARSING_ERROR;
    struct TokenList* current = *tok;
    if (current->token->type != type) {
        printf("Expecting <%s>, Found <%s>\n", type2char(type), type2char(current->token->type));
        return PARSING_ERROR;
    }
    if (lexeme != NULL)
        if(strcmp(current->token->lexeme, lexeme) != 0) {
            printf("Expecting %s, Found %s\n", lexeme, current->token->lexeme);
            return PARSING_ERROR;
        }
    struct Token* newTok = new_Token(current->token->lexeme, current->token->type);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;
    (*new)->child = NULL;
    (*new)->sibling = NULL;
    *tok = current->next;
    if (hasEndline && *tok==NULL){
        printf("Did you forget a Endline Token (semicolon)?\n");
        return PARSING_ERROR;
    }
    return SUBTREE_OK;
}

int _single_Token_template (struct TokenList** tok, struct ParseTree** new, enum TokenType type, char* lexeme) {
    return __single_Token_template(tok, new, type, lexeme, 1);
}


int is_Endline (struct TokenList** tok, struct ParseTree** new) {
    return __single_Token_template(tok, new, ENDLINE, NULL, 0);
}


int is_Int (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, protons, NULL);
}


int is_Dot (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Dot, NULL);
}


int is_readIn (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, READIN, NULL);
}

int is_Var (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, VAR, NULL);
}

int is_React(struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, react, "react");
}


int is_Else (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, unreact, "unreact");
}

int is_ElseIf (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, intermediate, "intermediate");
}


int is_While (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, periodic, "periodic");
}

int is_For (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, molecular, "molecular");
}

int is_Break (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, zn, "zn");
}


int is_Lbrack (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Lbrack, NULL);
}


int is_Rbrack (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Rbrack, NULL);
}


int is_Lpar (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Lpar, NULL);
}


int is_Rpar (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Rpar, NULL);
}


int is_Comma (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Comma, NULL);
}


int is_NEQ (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, NEQ, NULL);
}


int is_Equal (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, EQ, NULL);
}


int is_Plus (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, PLUS, NULL);
}


int is_Minus (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, MINUS, NULL);
}


int is_Greater (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, GT, NULL);
}


int is_GreaterEq (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, GEQ, NULL);
}


int is_Lesser (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, LT, NULL);
}


int is_LesserEq (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, LEQ, NULL);
}


int is_Star (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, TIMES, NULL);
}


int is_Div (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, DIVIDE, NULL);
}

int is_writeOut (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, k, "k");
}

int is_FloatDiv (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, FLOATDIV, NULL);
}


int is_Percent (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Percent, NULL);
}


int is_Or (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, OR, NULL);
}


int is_And (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, AND, NULL);
}


int is_Pow (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, Pow, NULL);
}


int is_Null (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, (enum TokenType)0, NULL);
}

int is_CharSeq (struct TokenList** tok, struct ParseTree** new) {
    return _single_Token_template(tok, new, alkali, NULL);
}

//To identify strings, as Alkalis is our string library
int is_Alkali (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *charseq, *comma, *obj, *last;
    int status, nVar, nObj;
    struct Token *newTok;

    status = SUBTREE_OK;
    nVar = nObj = 0;

    newTok = new_Token((char[1]){'\0'}, alkali);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    charseq = alloc_ParseTree();
    if (charseq == NULL)
        return MEMORY_ERROR;
    status = is_CharSeq(tok, &charseq);
    if (status != SUBTREE_OK) {
        free_ParseTree(charseq);
        return status;
    }
    (*new)->child = charseq;
    last = charseq;

    int i = 0;
    while (charseq->data->lexeme[i] != '\0') {
        if (charseq->data->lexeme[i] == '%') {
            if (charseq->data->lexeme[i+1] == '%') 
                i += 2;
            else if (charseq->data->lexeme[i+1] == 's') {
                nVar += 1;
                i += 2;
            }
            else i++;
        }
        else i++;
    }

    while ((*tok)->token->type == Comma) {
        comma = alloc_ParseTree();
        if (comma == NULL)
            return MEMORY_ERROR;
        status = is_Comma(tok, &comma);
        if (status != SUBTREE_OK) {
            free_ParseTree(comma);
            break;
        }
        last->sibling = comma;
        last = comma;
        obj = alloc_ParseTree();
        if (obj == NULL)
            return MEMORY_ERROR;
        status = is_Obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_ParseTree(obj);
            break;
        }
        last->sibling = obj;
        last = obj;
        nObj ++;
    }

    if (nObj != nVar) {
        printf("QuotedStr with #obj != #interpolation (%d != %d)\n", nObj, nVar);
        return PARSING_ERROR;
    }
    return status;
}



int is_CondOp (struct TokenList** tok, struct ParseTree** new) {
    enum TokenType type;

    type = (*tok)->token->type;
    if (type == AND)
        return is_And(tok, new);
    else if (type == OR)
        return is_Or(tok, new);
    else if (type == NEQ)
        return is_NEQ(tok, new);
    else if (type == GT)
        return is_Greater(tok, new);
    else if (type == GEQ)
        return is_GreaterEq(tok, new);
    else if (type == LT)
        return is_Lesser(tok, new);
    else if (type == LEQ)
        return is_LesserEq(tok, new);
    else
        return PARSING_ERROR;
}

int is_Operator (struct TokenList** tok, struct ParseTree** new) {
    enum TokenType type;

    type = (*tok)->token->type;
    if (type == PLUS)
        return is_Plus(tok, new);
    else if (type == MINUS)
        return is_Minus(tok, new);
    else if (type == TIMES)
        return is_Star(tok, new);
    else if (type == DIVIDE)
        return is_Div(tok, new);
    else if (type == FLOATDIV)
        return is_FloatDiv(tok, new);
    else if (type == Percent)
        return is_Percent(tok, new);
    else
        return is_CondOp(tok, new);
}

int match_CondOp_type (enum TokenType type) {
    return (type == NEQ ||
            type == GT ||
            type == GEQ ||
            type == LT ||
            type == LEQ ||
            type == AND ||
            type == OR);
}

int match_AritmOp_type (enum TokenType type) {
    return (type == PLUS ||
            type == MINUS ||
            type == TIMES ||
            type == DIVIDE ||
            type == FLOATDIV ||
            type == Percent);
}


int match_TermOp_type (enum TokenType type) {
    return (type == TIMES ||
            type == DIVIDE ||
            type == FLOATDIV ||
            type == Percent);
}

int match_operator_type (enum TokenType type) {
    return (match_AritmOp_type(type) ||
            match_CondOp_type(type));
}

int is_BaseExpr (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    struct ParseTree *lpar, *rpar, *subexpr, *obj;
    struct Token *newTok;

    status = SUBTREE_OK;

    newTok = new_Token((char[1]){'\0'}, BASIC);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    if ((*tok)->token->type == Lpar) {
        lpar = alloc_ParseTree();
        if (lpar == NULL)
            return MEMORY_ERROR;
        status = is_Lpar(tok, &lpar);
        if (status != SUBTREE_OK){
            free_ParseTree(lpar);
            return status;
        }
        (*new)->child = lpar;

        subexpr = alloc_ParseTree();
        if (subexpr == NULL)
            return MEMORY_ERROR;
        status = is_Expr(tok, &subexpr);
        if (status != SUBTREE_OK){
            free_ParseTree(subexpr);
            return status;
        }
        lpar->sibling = subexpr;

        rpar = alloc_ParseTree();
        if (rpar == NULL)
            return MEMORY_ERROR;
        status = is_Rpar(tok, &rpar);
        if (status != SUBTREE_OK){
            free_ParseTree(rpar);
            return status;
        }
        subexpr->sibling = rpar;
    }
    else {
        obj = alloc_ParseTree();
        if (obj == NULL)
            return MEMORY_ERROR;
        status = is_Obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_ParseTree(obj);
            return status;
        }
        (*new)->child = obj;
    }
    return status;
}

int is_Term (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    enum TokenType type;
    struct ParseTree *base, *op, *term;
    struct Token *newTok;

    status = SUBTREE_OK;

    newTok = new_Token((char[1]){'\0'}, TERM);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    base = alloc_ParseTree();
    if (base == NULL)
        return MEMORY_ERROR;
    status = is_BaseExpr(tok, &base);
    if (status != SUBTREE_OK){
        free_ParseTree(base);
        return status;
    }
    (*new)->child = base;

    type = (*tok)->token->type;

    if (match_TermOp_type(type)){
        op = alloc_ParseTree();
        if (op == NULL)
            return MEMORY_ERROR;
        status = is_Operator(tok, &op);
        if (status != SUBTREE_OK){
            free_ParseTree(op);
            return status;
        }
        base->sibling = op;

        term = alloc_ParseTree();
        if (term == NULL)
            return MEMORY_ERROR;
        status = is_Term(tok, &term);
        if (status != SUBTREE_OK){
            free_ParseTree(term);
            return status;
        }
        op->sibling = term;
    }
    return status;
}

int is_Pred (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *term, *op, *pred;
    struct Token *newTok;
    enum TokenType type;
    int status;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, PRED);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    term = alloc_ParseTree();
    if (term == NULL)
        return MEMORY_ERROR;
    status = is_Term(tok, &term);
    if (status != SUBTREE_OK){
        free_ParseTree(term);
        return status;
    }
    (*new)->child = term;

    type = (*tok)->token->type;
    if (match_AritmOp_type(type) &&
        !match_TermOp_type(type)){
        op = alloc_ParseTree();
        if (op == NULL)
            return MEMORY_ERROR;
        status = is_Operator(tok, &op);
        if (status != SUBTREE_OK){
            free_ParseTree(op);
            return status;
        }
        term->sibling = op;

        pred = alloc_ParseTree();
        if (pred == NULL)
            return MEMORY_ERROR;
        status = is_Pred(tok, &pred);
        if (status != SUBTREE_OK){
            free_ParseTree(pred);
            return status;
        }
        op->sibling = pred;
    }

    return status;
}

int is_Expr (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *pred, *op, *expr;
    struct Token *newTok;
    enum TokenType type;
    int status;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, Expr);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    pred = alloc_ParseTree();
    if (pred == NULL)
        return MEMORY_ERROR;
    status = is_Pred(tok, &pred);
    if (status != SUBTREE_OK){
        free_ParseTree(pred);
        return status;
    }
    (*new)->child = pred;

    type = (*tok)->token->type;
    if (match_CondOp_type(type)){
        op = alloc_ParseTree();
        if (op == NULL)
            return MEMORY_ERROR;
        status = is_Operator(tok, &op);
        if (status != SUBTREE_OK){
            free_ParseTree(op);
            return status;
        }
        pred->sibling = op;

        expr = alloc_ParseTree();
        if (expr == NULL)
            return MEMORY_ERROR;
        status = is_Expr(tok, &expr);
        if (status != SUBTREE_OK){
            free_ParseTree(expr);
            return status;
        }
        op->sibling = expr;
    }
    return status;
}


int is_List(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *open, *listexpr, *close;
    int status, has_expr;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, LIST);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;
    has_expr = 0;
    open = alloc_ParseTree();
    if (open == NULL)
        return MEMORY_ERROR;

    status = is_Lbrack(tok, &open);
    if (status != SUBTREE_OK) {
        free_ParseTree(open);
        return status;
    }
    (*new)->child = open;

    if ((*tok)->token->type != Rbrack) {
        listexpr = alloc_ParseTree();
        if (listexpr == NULL)
            return MEMORY_ERROR;
        status = is_ListExpr(tok, &listexpr);
        if (status != SUBTREE_OK) {
            free_ParseTree(listexpr);
            return status;
        }
        has_expr = 1;
        open->sibling = listexpr;
    }

    close = alloc_ParseTree();
    if (close == NULL)
        return MEMORY_ERROR;
    status = is_Rbrack(tok, &close);
    if (status != SUBTREE_OK) {
        free_ParseTree(close);
        return status;
    }

    if (has_expr)
        listexpr->sibling = close;
    else
        open->sibling = close;
    return status;
}

int is_ListElem(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *var, *lbrack, *idx, *rbrack;
    int status;
    struct Token *newTok;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, LISTELEMENTS);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    var = alloc_ParseTree();
    if (var == NULL)
        return MEMORY_ERROR;
    status = is_Var(tok, &var);
    if (status != SUBTREE_OK) {
        free_ParseTree(var);
        return status;
    }
    (*new)->child = var;

    lbrack = alloc_ParseTree();
    if (lbrack == NULL)
        return MEMORY_ERROR;
    status = is_Lbrack(tok, &lbrack);
    if (status != SUBTREE_OK) {
        free_ParseTree(lbrack);
        return status;
    }
    var->sibling = lbrack;

    idx = alloc_ParseTree();
    if (idx == NULL)
        return MEMORY_ERROR;
    if ((*tok)->token->type == protons)
        status = is_Int(tok, &idx);
    else
        status = is_Var(tok, &idx);
    if (status != SUBTREE_OK) {
        free_ParseTree(idx);
        return status;
    }
    lbrack->sibling = idx;

    rbrack = alloc_ParseTree();
    if (rbrack == NULL)
        return MEMORY_ERROR;
    status = is_Rbrack(tok, &rbrack);
    if (status != SUBTREE_OK) {
        free_ParseTree(rbrack);
        return status;
    }
    idx->sibling = rbrack;

    return status;
}

int is_ListExpr(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *obj, *comma, *last;
    int status;
    struct Token* newTok;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, LISTEXPRESSION);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    obj = alloc_ParseTree();
    if (obj == NULL)
        return MEMORY_ERROR;

    status = is_Obj(tok, &obj);
    if (status != SUBTREE_OK) {
        free_ParseTree(obj);
        return status;
    }
    (*new)->child = obj;
    last = obj;

    while( (*tok)->token->type == Comma) {
        comma = alloc_ParseTree();
        if (comma == NULL)
            return MEMORY_ERROR;
        status = is_Comma(tok, &comma);
        if (status != SUBTREE_OK) {
            free_ParseTree(comma);
            return status;
        }
        last->sibling = comma;
        last = comma;
        obj = alloc_ParseTree();
        if (obj == NULL)
            return MEMORY_ERROR;
        status = is_Obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_ParseTree(obj);
            return status;
        }
        last->sibling = obj;
        last = obj;
    }
    return status;

}

int is_Str (struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *quotedstr, *plus, *last;
    int status;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, STRING);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;
    quotedstr = alloc_ParseTree();
    if (quotedstr == NULL)
        return MEMORY_ERROR;

    status = is_Alkali(tok, &quotedstr);
    if (status != SUBTREE_OK) {
        free_ParseTree(quotedstr);
        return status;
    }
    (*new)->child = quotedstr;
    last = quotedstr;

    while((*tok)->token->type == PLUS) {
        plus = alloc_ParseTree();
        if (plus == NULL)
            return MEMORY_ERROR;
        status = is_Plus(tok, &plus);
        if (status != SUBTREE_OK) {
            free_ParseTree(plus);
            return status;
        }
        last->sibling = plus;
        last = plus;

        if ((*tok)->token->type != alkali)
            return PARSING_ERROR;
        quotedstr = alloc_ParseTree();
        if (quotedstr == NULL)
            return MEMORY_ERROR;
        status = is_Alkali(tok, &quotedstr);
        if (status != SUBTREE_OK) {
            free_ParseTree(quotedstr);
            return status;
        }
        last->sibling = quotedstr;
        last = quotedstr;
    }
    return status;
}

int is_Frac (struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *dot, *integer;
    int status;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, FRACTION);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;
    dot = alloc_ParseTree();
    if (dot == NULL)
        return MEMORY_ERROR;

    status = is_Dot(tok, &dot);
    if (status != SUBTREE_OK) {
        free_ParseTree(dot);
        return status;
    }
    (*new)->child = dot;

    integer = alloc_ParseTree();
    if (integer == NULL)
        return MEMORY_ERROR;

    status = is_Int(tok, &integer);
    if (status != SUBTREE_OK) {
        free_ParseTree(integer);
        return status;
    }
    dot->sibling = integer;
    return status;
}

int is_Exp (struct TokenList** tok, struct ParseTree** new) {
    int status, has_sign;
    struct ParseTree *pow, *sign, *integer;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, Pow);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;
    has_sign = 0;
    pow = alloc_ParseTree();

    if (pow == NULL)
        return MEMORY_ERROR;

    status = is_Pow(tok, &pow);
    if (status != SUBTREE_OK) {
        free_ParseTree(pow);
        return status;
    }
    (*new)->child = pow;

    sign = alloc_ParseTree();
    if (sign == NULL)
        return MEMORY_ERROR;

    if ((*tok)->token->type == PLUS) {
        status = is_Plus(tok, &sign);
        has_sign = 1;
    }
    else if ((*tok)->token->type == MINUS) {
        status = is_Minus(tok, &sign);
        has_sign = 1;
    }

    if (has_sign && (status != SUBTREE_OK)) {
        free_ParseTree(sign);
        return status;
    }
    if (has_sign)
        (*new)->child->sibling = sign;
    else
        free_ParseTree(sign);

    integer = alloc_ParseTree();
    if (integer == NULL)
        return MEMORY_ERROR;

    status = is_Int(tok, &integer);
    if (status != SUBTREE_OK) {
        free_ParseTree(integer);
        return status;
    }

    if (has_sign)
        sign->sibling = integer;
    else
        (*new)->child->sibling = integer;
    return status;
}


int is_Float(struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *integer, *frac, *pow, *last;
    int status;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, electrons);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;

    if ((*tok)->token->type == Dot) {
        frac = alloc_ParseTree();
        if (frac == NULL)
            return MEMORY_ERROR;
        status = is_Frac(tok, &frac);
        if (status != SUBTREE_OK) {
            free_ParseTree(frac);
            return status;
        }
        (*new)->child = frac;
        last = frac;

        if ((*tok)->token->type == Pow) {
            pow = alloc_ParseTree();
            if (pow == NULL)
                return MEMORY_ERROR;
            status = is_Exp(tok, &pow);
            if (status != SUBTREE_OK) {
                free_ParseTree(pow);
                return status;
            }
            last->sibling = pow;
            last = pow;
        }
    }
    else if ((*tok)->token->type == protons) {
        integer = alloc_ParseTree();
        if (integer == NULL)
            return MEMORY_ERROR;
        status = is_Int(tok, &integer);
        if (status != SUBTREE_OK) {
            free_ParseTree(integer);
            return status;
        }
        (*new)->child = integer;
        last = integer;

        if ((*tok)->token->type == Dot) {
            frac = alloc_ParseTree();
            if (frac == NULL)
                return MEMORY_ERROR;
            status = is_Frac(tok, &frac);
            if (status != SUBTREE_OK) {
                free_ParseTree(frac);
                return status;
            }
            last->sibling = frac;
            last = frac;
        }
        if ((*tok)->token->type == Pow) {
            pow = alloc_ParseTree();
            if (pow == NULL)
                return MEMORY_ERROR;
            status = is_Exp(tok, &pow);
            if (status != SUBTREE_OK) {
                free_ParseTree(pow);
                return status;
            }
            last->sibling = pow;
            last = pow;
        }
    }
    else
        status = PARSING_ERROR;
    return status;
}

int is_Num(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *sign, *numeric;
    int status, has_sign;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, NUM);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    status = SUBTREE_OK;
    has_sign = 1;
    sign = alloc_ParseTree();

    if (sign == NULL)
        return MEMORY_ERROR;

    if ((*tok)->token->type == PLUS)
        status = is_Plus(tok, &sign);
    else if ((*tok)->token->type == MINUS)
        status = is_Minus(tok, &sign);
    else
        has_sign = 0;

    if (status != SUBTREE_OK) {
        free_ParseTree(sign);
        return status;
    }
    if (has_sign)
        (*new)->child = sign;
    else
        free_ParseTree(sign);

    numeric = alloc_ParseTree();
    if (numeric == NULL)
        return MEMORY_ERROR;

    status = is_Float(tok, &numeric);

    if (status != SUBTREE_OK)
        free_ParseTree(numeric);
    else {
        if (has_sign)
            sign->sibling = numeric;
        else
            (*new)->child = numeric;
    }
    return status;
}

int is_Obj(struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;
    struct Token* newTok;
    struct ParseTree* subtree;
    int status;

    newTok = new_Token((char[1]){'\0'}, OBJ);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    subtree = alloc_ParseTree();
    if (subtree == NULL)
        return MEMORY_ERROR;

    // use LL(1) FOLLOW Sets
    struct TokenList* curr;
    curr = *tok;

    if (curr->token->type == VAR)
        if (curr->next != NULL && curr->next->token->type == Lbrack)
            status = is_ListElem(tok, &subtree);
        else
            status = is_Var(tok, &subtree);
    else if (curr->token->type == UNKNOWN)
        status = is_Null(tok, &subtree);
    else if (curr->token->type == Lbrack)
        status = is_List(tok, &subtree);
    else if (curr->token->type == alkali)
        status = is_Str(tok, &subtree);
    else if (curr->token->type == protons ||
             curr->token->type == Dot ||
             curr->token->type == PLUS ||
             curr->token->type == MINUS)
        status = is_Num(tok, &subtree);
    else
        status = PARSING_ERROR;

    if (status == SUBTREE_OK)
        (*new)->child = subtree;
    else
        free_ParseTree(subtree);
    return status;
}

//chlorine: assigns a value to a variable
int is_Assign(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *var1, *eq, *var2;
    int status;
    struct Token *newTok;

    newTok = new_Token((char[1]) {'\0'}, cl);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    var1 = alloc_ParseTree();
    if (var1 == NULL)
        return MEMORY_ERROR;
    status = is_Var(tok, &var1);
    if (status != SUBTREE_OK) {
        free_ParseTree(var1);
        return PARSING_ERROR;
    }
    (*new)->child = var1;

    eq = alloc_ParseTree();
    if (eq == NULL)
        return MEMORY_ERROR;
    status = is_Equal(tok, &eq);
    if (status != SUBTREE_OK) {
        free_ParseTree(eq);
        return PARSING_ERROR;
    }
    var1->sibling = eq;

    var2 = alloc_ParseTree();
    if (var2 == NULL)
        return MEMORY_ERROR;

    status = is_Expr(tok, &var2);
    if (status != SUBTREE_OK) {
        free_ParseTree(var2);
        return PARSING_ERROR;
    }
    eq->sibling = var2;
    return SUBTREE_OK;
}


//copper, takes in the input
int is_Input(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *readin, *var;
    int status;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, cu);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    readin = alloc_ParseTree();
    if (readin == NULL)
        return MEMORY_ERROR;
    status = is_readIn(tok, &readin);
    if (status != SUBTREE_OK) {
        free_ParseTree(readin);
        return status;
    }
    (*new)->child = readin;

    var = alloc_ParseTree();
    if (var == NULL)
        return MEMORY_ERROR;
    status = is_Var(tok, &var);
    if (status != SUBTREE_OK) {
        free_ParseTree(var);
        return status;
    }
    readin->sibling = var;

    return SUBTREE_OK;
}

//potassium prints the output
int is_Output(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *writeOut, *obj;
    int status;
    struct Token* newTok;

    newTok = new_Token((char[1]){'\0'}, k);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    writeOut = alloc_ParseTree();
    if (writeOut == NULL)
        return MEMORY_ERROR;
    status = is_writeOut(tok, &writeOut);
    if (status != SUBTREE_OK) {
        free_ParseTree(writeOut);
        return status;
    }
    (*new)->child = writeOut;

    obj = alloc_ParseTree();
    if (obj == NULL)
        return MEMORY_ERROR;
    status = is_Obj(tok, &obj);
    if (status != SUBTREE_OK) {
        free_ParseTree(obj);
        return status;
    }
    writeOut->sibling = obj;

    return status;
}

//prints the else block
int is_OptElse (struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *elsetok, *line, *endline, *last;
    int status;
    struct Token* newTok;

    status = SUBTREE_OK;

    newTok = new_Token((char[1]){'\0'}, unreact);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    elsetok = alloc_ParseTree();
    if (elsetok == NULL)
        return MEMORY_ERROR;
    status = is_Else(tok, &elsetok);
    (*new)->child = elsetok;
    last = elsetok;
    if (status != SUBTREE_OK)
        return status;
    do{
        // else cannot be empty
        line = alloc_ParseTree();
        if (line == NULL)
            return MEMORY_ERROR;
        status = is_Line(tok, &line);
        last->sibling = line;
        last = line;
        if (status != SUBTREE_OK)
            return status;
        endline = alloc_ParseTree();
        if (endline == NULL)
            return MEMORY_ERROR;
        status = is_Endline(tok, &endline);
        last->sibling = endline;
        last = endline;
        if (status != SUBTREE_OK)
            return status;
    }
    while ( (*tok) != NULL && (*tok)->token->type != ENDLINE);
    return status;
}

int is_ReactBody(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *line, *endline, *last;
    int status, count;
    struct Token* newTok;

    status = SUBTREE_OK;
    count = 0;

    newTok = new_Token((char[1]){'\0'}, ReactBody);  // Assuming ReactBody is the enum value for "react" body
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;
    last = NULL;

    if ((*tok)->token->type == Lpar) {
        *tok = (*tok)->next;
    } else {
        free_ParseTree(*new);
        return PARSING_ERROR;
    }

    while ((*tok) != NULL &&
           (*tok)->token->type != Rpar) {  
        count++;
        line = alloc_ParseTree();
        if (line == NULL)
            return MEMORY_ERROR;
        status = is_Line(tok, &line);
        if (last == NULL)
            (*new)->child = line;
        else
            last->sibling = line;
        last = line;
        if (status != SUBTREE_OK)
            return status;

        endline = alloc_ParseTree();
        if (endline == NULL)
            return MEMORY_ERROR;
        status = is_Endline(tok, &endline);
        last->sibling = endline;
        last = endline;
        if (status != SUBTREE_OK)
            return status;
    }

    if ((*tok)->token->type == Rpar) {
        *tok = (*tok)->next;
    } else {
        free_ParseTree(*new);
        return PARSING_ERROR;
    }

    if (count == 0) {
        printf("ReactBody cannot be empty\n");
        return PARSING_ERROR;
    }

    return status;
}


int is_ReactCond(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *lpar, *expr, *rpar;
    int status;
    struct Token* newTok;
    status = SUBTREE_OK;

    newTok = new_Token((char[1]){'\0'}, ReactCond);  // Assuming ReactCond is the enum value for "react" condition
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    if ((*tok)->token->type == Lpar) {
        *tok = (*tok)->next;
    } else {
        free_ParseTree(*new);
        return PARSING_ERROR;
    }

    lpar = alloc_ParseTree();
    if (lpar == NULL)
        return MEMORY_ERROR;
    status = is_Lpar(tok, &lpar);
    (*new)->child = lpar;
    if (status != SUBTREE_OK)
        return status;

    expr = alloc_ParseTree();
    if (expr == NULL)
        return MEMORY_ERROR;
    status = is_Expr(tok, &expr);
    lpar->sibling = expr;
    if (status != SUBTREE_OK)
        return status;

    rpar = alloc_ParseTree();
    if (rpar == NULL)
        return MEMORY_ERROR;
    status = is_Rpar(tok, &rpar);
    expr->sibling = rpar;
    if (status != SUBTREE_OK)
        return status;
    if ((*tok)->token->type == Rpar) {
        *tok = (*tok)->next;
    } else {
        free_ParseTree(*new);
        return PARSING_ERROR;
    }
    return status;
}


int is_React2(struct TokenList** tok, struct ParseTree** new) {
    if (*tok == NULL)
        return PARSING_ERROR;

    struct ParseTree *reactToken;
    struct Token *newTok;
    int status;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, react); 
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    reactToken = alloc_ParseTree();
    if (reactToken == NULL)
        return MEMORY_ERROR;

    if ((*tok)->token->type == react) {
        *tok = (*tok)->next;
    } else {
        free_ParseTree(reactToken);
        return PARSING_ERROR;
    }

    (*new)->child = reactToken;

    return status;
}

int is_PeriodicLine(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *periodickey, *ifcond, *loopbody;
    int status;
    struct Token* newTok;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, periodic);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    periodickey = alloc_ParseTree();
    if (periodickey == NULL)
        return MEMORY_ERROR;
    status = is_While(tok, &periodickey);  
    (*new)->child = periodickey;
    if (status != SUBTREE_OK)
        return status;

    ifcond = alloc_ParseTree();
    if (ifcond == NULL)
        return MEMORY_ERROR;
    status = is_ReactCond(tok, &ifcond);
    periodickey->sibling = ifcond;
    if (status != SUBTREE_OK)
        return status;

    loopbody = alloc_ParseTree();
    if (loopbody == NULL)
        return MEMORY_ERROR;
    status = is_Program(tok, &loopbody);
    if (status != SUBTREE_OK) {
        free_ParseTree(loopbody);
        return status;
    }
    ifcond->sibling = loopbody;

    return status;
}

int is_MolecularLine(struct TokenList** tok, struct ParseTree** new) {
    struct ParseTree *molecularkey, *forcond, *loopbody;
    int status;
    struct Token* newTok;

    status = SUBTREE_OK;
    newTok = new_Token((char[1]){'\0'}, molecular);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*new)->data = newTok;

    molecularkey = alloc_ParseTree();
    if (molecularkey == NULL)
        return MEMORY_ERROR;
    status = is_For(tok, &molecularkey);  
    (*new)->child = molecularkey;
    if (status != SUBTREE_OK)
        return status;

    forcond = alloc_ParseTree();
    if (forcond == NULL)
        return MEMORY_ERROR;
    status = is_ReactCond(tok, &forcond);  
    molecularkey->sibling = forcond;
    if (status != SUBTREE_OK)
        return status;

    loopbody = alloc_ParseTree();
    if (loopbody == NULL)
        return MEMORY_ERROR;
    status = is_Program(tok, &loopbody);
    if (status != SUBTREE_OK) {
        free_ParseTree(loopbody);
        return status;
    }
    forcond->sibling = loopbody;

    return status;
}

int is_Line(struct TokenList** tok, struct ParseTree** line) {
    struct ParseTree* subtree;
    struct Token* newTok;
    int status;
    struct TokenList* curr;

    newTok = new_Token((char[1]){'\0'}, LINE);
    if (newTok == NULL)
        return MEMORY_ERROR;
    (*line)->data = newTok;

    subtree = alloc_ParseTree();
    if (subtree == NULL)
        return MEMORY_ERROR;

    curr = *tok;
    if (curr->token->type == cu)
        status = is_Input(tok, &subtree);
    else if (curr->token->type == k)
        status = is_Output(tok, &subtree);
    else if (curr->token->type == react)
        status = is_React(tok, &subtree);
    else if (curr->token->type == periodic)
        status = is_PeriodicLine(tok, &subtree);
    else if (curr->token->type == molecular)
        status = is_MolecularLine(tok, &subtree);
    else if (curr->token->type == zn)
        status = is_Break(tok, &subtree);
    else if (curr->token->type == cl)
        status = is_Assign(tok, &subtree);
    else
        status = PARSING_ERROR;

    (*line)->child = subtree;
    return status;
}

int is_Program(struct TokenList** head, struct ParseTree** tree) {
    struct Token *tok;
    int status, child;
    struct ParseTree *current;
    struct ParseTree *line, *endline;
    
    tok = new_Token((char[1]){'\0'}, FRANCIUM);
    if (tok == NULL)
        return MEMORY_ERROR;
    (*tree)->data = tok;

    line = alloc_ParseTree();
    endline = alloc_ParseTree();
    if (line == NULL || endline == NULL) {
        free(line);
        free(endline);
        return MEMORY_ERROR;
    }

    current = *tree; 
    
    child = 1; 
    while ((*head) != NULL &&
           (*head)->token->type != ENDLINE) {

        status = is_Line(head, &line);

        if (child) {
            current->child = line;
            child = !child;
        }
        else
            current->sibling = line;

        current = line;
        line = alloc_ParseTree();
        if (status != SUBTREE_OK) {
            printf("ERROR PARSING LINE: %d\n", status);
            break;
        }

        status = is_Endline(head, &endline);
        current->sibling = endline;
        current = endline;
        endline = alloc_ParseTree();
        if (status != SUBTREE_OK) {
            printf("Missing ENDLINE\n");
            break;
        }
    }
    free_ParseTree(line);
    free_ParseTree(endline);

    return status;
}


int build_ParseTree (struct TokenList* head, struct ParseTree** tree) {
    int status;

    status = is_Program(&head, tree);
    return status;
}


int build_ParseTree_FromFile (const char *fileName, struct ParseTree **tree) {
    FILE *file;
    char *vec;
    struct stat buffer;
    struct TokenList *list, *list2;
    int status;

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Cannot read the given file path.\n");
        return MEMORY_ERROR;
    }
    stat(fileName, &buffer);
    vec = malloc((buffer.st_size + 1) * sizeof(char));
    if (vec == NULL)
        return MEMORY_ERROR;
    fread(vec, sizeof(char), buffer.st_size, file);
    fclose(file);
    *(vec+buffer.st_size) = '\0';
    const char *fp = vec;

    list = build_TokenList(fp);

    if (list == NULL)
        return MEMORY_ERROR; 
    list2 = strip_WS(list);
    free_TokenList(list);

    status = build_ParseTree(list2, tree);

    free_TokenList(list2);
    free(vec);
    return status;

}