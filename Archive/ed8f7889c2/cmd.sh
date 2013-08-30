while read line ; do
  echo "C:$line"
  echo "O:$(${line} 2>&1 | perl -pe 's,\n,\\n,'g)\n"
done << EOF
g++-4.8 -O2 -Wall -Wextra -pedantic -pthread main.cpp
./a.out
EOF