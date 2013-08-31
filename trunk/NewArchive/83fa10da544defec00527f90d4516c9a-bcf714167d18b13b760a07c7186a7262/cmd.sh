g++-4.8 -DC -O2 main.cpp && strace ./a.out >c 2>&1
g++-4.8     -O2 main.cpp && strace ./a.out >c++ 2>&1
diff -W 240 -y c c++
cat c++