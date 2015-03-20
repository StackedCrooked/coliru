g++     -std=c++11 -O3 -S -masm=intel -o - main.cpp | grep -v '\.' > gcc_output
clang++ -std=c++11 -O3 -S -masm=intel -o - main.cpp | grep -v '\.\|BB' > clang_output
diff -y -t gcc_output clang_output