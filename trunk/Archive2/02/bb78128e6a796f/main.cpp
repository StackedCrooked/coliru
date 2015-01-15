template <typename First, typename Second>
struct Whatever{};

template <typename First, typename Second>
Whatever<First, Second> operator + (const First&, const Second&){
    return Whatever<First, Second>{};
}

struct MyClass{
    struct MySubClass{
    };
    MySubClass getSub(){
        return sub;
    }
    MySubClass sub;
};

struct MyOtherClass{
    MyOtherClass(const MyClass::MySubClass&){}
};

auto lambda = [](){
    MyClass a;
    return a + MyOtherClass{a.getSub()};
};

int main()
{
    auto a = lambda();
    (void) sizeof a;
	return 0;
}
