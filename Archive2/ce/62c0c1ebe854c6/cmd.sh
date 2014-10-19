clang++ -std=c++1y -stdlib=libc++ -Wall -Wextra -Wno-gnu-anonymous-struct -pedantic-errors -O3 -pthread main.cpp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 && ./a.out
#clang++ -E -P main.cpp
#g++-4.9 -std=c++1y -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp && ./a.out