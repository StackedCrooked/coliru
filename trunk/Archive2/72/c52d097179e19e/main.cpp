#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void trim_string(char *);

int main() {

    char *temp = "   I struggle with strings in C.\n";
    trim_string(temp);
    printf("%s", temp);

    return 0;
}


void trim_string(char *string) {
    char *string_trimmed = "";
    int i=0, j=0;

    while (isblank(string[i])) {
        i++;
    }
    while (string[i] != '\0') {
        string_trimmed[j] = string[i];
        i++;
        j++;
    }
    string_trimmed[j] = '\0';
    strcpy(string, string_trimmed);
}
