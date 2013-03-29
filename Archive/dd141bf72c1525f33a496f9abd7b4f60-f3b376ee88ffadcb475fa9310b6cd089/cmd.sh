compile_with_loglevel() { 
    g++-4.8 -std=c++11 -O3 -Wall -Wextra -pthread -S -o "$1.asm" -DLOG_LEVEL="$1" main.cpp
}
compile_with_loglevel Trace ; compile_with_loglevel Info
diff -y Trace.asm Info.asm