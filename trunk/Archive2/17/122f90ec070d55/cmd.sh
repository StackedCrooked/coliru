clang -E -dM - < /dev/null | awk '/define/ {print "-U" $2}' > clang_undefs
gcc -E -dM - < /dev/null | sed -e 's/#define \([_0-9A-Za-z()]*\) \(.*\)/"-D\1=\2"/' > gcc_defs
cat clang_undefs gcc_defs | xargs clang -E main.cpp -o -