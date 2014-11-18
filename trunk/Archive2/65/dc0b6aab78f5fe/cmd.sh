echo libstdc++
clang++ -std=c++1z main.cpp -Weverything -Wno-c++98-compat -Wno-padded -pthread && ./a.out
echo libc++
clang++ -std=c++1z -stdlib=libc++ main.cpp -Weverything -Wno-c++98-compat -Wno-padded -pthread -lsupc++ && ./a.out