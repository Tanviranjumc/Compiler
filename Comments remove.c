#include <stdio.h>
#include <string.h>
int main() {
    char input[5000] = "";
    char line[500];
    char output[5000];
    int inside_single = 0, inside_multi = 0;
    int i = 0, j = 0;
    printf("Enter a code ( Comments C code)-\n");
     while (1) {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "END\n") == 0 || strcmp(line, "END\r\n") == 0) break;
        strcat(input, line);
    }
    while (input[i] != '\0') {
        if (!inside_single && !inside_multi && input[i] == '/' && input[i + 1] == '/') {
            inside_single = 1;
            i += 2;
            continue;
        }
        if (!inside_single && !inside_multi && input[i] == '/' && input[i + 1] == '*') {
            inside_multi = 1;
            i += 2;
            continue;
        }
        if (inside_single && input[i] == '\n') {
            inside_single = 0;
        }
        if (inside_multi && input[i] == '*' && input[i + 1] == '/') {
            inside_multi = 0;
            i += 2;
            continue;
        }
        if (!inside_single && !inside_multi) {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
    printf("\nC Code after removing comments:-\n%s\n", output);
    return 0;
}
