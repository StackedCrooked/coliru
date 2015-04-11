#include <iostream>
#include <array>
 
// Buffer for std::ostream implemented by std::array
template<std::size_t SIZE, class CharT = char>
class ArrayedStreamBuffer : public std::basic_streambuf<CharT>
{
public:
    using Base = std::basic_streambuf<CharT>;
    using char_type = typename Base::char_type;
 
    ArrayedStreamBuffer() : buffer_{} // value-initialize buffer_ to all zeroes
    {
        Base::setp(buffer_.begin(), buffer_.end()); // set std::basic_streambuf
            // put area pointers to work with 'buffer_'
    }
 
    void print_buffer()
    {
        for (const auto& i: buffer_) {
            if (i == 0) {
                std::cout << "NULL";
            } else {
                std::cout << i;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
 
private:
    std::array<char_type, SIZE> buffer_;
};
 
int main()
{
    ArrayedStreamBuffer<10> streambuf;
    std::ostream stream(&streambuf);
 
    stream << "hello";
    stream << ",";
 
    streambuf.print_buffer();
}