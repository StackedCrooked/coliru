prefix() { local l ; while read l; do printf '%s%s\n' "$1" "$l"; done  ; } ; while read c; do (o=$(mktemp -u); p=$(mktemp -u) ; mkfifo "$o" "$p" ; trap 'rm -f "$o" "$p"' EXIT ; prefix 'O:' < "$o" >&1 & prefix 'E:' < "$p" >&2 & echo "C:$c" ; eval "$c" 1> "$o" 2> "$p" ; e=$? ; wait ; echo "R:$e" ; exit $e) done <<EOF
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
./a.out
EOF