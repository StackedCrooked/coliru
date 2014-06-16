
class shy {
private:
    int dont_touch;

public:
    static const shy object;
    static const shy object2;
};


const shy shy::object = []{
    shy obj;
    obj.dont_touch = 42;
    return obj;
}();


shy init() {
    shy obj;
    obj.dont_touch = 42;
    return obj;
}

const shy shy::object2 = init();


int main()
{
}
