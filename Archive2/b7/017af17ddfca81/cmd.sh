clang++ -std=c++14 -stdlib=libc++ main.cpp -lsupc++ -Os -Weverything -Wno-c++98-compat -Wno-sign-conversion && ./a.out << EOF
print
quit
EOF