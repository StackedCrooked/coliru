set -x
#g++ -O2 -std=c++98 -pedantic -Wall -Wextra -pthread main.cpp && ./a.out
g++ -O2 -std=c++1y -pedantic -Wall -Wextra -pthread main.cpp && ./a.out
clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out
#clang++ -O2 -stdlib=libc++ -std=c++98 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out