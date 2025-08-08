#include <stdio.h>

int main (){
    FILE *files, *files2;
    files = fopen("test3.c", "r");
    files2 = fopen("test2.txt", "w");

    char readTheFIle;
    if(files != NULL){
        while((readTheFIle = getc(files)) != EOF){
            putchar(readTheFIle);
            putc(readTheFIle, files2);
        }
    }
    else{
        printf("Error reading files");
    }

    fclose(files2);
    fclose(files);

    return 0;
}


