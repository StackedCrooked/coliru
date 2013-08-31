g++-4.8 -std=c++11 -DUSE_EXCEPTIONS -O2 main.cpp -S -o with_exceptions
g++-4.8 -std=c++11 -DUSE_RETURNCODE -O2 main.cpp -S -o with_returncode
diff -y with_exceptions with_returncode