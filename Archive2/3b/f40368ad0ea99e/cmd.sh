echo clang:
clang++ -std=c++03 -O3 -w -pedantic -pthread -stdlib=libc++ -D_LIBCPP_DEBUG main.cpp && ./a.out
clang++ -std=c++11 -O3 -w -pedantic -pthread -stdlib=libc++ -D_LIBCPP_DEBUG main.cpp && ./a.out
clang++ -std=c++14 -O3 -w -pedantic -pthread -stdlib=libc++ -D_LIBCPP_DEBUG main.cpp && ./a.out
echo gcc:
g++ -std=c++03 -O3 -w -pedantic -pthread -D_GLIBCXX_DEBUG main.cpp && ./a.out
g++ -std=c++11 -O3 -w -pedantic -pthread -D_GLIBCXX_DEBUG main.cpp && ./a.out
g++ -std=c++14 -O3 -w -pedantic -pthread -D_GLIBCXX_DEBUG main.cpp && ./a.out