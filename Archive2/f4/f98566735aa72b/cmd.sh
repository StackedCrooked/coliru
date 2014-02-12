ln -s /Archive2/3b/e5877aa14466da/main.cpp foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -c foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp foo.o -lsupc++ && time ./a.out