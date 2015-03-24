mkdir vanilla && g++ -std=c++14 -Wall -shared -fpic -o vanilla/libplugin.so /Archive2/f4/26b804eb0ffa8b/main.cpp
mkdir chocolate && g++ -std=c++14 -Wall -shared -fpic -o chocolate/libplugin.so /Archive2/6c/dddc69a12b2e12/main.cpp
g++ -std=c++14 -Wall main.cpp -Lvanilla -lplugin
LD_LIBRARY_PATH=vanilla/ ./a.out
LD_LIBRARY_PATH=chocolate/ ./a.out