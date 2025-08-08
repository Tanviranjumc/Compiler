#include <stdio.h>
#include <string.h>

char email[100], website[100];
int is_valid_email() {
    int at_index = -1, dot_index = -1;
    int length = strlen(email);
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            if (at_index != -1) return 0;
            at_index = i;
        }
        else if (email[i] == '.' && at_index != -1) {
            dot_index = i;
        }
    }

    if (!(at_index > 0 && dot_index > at_index + 1 && dot_index < length - 1)) {
        return 0;
    }
    for(int i = 0; i< length; i++){
        if(email[i] == '@' || email[i] == '.'){
            continue;
        }
        if (!((email[i] >= 'a' && email[i] <= 'z') ||
              (email[i] >= 'A' && email[i] <= 'Z') ||
              (email[i] >= '0' && email[i] <= '9') ||
              email[i] == '_' || email[i] == '-' || email[i] == '+')) {
                return 0;
        }
    }

    char *domain = email + at_index + 1;
    char *valid_domains[] = {
        "gmail.com", "yahoo.com", "outlook.com", "hotmail.com", "edu.com", "gov.com"
    };

    int domain_count = sizeof(valid_domains) / sizeof(valid_domains[0]);

    for (int i = 0; i < domain_count; i++) {
        if (strcmp(domain, valid_domains[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_valid_website() {
    int length = strlen(website);
    if (length < 5) return 0;

    char *valid_suffixes[] = {".com", ".org", ".net", ".edu", ".gov", ".io", ".app"};
    int suffix_count = sizeof(valid_suffixes) / sizeof(valid_suffixes[0]);

    for (int i = 0; i < suffix_count; i++) {
        int suffix_len = strlen(valid_suffixes[i]);
        if (length > suffix_len && strcmp(website + length - suffix_len, valid_suffixes[i]) == 0) {
            return 1;
        }
    }

    for(int i = 0; i< length; i++){
        if (!((website[i] >= 'a' && website[i] <= 'z') ||
              (website[i] >= 'A' && website[i] <= 'Z') ||
              (website[i] >= '0' && website[i] <= '9') ||
              website[i] == '_' || website[i] == '-' || website[i] == '+')){
            return 0;
        }
    }
    return 0;
}
void trim_newline(char *str) {
    int len = strlen(str);
    if (len && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    FILE *input = fopen("test2.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output) {
        printf("Error opening file.\n");
        return 1;
    }

    char line1[200], line2[200];
    fgets(line1, sizeof(line1), input);
    fgets(line2, sizeof(line2), input);

    trim_newline(line1);
    trim_newline(line2);

    int valid_email = 0, valid_website = 0;

    if (strchr(line1, '@')) {
        strcpy(email, line1);
        strcpy(website, line2);
    }
    else {
        strcpy(email, line2);
        strcpy(website, line1);
    }

    valid_email = is_valid_email();
    valid_website = is_valid_website();

    if (valid_email){
        fprintf(output, "Email: %s - is valid\n", email);
    }
    else{
        fprintf(output, "Email: %s - is invalid\n", email);
    }
    if(valid_website){
        fprintf(output, "Website: %s - is valid", website);
    }
    else{
        fprintf(output, "Website: %s - is invalid", website);
    }

    fclose(input);
    fclose(output);

    return 0;
}
