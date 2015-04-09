echo clang:
clang++ -std=c++1z -O0 -Wall -pedantic -pthread -stdlib=libc++ -D_LIBCPP_DEBUG main.cpp && ./a.out
echo gcc:
g++ -std=c++14 -O0 -Wall -pedantic -pthread -D_GLIBCXX_DEBUG main.cpp && ./a.out