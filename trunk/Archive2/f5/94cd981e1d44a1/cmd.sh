set -x; g++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out <<< 5
clang++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out <<< 5 
clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out <<< 5