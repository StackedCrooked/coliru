clang++ -std=c++11 -O2 -Wall -pedantic -pthread -S -emit-llvm -o prefix.s main.cpp
clang++ -std=c++11 -O2 -Wall -pedantic -pthread -S -emit-llvm -o postfix.s -DUSE_POSTFIX main.cpp
diff prefix.s postfix.s -s