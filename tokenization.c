#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void", "main"
};
int isKeyword(char *str) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *file;
    char ch, buffer[MAX];
    int i = 0;

    file = fopen("Token_Input.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    printf("Tokens:\n");

    while ((ch = fgetc(file)) != EOF) {

        if (isspace(ch)) continue;
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            if (isKeyword(buffer))
                printf("<KEYWORD>     %s\n", buffer);
            else
                printf("<IDENTIFIER>  %s\n", buffer);
        }
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(file))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            printf("<NUMBER>      %s\n", buffer);
        }
        else if (ch == '=' || ch == '!' || ch == '<' || ch == '>') {
            char next = fgetc(file);
            if (next == '=') {
                printf("<OPERATOR>    %c%c\n", ch, next);
            } else {
                ungetc(next, file);
                printf("<OPERATOR>    %c\n", ch);
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            printf("<SYMBOL>      %c\n", ch);
        }
        else if (ch == '/') {
            char next = fgetc(file);
            if (next == '/') {
                while ((ch = fgetc(file)) != '\n' && ch != EOF);
            } else if (next == '*') {
                while (1) {
                    ch = fgetc(file);
                    if (ch == '*' && fgetc(file) == '/')
                        break;
                }
            } else {
                ungetc(next, file);
                printf("<OPERATOR>    /\n");
            }
        }
    }
    fclose(file);
    return 0;
}
