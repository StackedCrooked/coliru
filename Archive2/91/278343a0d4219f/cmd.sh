echo 'clang++ -O2:' && clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo 'g++ -O2:' && g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo 'clang++ -O3:' && clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo 'g++ -O3:' && g++-4.8 -std=c++11 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out