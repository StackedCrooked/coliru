echo 'clang++ c++14' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo 'clang++ c++11' && clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo 'g++ c++14 (partial)' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo 'g++ c++11' && g++ -std=c++11 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out