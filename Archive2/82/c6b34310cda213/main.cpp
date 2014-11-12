#include <iostream>
#include <iomanip>
#include <fstream>

class linebuf : public std::streambuf
{
public:
    linebuf() : m_sbuf() { m_sbuf.open("file.txt", std::ios_base::out); }
    
    int_type overflow(int_type c) override
    {
        char ch = traits_type::to_char_type(c);
        if (ch != traits_type::eof() && new_line)
        {
            std::ostream(&m_sbuf) << line_number++ << " ";
        }
        new_line = ch == '\n';
        return m_sbuf.sputc(ch);
    }
    
    int sync() override { return m_sbuf.pubsync() ? 0 : -1; }
private:
    std::filebuf m_sbuf;
    bool new_line = true;
    int line_number = 1;
};

int main() {
    std::ofstream out("file.txt");
    linebuf buf;
    std::ostream os(&buf);
    os << "This is the first line\n";
    os << "This is the second line\n";

    std::ifstream in("file.txt"); in.tie(&os);
    std::string str;
    while (std::getline(in, str)) std::cout << str << std::endl;
}