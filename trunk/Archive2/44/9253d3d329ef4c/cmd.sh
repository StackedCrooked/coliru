clang++ -std=c++1y -Wall -Wextra -pedantic main.cpp -stdlib=libstdc++ && ./a.out
echo -e "\n###################################\n"
clang++ -std=c++1y -Wall -Wextra -pedantic main.cpp -stdlib=libc++ && ./a.out