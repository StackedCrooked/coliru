clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
foo1 = example.Foo("abc")
foo2 = example.Foo("abc")
foo3 = example.Foo("def")
aasert(foo1 == foo1)
assert(foo1 == foo2)
assert(foo1 != foo3)
EOF
echo $?