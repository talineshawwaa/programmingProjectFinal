#include "executor.h"
#include <stdio.h>


int executeExpression(struct ParseTree* expr);
void executeStatement(struct ParseTree* stmt);
void executePrint(struct ParseTree* expr);


void executeParseTree(struct ParseTree* tree) {
    if (!tree) return;
    switch (tree->data->type) {


        case PRINT: 
            executePrint(tree->child);
            break;

    }

    executeParseTree(tree->child);
    executeParseTree(tree->sibling);
}

void executePrint(struct ParseTree* expr) {
    if (expr && expr->data->type == StringLiteral) {
        printf("%s\n", expr->data->lexeme);
    } else {

    }
}

int executeExpression(struct ParseTree* expr) {

    return 0; 
}

void executeStatement(struct ParseTree* stmt) {

}
