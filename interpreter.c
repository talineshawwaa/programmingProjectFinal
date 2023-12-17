#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>

char* readSourceCode(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("File opening failed");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    char* sourceCode = readSourceCode(argv[1]);
    if (sourceCode == NULL) {
        fprintf(stderr, "Failed to read the source file.\n");
        return 1;
    }

    struct TokenList* tokens = build_TokenList(sourceCode);
    if (tokens == NULL) {
        fprintf(stderr, "Failed to tokenize the source file.\n");
        free(sourceCode);
        return 1;
    }

    struct ParseTree* parseTree = NULL;
    int status = build_ParseTree(tokens, &parseTree);
    if (status != SUBTREE_OK || parseTree == NULL) {
        fprintf(stderr, "Failed to parse the source file.\n");
        free_TokenList(tokens);
        free(sourceCode);
        return 1;
    }

    executeParseTree(parseTree);

    free_ParseTree(parseTree);
    free_TokenList(tokens);
    free(sourceCode);

    return 0;
}