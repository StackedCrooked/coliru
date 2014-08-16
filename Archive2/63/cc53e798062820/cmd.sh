false && echo g++ && g++ -x c++ -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out
echo gcc && gcc -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out
false && echo clang++ && clang++ -x c++ -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out
echo clang && clang -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out