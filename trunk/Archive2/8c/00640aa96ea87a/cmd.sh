echo "abc123" > ../Dose.c
clang++ -std=c++1y -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 && ./a.out
#clang++ -E -P main.cpp
#g++-4.9 -std=c++1y -Wall -Wextra -pedantic-errors -Werror=zero-as-null-pointer-constant -O3 -pthread main.cpp && ./a.out
#clang -x c -std=c11 -Wall -Wextra -pedantic -O3 main.cpp && ./a.out