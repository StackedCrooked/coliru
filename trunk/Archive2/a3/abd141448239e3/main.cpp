template<typename T>
class Representation{};

template<typename T, template<typename> class Representation>
class Point: private Representation<T>{};

template<typename T, template<typename> class Representation>
class Vector: private Representation<T>{};

template
< typename T
, template<typename> class Representation
, template<typename, template<typename> class Representation> class Point
, template<typename, template<typename> class Representation> class Vector >
class Line:
private Point<T, Representation>,
private Vector<T, Representation>
{};

int main(int argc, char* argv[])
{
    Line<double, Representation, Point, Vector> line;
    return 0;
}