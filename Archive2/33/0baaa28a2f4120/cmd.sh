clang++ -std=c++98 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 && echo '3 2 +' | ./a.out
##clang++ -E -P main.cpp
##g++-4.9 -std=c++1y -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp && ./a.out