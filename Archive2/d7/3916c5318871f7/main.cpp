
struct B {
    B operator,(B) {return *this;}
    template<class func_type>
    auto operator->*(func_type&& func) -> decltype(func(1, 3, 4)) {return func(1, 3, 5);}
};


int main()
{
    B width,height,depth;
    auto volume = (width,height,depth) ->* [] (int w, int h, int d) { return w * h * d; };
}