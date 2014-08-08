echo g++ && g++ -x c++ -std=c++1y -Wall -Wextra -pedantic main.cpp && ./a.out
echo gcc && g++ -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out
echo clang++ && clang++ -x c++ -std=c++1y -Wall -Wextra -pedantic main.cpp && ./a.out
echo clang && clang++ -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out