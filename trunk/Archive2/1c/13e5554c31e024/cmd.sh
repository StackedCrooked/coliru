set -x
#g++ -O2 -std=c++98 -pedantic -Wall -Wextra -pthread main.cpp && ./a.out
g++ -O2 -std=c++11 -pedantic -Wall -Wextra -pthread main.cpp && ./a.out <<< "1940 6 2 23 59 59 1940 6 3 1 0 0 1940 6 3 1 0 0 1940 6 2 23 59 59 1940 6 2 23 59 59"
#clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out
#clang++ -O2 -stdlib=libc++ -std=c++98 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out