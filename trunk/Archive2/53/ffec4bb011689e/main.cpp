#include <iostream>//std::cout
#include <stdexcept>//std::out_of_range

template <typename T, size_t Size>//size_t is the largest unsigned type available and is commonly used for size-expressions
struct static_array {
    static_assert(Size > 0, "static_array<T> shall contain at least one element");//0 sized arrays are not valid, enforce error
private:
    T data[Size];//this array syntax is only legal with a compile time size – template arguments are compile time constants
public:
    static_array(const T & elem) {
        std::fill(std::begin(data), std::end(data), elem);//initialize all elements with elem
    }
    T& operator[](size_t index) {//size_t is unsigned – non-negative
        if (index >= Size) {//instead of a custom exception we use an already supplied one
            throw std::out_of_range("ivalid access at "+std::to_string(index)+" of static_array["+std::to_string(Size)+"]");
        }
        return data[index];
    }
    const T& operator[](size_t index) const {//size_t is unsigned – non-negative, function is const – access of const array
        if (index >= Size) {//instead of a custom exception we use an already supplied one
            throw std::out_of_range("ivalid access at "+std::to_string(index)+" of static_array["+std::to_string(Size)+"]");
        }
        return data[index];
    }
    static const size_t size = Size;
    //the compiler supplied cctor, dtor and op= work as expected, no additional work needed
};

template <typename T, size_t Size>
std::ostream& operator<<(std::ostream & out, const static_array<T, Size> & arr) {
    out << "{";
    for (size_t i = 0; i < Size-1; ++i) {//one off, to omit the last comma
        out << arr[i] << ", ";
    }
    out << arr[Size-1];//0 size is not valid, so this is okay
    return out << "}";
}

int main() {
    //static_array<std::string, 0> arr("bla");//error
    static_array<std::string, 15> arr1("bla");
    std::cout << arr1 << '\n';
    static_array<std::string, 15> arr2("foo");
    arr2[5] = "oink";
    std::cout << arr2 << '\n';
    arr1 = arr2;
    std::cout << arr1 << '\n';
    std::cout << arr2 << '\n';
    arr1[0];
    arr1[5];
    arr1[14];
    try {
        arr1[-1];
    } catch (const std::exception & ex) {
        std::cout << "oh, no: " << ex.what() << '\n';
    }
    try {
        arr1[15];
    } catch (const std::exception & ex) {
        std::cout << "oh, no: " << ex.what() << '\n';
    }
}