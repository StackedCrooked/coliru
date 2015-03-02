clang++ -std=c++11 -O2 -I /usr/include/python2.7 -Wall -Werror -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
foo = example.Foo()
assert(foo is last_foo)
bar = example.Bar()
assert(bar is last_bar)
spam = example.Spam()
assert(spam is last_spam)
egg = example.Egg()
assert(egg is last_egg)
EOF
echo $?