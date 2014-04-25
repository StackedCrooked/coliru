#include <iostream>
#include <fstream>
#include <vector>

template<class streamT>
class textbuf;

template<>
class textbuf<std::ofstream> : public std::streambuf
{
public:
    textbuf(int buf_size = 1) : buffer(buf_size), out()
    {
        this->setp(this->buffer.data(), this->buffer.data() + buf_size - 1);
    }
    
    void open(const std::string& path)
    {
        this->out.open(path, std::ios_base::out);
    }
    
    int_type overflow(int_type c)
    {
        if (!this->out.is_open())
            return traits_type::eof();
        
        if (c != traits_type::eof())
        {
            std::ptrdiff_t pos1 = pptr() - pbase();
            pos_type pos2 = this->out.seekp(0, std::ios_base::end).tellp();
            this->out.seekp(pos1, std::ios_base::beg);
            
            if (!done && pos1 < pos2 && c != traits_type::eof())
            {
                trail.assign(this->pptr(), this->buffer.substr(pos1, pos2));
                done = true;
            }
            
            *this->pptr() = traits_type::to_int_type(c);
            this->pbump(1);
            
            if (sync())
            {
                this->pbump(-(this->pptr() - this->pbase()));
                this->setp(buffer.data(), buffer.data() + buffer.size());
            }
        }
    }
    
    int sync()
    {
        return this->out.write(trail.data(), trail.size()) ? 0 : -1;
    }
private:
    std::vector<char> buffer;
    std::string trail;
    std::ofstream out;
    bool done = false;
};

int main()
{
    
}