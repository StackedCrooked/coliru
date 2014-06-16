
class shy {
private:
    int dont_touch;

public:
    static const shy object;
};


const shy shy::object = []{
    shy obj;
    obj.dont_touch = 42;
    return obj;
}();


int main()
{
}
