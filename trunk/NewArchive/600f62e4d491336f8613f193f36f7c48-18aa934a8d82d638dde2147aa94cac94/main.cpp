template<class it_type>
class range {
    it_type f,l;
public:
    range() :f(),l(){}
    range(it_type first, it_type last) :f(first),l(last){}
    it_type& begin() noexcept(true) {return f;}
    it_type& end() noexcept(true) {return l;}
    const it_type& begin() const noexcept(true) {return f;}
    const it_type& end() const noexcept(true) {return l;}
};

int main() {}