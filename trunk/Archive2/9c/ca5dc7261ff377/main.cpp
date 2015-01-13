#include <stdio.h>

void splitter(char* name, int length);
 
int main(int argc, char **argv) {
        char *name = NULL;
        int length = 0;
        int arg = 1;
 
        while (arg < argc) {
                if (argv[arg][0] == '-') {
                        switch(argv[arg][1]) {
                        case 'l':
                                ++arg;
                                printf("Hello: %s\n", name); // prints Hello: (null)
                                splitter(name, length); // prints Hi: (null)
                                break;
                        case 'n':
                                ++arg;
                                if (argv[arg]) {
                                  {
                                        name = argv[arg];
                                        ++arg;
                                  }
                                } else {
                                        name = "John";
                                }
                                break;
                        default:
                                printf("Hello, I am default!\n");
                        }
                }
        }
        return 0;
}
 
void splitter(char* name, int length) {
        printf("Hi: %s\n", name);
}