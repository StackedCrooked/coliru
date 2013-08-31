template<class it_type>
class range {
    it_type f,l;
public:
    range() :f(),l(){}
    range(it_type first, it_type last) :f(first),l(last){}
    it_type& begin() noexcept(true) {return first;}
    it_type& end() noexcept(true) {return last;}
    const it_type& begin() const noexcept(true) {return first;}
    const it_type& end() const noexcept(true) {return last;}
};