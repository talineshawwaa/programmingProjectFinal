#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "lexer.h"

#define MAX_LINE 100

void skip_WS(struct TokenList** list);


const char* type2char (enum TokenType t){
    switch (t)
    {
        case H: return "H**";
        case C: return "C";
        case Ne: return "Ne";
        case au: return "au";
        case Hg: return "hg";
        case fe: return "fe";
        case si: return "si";
        case w: return "w";
        case zn: return "zn";
        case p: return "p";
        case cu: return "cu";
        case fluorine: return "fluorine";
        case kr: return "kr";
        case oxy: return "oxy";
        case k: return "k";
        case FRANCIUM: return "FRANCIUM RADIATION";
        case StringLiteral: return "StringLiteral";
        case ca: return "!!ca";
        case cl: return "cl";
        case ReactBody: return "ReactBody";
        case ReactCond: return "ReactCond";
        case LINE: return "LINE";
        case Expr: return "Expr";
        case PLUS: return "PLUS";
        case MINUS: return "Minus";
        case TIMES: return "Times";
        case DIVIDE: return "Divide";
        case FLOATDIV: return "FLOATDIV";
        case ENDLINE: return "ENDLINE";
        case EQ: return "EQ";
        case READIN: return "READIN";
        case UNKNOWN: return "UNKNOWN";
        case BASIC: return "BASIC";
        case TERM: return "TERM";
        case PRED: return "PRED";
        case LIST: return "LIST";
        case LISTELEMENTS: return "LISTELEMENTS";
        case LISTEXPRESSION: return "LISTEXPRESSION";
        case FRACTION: return "FRACTION";
        case NUM: return "NUM";
        case OBJ: return "OBJ";
        case VAR: return "VAR";
        case STRING: return "STRING";
        case NEQ: return "NEQ";
        case LT: return "LT";
        case LEQ: return "LEQ";
        case GT: return "GT";
        case GEQ: return "GEQ";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case Lbrack: return "Lbrack";
        case Rbrack: return "Rbrack";
        case Comma: return "Comma";
        case Lpar: return "Lpar";
        case Rpar: return "Rpar";
        case Lcurly: return "Lcurly";
        case Rcurly: return "Rcurly";
        case Percent: return "Percent";
        case Pow: return "Pow";
        case Dot: return "Dot";
        case react: return "react";
        case unreact: return "unreact";
        case intermediate: return "intermediate";
        case molecular: return "molecular";
        case periodic: return "periodic";
        case protons: return "protons";
        case electrons: return "electrons";
        case neutrons: return "neutrons";
        case cloud: return "cloud";
        case alkali: return "alkali";
        case halogens: return "halogens";
        case nobles: return "nobles";
        case transition: return "transition";
        case WS: return "WS";
        default: return "UNKNOWN";
    }
}

void free_Token(struct Token* tok) {
    if (tok == NULL) {
        return;
    }
    free(tok->lexeme);
    free(tok);
}

void free_TokenList(struct TokenList* tok) {
    struct TokenList* current;
    while ((current = tok) != NULL) {
        tok = tok->next;
        free_Token(current->token);
        free(current);
    }
}

int alloc_failed(struct Token* tok, char* tmp) {
    printf("FAILED TO (RE)ALLOC");
    free_Token(tok);
    free(tmp);
    return -1;
}

void print_Token(struct Token* p) {
    if (p == NULL)
        printf("Token is NULL\n");
    else
        if (strlen(p->lexeme) == 0 || p->type == oxy)
            printf("<%s>\n", type2char(p->type));
        else
            printf("<|%s|, %s>\n", p->lexeme, type2char(p->type));
}

void print_TokenList(struct TokenList* p) {
    int i = 0;
    struct TokenList* current = p;
    while (current != NULL) {
        i++;
        print_Token(current->token);
        current = current->next;
    }
    printf("====================\n");
    printf("Found %d Tokens\n", i);
    printf("====================\n");
}

char consume(const char** p) {
    char c = **p;
    (*p)++;
    return c;
}

int skip_comment(const char** p) {
    if (**p != '!' || *(*p + 1) != '!') {
        printf("Bad call to comment !!\n");
        return 1;
    }
    while (**p != '\0' && **p != '\n') {
        consume(p); // Consume the comment characters until end of line or end of file
    }
    return 0;
}

int match_ws(const char** p, struct Token* tok) {

    if ( **p != ' ' &&
         **p != '\t' &&
         **p != '\r' &&
         **p != '\n')
    {
        printf("Bad call to whitespace!!");
        return 1;
    }
    int i = 0;
    char c;
    char* tmp;
    char ws[MAX_LINE] = "";
    do {
        if (i >= MAX_LINE - 1) {
            printf("Found more than %d white spaces\n", MAX_LINE);
            return 1;
        }
        c = consume(p); // p is incremented here
        ws[i++] = c;
    }
    while (**p == ' ' || **p == '\t' || **p == '\r' || **p == '\n');
    ws[i++] = '\0';
    tmp = realloc(tok->lexeme, i * sizeof(char));
    if (tmp == NULL)
        return alloc_failed(tok, tmp);
    else
        tok->lexeme = tmp;
    memcpy(tok->lexeme, ws, i);
    tok->type = WS;
    return 0;
}

int match_template(const char** p, struct Token* tok, char c, enum TokenType type) {

    if (**p != c) {
        printf("Bad call to |%c| !!\n", c);
        return 1;
    }
    char* tmp;
    consume(p);
    tmp = realloc(tok->lexeme, 2 * sizeof(char));
    if (tmp == NULL)
        return alloc_failed(tok, tmp);
    else
        tok->lexeme = tmp;
    memcpy(tok->lexeme, (char[2]) {c, '\0'}, 2);
    tok->type = type;
    return 0;
}

int match_lbrack(const char** p, struct Token* tok) {
    return match_template(p, tok, '[', Lbrack);
}

int match_rbrack(const char** p, struct Token* tok) {
    return match_template(p, tok, ']', Rbrack);
}

int match_plus(const char** p, struct Token* tok) {
    return match_template(p, tok, '+', PLUS);
}

int match_comma(const char** p, struct Token* tok) {
    return match_template(p, tok, ',', Comma);
}

int match_minus(const char** p, struct Token* tok) {
    return match_template(p, tok, '-', MINUS);
}

int match_lpar(const char** p, struct Token* tok) {
    return match_template(p, tok, '(', Lpar);
}

int match_rpar(const char** p, struct Token* tok) {
    return match_template(p, tok, ')', Rpar);
}

int match_lcurly(const char** p, struct Token* tok) {
    return match_template(p, tok, '{', Lcurly);
}

int match_rcurly(const char** p, struct Token* tok) {
    return match_template(p, tok, '}', Rcurly);
}

int match_star(const char** p, struct Token* tok) {
    return match_template(p, tok, '*', TIMES);
}

int match_percent(const char** p, struct Token* tok) {
    return match_template(p, tok, '%', Percent);
}

int match_pow(const char** p, struct Token* tok) {
    return match_template(p, tok, '^', Pow);
}

int match_dot(const char** p, struct Token* tok) {
    return match_template(p, tok, '.', Dot);
}

int match_equal(const char** p, struct Token* tok) {
    if (**p != '=') {
        printf("Bad call to = !\n");
        return 1;
    }
    char* tmp;

    consume(p);
    if (**p == '=') {
        consume(p);
        tmp = realloc(tok->lexeme, 3 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[3]) {'=', '=', '\0'}, 3 * sizeof(char));
        tok->type = NEQ;
    }
    else {
        tmp = realloc(tok->lexeme, 2 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[2]) {'=', '\0'}, 2 * sizeof(char));
        tok->type = EQ;
    }
    return 0;
}

int match_lesser(const char** p, struct Token* tok) {
    if (**p != '<') {
        printf("Bad call to < !\n");
        return 1;
    }
    char* tmp;
    consume(p);
    if (**p == '=') {
        consume(p);
        tmp = realloc(tok->lexeme, 3 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[3]) {'<', '=', '\0'}, 3 * sizeof(char));
        tok->type = LEQ;
    }
    else {
        tmp = realloc(tok->lexeme, 2 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[2]) {'<', '\0'}, 2 * sizeof(char));
        tok->type = LT;
    }
    return 0;
}

int match_greater(const char** p, struct Token* tok) {
    if (**p != '>') {
        printf("Bad call to > !\n");
        return 1;
    }
    char* tmp;
    consume(p);
    if (**p == '=') {
        consume(p);
        tmp = realloc(tok->lexeme, 3 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[3]) {'>', '=', '\0'}, 3 * sizeof(char));
        tok->type = GEQ;
    }
    else {
        tmp = realloc(tok->lexeme, 2 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[2]) {'>', '\0'}, 2 * sizeof(char));
        tok->type = GT;
    }
    return 0;
}

int match_div(const char** p, struct Token* tok) {
    if (**p != '/') {
        printf("Bad call to / !\n");
        return 1;
    }
    char* tmp;
    consume(p);
    if (**p == '.') {
        consume(p);
        tmp = realloc(tok->lexeme, 3 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[3]) {'/', '.', '\0'}, 3 * sizeof(char));
        tok->type = FLOATDIV;
    }
    else {
        tmp = realloc(tok->lexeme, 2 * sizeof(char));
        if (tmp == NULL)
            return alloc_failed(tok, tmp);
        else
            tok->lexeme = tmp;
        memcpy(tok->lexeme, (char[2]) {'/', '\0'}, 2 * sizeof(char));
        tok->type = DIVIDE;
    }
    return 0;
}

int match_two_template(const char** p, struct Token* tok, char c1, char c2, enum TokenType type) {

    if (**p != c1) {
        printf("Bad call to |%c| !\n", c1);
        return 1;
    }
    char* tmp;
    consume(p);
    if (**p != c2) {
        printf("Unrecognized Token. |%c| must be followed by |%c|\n", c1, c2);
        return 1;
    }
    consume(p);
    tmp = realloc(tok->lexeme, 3 * sizeof(char));
    if (tmp == NULL)
        return alloc_failed(tok, tmp);
    else
        tok->lexeme = tmp;
    memcpy(tok->lexeme, (char[3]) {c1, c2, '\0'}, 3 * sizeof(char));
    tok->type = type;
    return 0;
}

int match_noteq(const char** p, struct Token* tok) {
    return match_two_template(p, tok, '!', '=', NEQ);
}

int match_or(const char** p, struct Token* tok) {
    return match_two_template(p, tok, '|', '|', OR);
}

int match_and(const char** p, struct Token* tok) {
    return match_two_template(p, tok, '&', '&', AND);
}

int match_endline(const char** p, struct Token* tok) {
    return match_two_template(p, tok, ';', '\n', ENDLINE);
}

int match_int(const char** p, struct Token* tok) {

    if (**p < 48 || **p > 57) {
        printf("Bad call to int !!\n");
        return 1;
    }
    char* tmp;
    size_t curr_size = 8;
    char c;
    int totchar = 0;

    if (**p == '0') {
        c = consume(p);
        if (**p >= 48 && **p <= 57) {
            printf("Cannot have INT starting with 0\n");
            return 1;
        }
        memcpy(tok->lexeme, (char[2]) {'0', '\0'}, 2);
        tok->type = protons;
        return 0;
    }
    tmp = realloc(tok->lexeme, curr_size);
    if (tmp == NULL)
        return alloc_failed(tok, tmp);
    else
        tok->lexeme = tmp;
    while (**p >= 48 && **p <= 57) {
        c = consume(p);
        tok->lexeme[totchar++] = c;
        if (totchar * sizeof(char) >= curr_size) {
            tmp = realloc(tok->lexeme, 2*curr_size);
            if (tmp == NULL)
                return alloc_failed(tok, tmp);
            else
                tok->lexeme = tmp;
            curr_size *= 2;
        }
    }
    tmp = realloc(tok->lexeme, sizeof(char) * totchar + 1);
    if (tmp == NULL)
        return alloc_failed(tok, tmp);
    else
        tok->lexeme = tmp;
    tok->lexeme[totchar] = '\0';
    tok->type = protons;
    return 0;
}

int match_id(const char** p, struct Token* tok) {

    if (**p < 65 || **p > 122 || (**p > 90 && **p < 97)) {
        printf("Bad call to ID !!\n");
        return 1;
    }
    char* tmp;
    size_t curr_size = 16;
    int totchar = 0;
    tmp = realloc(tok->lexeme, curr_size);
    if (tmp == NULL)
        return alloc_failed(tok, tmp); 
    else
        tok->lexeme = tmp;
    while ((**p >= 48 && **p <= 57) ||
           (**p >= 65 && **p <= 90) ||
           (**p >= 97 && **p <= 122)) {
        tok->lexeme[totchar++] = **p;
        consume(p);
        if (totchar * sizeof(char) >= curr_size) {
            tmp = realloc(tok->lexeme, 2*curr_size);
            if (tmp == NULL)
                return alloc_failed(tok, tmp); 
            else
                tok->lexeme = tmp;
            curr_size *= 2;
        } 
    }
    tmp = realloc(tok->lexeme, sizeof(char) * totchar + 1);
    if (tmp == NULL)
        return alloc_failed(tok, tmp); 
    else
        tok->lexeme = tmp;
    tok->lexeme[totchar] = '\0';
    if (strcmp(tok->lexeme, "zn") == 0)
        tok->type = zn;
    else if (strcmp(tok->lexeme, "react") == 0)
        tok->type = react;
    else if (strcmp(tok->lexeme, "unreact") == 0)
        tok->type = unreact;
    else if (strcmp(tok->lexeme, "intermediate") == 0)
        tok->type = intermediate;
    else if (strcmp(tok->lexeme, "periodic") == 0)
        tok->type = periodic;
    else if (strcmp(tok->lexeme, "molecular") == 0)
        tok->type = molecular;
    else if (strcmp(tok->lexeme, "readInt") == 0)
        tok->type = READIN;
    else if (strcmp(tok->lexeme, "readFloat") == 0)
        tok->type = READIN;
    else if (strcmp(tok->lexeme, "readStr") == 0)
        tok->type = READIN;
    else if (strcmp(tok->lexeme, "readBool") == 0)
        tok->type = READIN;
    else if (strcmp(tok->lexeme, "writeOut") == 0)
        tok->type = READIN;
    else
        tok->type = oxy;
    return 0;
}


int next_Token(const char** p, struct Token* tok) {
    /*
     * Process the next character(s) and store the Token.
     * Return values:
     * 0      - STATUS OK
     * -1    - MEMORY ISSUE
     * 1    - INVALID CHARACTER SEQUENCE FOUND
    */

    char c = **p;
    if (c == '\0') {
        printf("Reached end of input\n");
        return 0;
    }

    // Add logic for matching 'H**'
    if (c == 'H' && *(*p + 1) == '*' && *(*p + 2) == '*') {
        consume(p); // Consume 'H'
        consume(p); // Consume '*'
        consume(p); // Consume '*'
        tok->type = H; // Set token type to H
        return 0;
    }
    
    if (c == '\0') {
        printf("Reached end of input\n");
        return 0;
    }

    if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
        return match_ws(p, tok);
    else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return match_id(p, tok);
    else
        switch (c) {
            case '[': return match_lbrack(p, tok);
            case ']': return match_rbrack(p, tok);
            case '+': return match_plus(p, tok);
            case '-': return match_minus(p, tok);
            case ',': return match_comma(p, tok);
            case '(': return match_lpar(p, tok);
            case ')': return match_rpar(p, tok);
            case '{': return match_lcurly(p, tok);
            case '}': return match_rcurly(p, tok);
            case '=': return match_equal(p, tok);
            
            case '>': return match_greater(p, tok);
            case '<': return match_lesser(p, tok);
            case '/': return match_div(p, tok);
            case '!':
                if (*(*p + 1) == '!!') {
                    return skip_comment(p);
                } else {
                    return match_noteq(p, tok); // Keep existing logic for '!='
                }
            case '*': return match_star(p, tok);
            case '%': return match_percent(p, tok);
            case '|': return match_or(p, tok);
            case '&': return match_and(p, tok);
            case '0': return match_int(p, tok);
            case '1': return match_int(p, tok);
            case '2': return match_int(p, tok);
            case '3': return match_int(p, tok);
            case '4': return match_int(p, tok);
            case '5': return match_int(p, tok);
            case '6': return match_int(p, tok);
            case '7': return match_int(p, tok);
            case '8': return match_int(p, tok);
            case '9': return match_int(p, tok);
            case '^': return match_pow(p, tok);
            case ';': return match_endline(p, tok);
            case '.': return match_dot(p, tok);
            default: return 1;
        }
}

struct Token* new_Token(char* lexeme, enum TokenType type) {
    struct Token* new;
    new = malloc(sizeof(struct Token));
    if (new == NULL)
        return NULL;
    new->lexeme = malloc(sizeof(char) * (strlen(lexeme) + 1));
    if (new->lexeme == NULL) {
        free(new);
        return NULL;
    }
    memcpy(new->lexeme, lexeme, strlen(lexeme) + 1);
    new->type = type;
    return new;
}

struct TokenList* alloc_TokenList() {
    struct TokenList* new;
    new = malloc(sizeof(struct TokenList));
    if (new == NULL)
        return NULL;
    new->token = NULL;
    new->next = NULL;
    return new;
}

struct TokenList* new_TokenList(struct Token* tok) {
    struct TokenList* new;
    struct Token* newTok;
    new = alloc_TokenList();
    if (new == NULL)
        return NULL;
    newTok = new_Token(tok->lexeme, tok->type);
    if (newTok == NULL) {
        free_TokenList(new);
        return NULL;
    }
    new->token = newTok;
    new->next = NULL;
    return new;
}

struct TokenList* build_TokenList(const char* fp) {

    char init[16] = {0};
    struct Token* tok = new_Token(init, UNKNOWN);
    struct TokenList* head = NULL;
    struct TokenList* current = head;
    struct TokenList* tail;

    int i = 0;
    int exit;
    while (*fp != '\0' && (exit = next_Token(&fp, tok)) == 0) {
        i++;
        if (head == NULL) {
            head = new_TokenList(tok);
            if (head == NULL) {
                free_Token(tok);
                return NULL;
            }
            current = head;
        }
        else {
            tail = new_TokenList(tok);
            if (tail == NULL) {
                free_TokenList(head);
                free_Token(tok);
                return NULL;
            }
            current->next = tail;
            current = tail;
        }
    }
    free_Token(tok);
    if (exit == 0) {

        printf("Tot Tokens = %d\n", i);
        printf("===================================\n");
    }
    else{

        free_TokenList(head);
        head = NULL;
    }
    return head;
}

struct TokenList* strip_WS(struct TokenList* list) {
    if (list == NULL)
        return NULL;
    struct TokenList *head, *curr, *prev, *new;

    curr = list;
    head = NULL;
    new = NULL;
    while (curr != NULL) {
        if (curr->token->type != WS) {
            new = new_TokenList(curr->token);
            if (new == NULL) {
                free_TokenList(head);
                return NULL;
            }
            if (head == NULL) {
                head = new;
                prev = head;
            }
            else {
                prev->next = new;
                prev = prev->next;
            }
        }
        curr = curr->next;
    }
    return head;
}


void skip_WS(struct TokenList** list) {

    struct TokenList* current = *list;
    while (current != NULL && current->token->type == WS)
        current = current->next;
    *list = current;
}
