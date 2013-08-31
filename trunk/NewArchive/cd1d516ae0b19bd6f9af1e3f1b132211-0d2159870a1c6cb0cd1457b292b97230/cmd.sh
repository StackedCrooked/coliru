clang++ -std=c++11 -O1 -Wall -Werror main.cpp && ./a.out <<EOF
// comment bla bla
[sectionname]
key = value
key2=value2


// comment
key3 = value3

[anothersection]
key = value
EOF