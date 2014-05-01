#include <istream>
#include <map>
#include <string>

template<class T>
struct Shape { };

/* thrown when a shape cannot be read from a stream */
template<class T>
class WrongFormatException { };

template<class T>
class ShapeFactory
{
public:
    using createShapeFunction=Shape<T>*(void);
    static void registerFunction(const std::string &, const createShapeFunction *);
    static Shape<T> *createShape(const std::string &);
    static Shape<T> *createShape(std::istream &);
private:
    std::map<std::string, createShapeFunction *> creationFunctions;
    ShapeFactory();
    static ShapeFactory<T> *getShapeFactory();
};

int main()
{
    
}