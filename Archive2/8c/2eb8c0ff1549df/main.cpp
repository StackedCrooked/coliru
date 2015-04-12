template <class T>
class TypeDisplayer;

int main()
{
    auto d = "variable";
    TypeDisplayer<decltype(d)> t;
    
    return 0;
}