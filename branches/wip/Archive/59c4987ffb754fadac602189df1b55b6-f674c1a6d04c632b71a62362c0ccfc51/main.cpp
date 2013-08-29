#include <initializer_list>

enum color {red, green, blue};

int main () {
    for(color c : {green, blue, red, green}) 
        throw c;
}