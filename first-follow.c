#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10

char production[MAX][10];
char firstResult[10], followResult[10];
int num;

void findFirst(char, int, int);
void findFollow(char, int, int);
int isNonTerminal(char);
void addToResult(char*, char);

int main() {
    int i;
    char ch;
    printf("Write a production number: ");
    scanf("%d", &num);

    printf("productions (A=aA format)give:\n");
    for (i = 0; i < num; i++) {
        scanf("%s", production[i]);
    }

    for (i = 0; i < num; i++) {
        ch = production[i][0];
        printf("FIRST(%c) = { ", ch);
        findFirst(ch, 0, 0);
        for (int k = 0; firstResult[k] != '\0'; k++) {
            printf("%c ", firstResult[k]);
        }
        printf("}\n");
        memset(firstResult, 0, sizeof(firstResult));
    }

    for (i = 0; i < num; i++) {
        ch = production[i][0];
        printf("FOLLOW(%c) = { ", ch);
        followResult[0] = '\0';
        findFollow(ch, 0, 0);
        for (int k = 0; followResult[k] != '\0'; k++) {
            printf("%c ", followResult[k]);
        }
        printf("}\n");
    }
    return 0;
}
// FIRST
void findFirst(char c, int q1, int q2) {
    int j;
    if (!(isupper(c))) {
        addToResult(firstResult, c);
        return;
    }

    for (j = 0; j < num; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                findFirst(production[q1][q2 + 1], q1, q2 + 1);
            } else if (!isupper(production[j][2])) {
                addToResult(firstResult, production[j][2]);
            } else {
                findFirst(production[j][2], j, 2);
            }
        }
    }
}
// FOLLOW
void findFollow(char c, int c1, int c2) {
    int i, j;

    if (production[0][0] == c)
        addToResult(followResult, '$');

    for (i = 0; i < num; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    findFirst(production[i][j + 1], i, j + 1);
                    for (int k = 0; firstResult[k] != '\0'; k++) {
                        if (firstResult[k] != '#')
                            addToResult(followResult, firstResult[k]);
                        else
                            findFollow(production[i][0], i, 0);
                    }
                } else if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    findFollow(production[i][0], i, 0);
                }
            }
        }
    }
}

int isNonTerminal(char c) {
    return isupper(c);
}
void addToResult(char *result, char c) {
    for (int i = 0; result[i] != '\0'; i++) {
        if (result[i] == c)
            return;
    }
    int len = strlen(result);
    result[len] = c;
    result[len + 1] = '\0';
}
