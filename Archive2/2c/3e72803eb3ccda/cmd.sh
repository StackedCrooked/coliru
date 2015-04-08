clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example

class BadPolygon(example.Polygon):
    pass

class Square(example.Polygon):
    def __init__(self, length):
        example.Polygon.__init__(self)
        self.length = length
    def area(self):
        return self.length**2

try:
    polygon = BadPolygon()
    assert(isinstance(polygon, example.Polygon))
    got_runtime_error = False
    polygon.area()
except RuntimeError:
    got_runtime_error = True
finally:
    assert(got_runtime_error)

polygon = Square(6)
assert(isinstance(polygon, example.Polygon))
assert(36 == polygon.area())
EOF
echo $?