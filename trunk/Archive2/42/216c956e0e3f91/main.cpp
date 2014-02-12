#include <stdexcept>
#include <sstream>
#include <string>


struct DynamicException : std::runtime_error
{
    DynamicException(const std::string& inName) :
        std::runtime_error(inName)
    {
    }

    template<typename T>
    DynamicException set(std::string key, T value)
    {
        std::stringstream ss;
        ss << what() << " " << encode(std::move(key)) << "=" << encode(std::move(value));
        return DynamicException(ss.str());
    }

private:
    template<typename T>
    std::string encode(T&& t)
    {
        std::stringstream ss;
        ss << t;
        return encode(ss.str());
    }

    // use percent encoding
    std::string encode(std::string&& s)
    {
        replace_all(s, "%", "%25");
        replace_all(s, " ", "%20");
        return s;
    }

    void replace_all(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }
};


int main()
{
    throw DynamicException("FileNotFound")
            .set("name", "test.jpg")
            .set("path", "My Documents\\test.jpg")
            .set("index", 1);
}