clang++ -std=c++11 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
assert(type(example.make_object("spam")) is example.Spam)
assert(type(example.make_object("egg")) is example.Egg)
assert(example.make_object("bogus") is None)
EOF
echo $?