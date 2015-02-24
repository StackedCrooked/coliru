echo libc++ && clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo -e '\nlibstdc++' && g++ --version | grep GCC && g++ -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo -e '\nlibstdc++ 4.8' && g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out