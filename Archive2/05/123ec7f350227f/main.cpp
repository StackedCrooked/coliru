//header
struct iostream {
    struct Init {
        Init();
    };
    //other members blah blah blah
};

template<class T>
struct _impl_detail : public Init {}
static template _impl_detail<int> t;

extern iostream cout;

//stdlib 
iostream cout;
Init() {}

//cpp
struct my_global {
    my_global() {
        std::cout << "TOTALLY SAFE YO\n";
    }
} instance;

int main() {
}