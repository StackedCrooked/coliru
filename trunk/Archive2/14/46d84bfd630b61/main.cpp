#include <stdio.h>
#include <unistd.h>

void splitter(char* name, int length);
 
int main(int argc, char **argv) {
    int opt;
    char *name = NULL;
    int length = 0;
 
    while((opt = getopt(argc, argv, "ln:")) != -1) {
        switch(opt) {
        case 'l':
            splitter(name, length);
            break;
        case 'n':
            name = optarg;
            break;
        default:
            printf("Enter a third perimeter as your name\n");
        }
    }
}
 
void splitter(char* name, int length) {
    printf("Hi: %s\n", name); // prints "Hi: (null)"
}