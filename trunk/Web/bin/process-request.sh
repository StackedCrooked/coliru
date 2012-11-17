set -x
touch compiler-flags.txt
GCC_OPTIONS=`cat main.cpp | head -n1`
echo "GCC_OPTIONS: ${GCC_OPTIONS}"
if grep -q "^// g++" <<< ${GCC_OPTIONS} ; then
    echo ${GCC_OPTIONS} >> compiler-flags.txt
fi
g++ `cat compiler-flags.txt | head -n 1` -o test main.cpp >response.txt 2>&1
./test >>response.txt 2>&1
cat response.txt
