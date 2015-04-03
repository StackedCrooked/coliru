echo "no RVO"
clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -Wno-unused-variable -fno-elide-constructors && ./a.out
echo "C++11 RVO"
clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -Wno-unused-variable && ./a.out
echo "C++14 RVO"
clang++ -std=c++1z -Os -Wall -pedantic -pthread main.cpp -Wno-unused-variable -felide-constructors && ./a.out