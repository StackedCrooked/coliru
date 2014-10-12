set -x; g++ -std=c++1y -O2 -Wsystem-headers -Wdelete-non-virtual-dtor -pthread main.cpp && ./a.out
clang++ -std=c++1y -O2 -Wsystem-headers -Wdelete-non-virtual-dtor -pthread main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O2 -Wsystem-headers -Wdelete-non-virtual-dtor -pthread main.cpp && ./a.out