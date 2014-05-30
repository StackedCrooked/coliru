
template<class T>
struct is_any_of_type {
    is_any_of_type(const T* t) : left(t),found(false) {}    
    template<class U> is_any_of_type operator,(const U& right) {found |= (*left==right); return *this;}
    template<class U> is_any_of_type operator>(const U& right) {found |= (*left==right); return *this;}
    operator bool() const {return found;}
private:
    const T* left;
    bool found;
};
static is_any_of_type<void> is_any_of(0);
template<class T>
is_any_of_type<T> operator<(const T& left, is_any_of_type<void>)
{return is_any_of_type<T>(&left);}

#include <iostream>
int main() {
    std::string order = "VINFDWOPYCLERX";
    bool one = (order[0] <is_any_of> 'A');
    bool two = (order[0] <is_any_of> 'D','W','O','P');
    bool three = (order[0] <is_any_of> 'Z','Y','W','X','V','U');
    std::cout << one << two << three;
}