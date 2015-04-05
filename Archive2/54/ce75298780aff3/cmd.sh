ln -s /Archive2/f1/77475ef4c5e4f1/main.cpp foo.cpp
clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp foo.cpp -lsupc++ && ./a.out 
echo ============== && sleep 2 && g++ -std=c++14  -O3 -Wall -Wextra -pedantic-errors main.cpp foo.cpp && ./a.out