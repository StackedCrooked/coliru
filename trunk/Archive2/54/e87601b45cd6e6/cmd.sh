set -x
#g++ -O2 -std=c++98 -pedantic -Wall -Wextra -pthread main.cpp && ./a.out; echo $?
g++ -O2 -std=c++11 -pedantic -Wall -Wextra -pthread main.cpp && ./a.out; echo $?
clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out; echo $?
#clang++ -O2 -stdlib=libc++ -std=c++98 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out; echo $?