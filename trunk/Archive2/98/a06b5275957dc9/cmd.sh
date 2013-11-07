clang++ -std=c++11 -O0 -Wall -pedantic main.cpp -S -emit-llvm -o O0.asm &&
clang++ -std=c++11 -O1 -Wall -pedantic main.cpp -S -emit-llvm -o O1.asm &&
diff --side-by-side O0.asm O1.asm