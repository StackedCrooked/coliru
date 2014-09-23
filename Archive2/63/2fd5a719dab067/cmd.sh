set -x;
clang++ -std=gnu++1z -stdlib=libc++ -Ofast -Wall -Wextra -Weverything -pedantic -Wno-c++98-compat main.cpp && ./a.out