#set -ex
clang++ -std=gnu++1z -stdlib=libc++ -Weverything -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof main.cpp
./a.out && echo "Success!" || echo "Failure!"