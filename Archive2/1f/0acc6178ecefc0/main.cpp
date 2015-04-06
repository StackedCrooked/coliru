#include <stdio.h>

                                                                                                                                                                                                                                                            int _NSConcreteStackBlock;

void greet(void (^greet)(char const* name)) {
    greet("rightfold");
}

int main() {
    char const* greeting = "Hello";
    greet(^(char const* name) {
        printf("%s, %s!", greeting, name);
    });
    return 0;
}
