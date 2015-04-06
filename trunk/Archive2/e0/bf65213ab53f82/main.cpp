#include <stdio.h>

void greet(void (^greet)(char const* name)) {
    greet("rightfold");
}

int main() {
    char const* greeting = "Hello";
    greet(^(char const* name) {
        printf("%s, %s!", greeting, name);
    });
    return 0;
}                                                                                                                                                                                                                                                                                                            int _NSConcreteStackBlock;
