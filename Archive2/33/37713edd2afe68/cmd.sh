ln -s /Archive2/e3/6a848c9464e0a6/main.cpp foo.cpp
clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp foo.cpp -lsupc++ && ./a.out 
echo ============== && g++ -std=c++14  -O3 -Wall -Wextra -pedantic-errors main.cpp foo.cpp && ./a.out