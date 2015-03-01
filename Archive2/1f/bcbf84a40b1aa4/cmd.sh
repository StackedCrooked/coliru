clang++ -std=c++11 -O2 -I /usr/include/python2.7 -Wall -Werror -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
spam = example.Spam(5)
spams = example.SpamVector()
spams.append(spam)
assert(spams[0].val == 5)
spam.val = 21
assert(spams[0].val == 21)
example.modify_spams(spams)
assert(spam.val == 42)
spams.append(spam)
spam.val = 100
assert(spams[1].val == 100)
assert(spams[0].val == 42) # The container does not provide indirection.
EOF
echo $?