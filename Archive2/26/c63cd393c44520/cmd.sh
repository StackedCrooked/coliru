set -x; #g++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp  -fsanitize=undefined && ./a.out
#clang++ -stdlib=libc++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp -fsanitize=undefined -lcxxrt -ldl && ./a.out
clang++ -v -std=c++11 -O0 -Wall -pedantic -pthread main.cpp  -fsanitize=undefined -lcxxrt -ldl && ./a.out