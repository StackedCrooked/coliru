run() { echo "Optimization level: $1" ; g++ -std=c++11 $1 main.cpp && ./a.out ; }
run "-O0" > unoptimized ; run "-O2" > optimized
diff -y -W 160 unoptimized optimized