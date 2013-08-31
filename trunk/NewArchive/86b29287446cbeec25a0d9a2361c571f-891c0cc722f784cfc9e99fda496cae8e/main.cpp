#include <iostream>

int main() {
    for(char a='a'; a<='z'; ++a) {
        for(char b='a'; b<='z'; ++b) {
            if (b==a) continue;
            for(char c='a'; c<='z'; ++c) {
                if (c==a) continue;
                if (c==b) continue;
                std::cout << a << b << c << '\n';
            }
        }
    }
}
