#include <boost/exception/all.hpp>
#include <algorithm>


struct ExceptionBase : virtual std::exception, virtual boost::exception {};
struct SystemError : ExceptionBase {};
struct PermissionsError : SystemError {};
struct ImageError : ExceptionBase {};
struct ImageParseError : ImageError {};
struct InvalidExtension : ImageError {};
struct TooManyErrors : ImageError {};


using FileNameTag = boost::error_info<struct FileName, std::string>;
using ExtensionTag = boost::error_info<struct Extension, char>;
using ProgressTag = boost::error_info<struct Progress, int>;


void CheckExtension(const std::string & name)
{
    if (name.back() == '4')
    {
        BOOST_THROW_EXCEPTION(InvalidExtension() << FileNameTag(name) << ExtensionTag(name.back()));
    }
}


std::string ReadFile(const std::string & name)
{
    if (name.back() == '2')
    {
        BOOST_THROW_EXCEPTION(PermissionsError() << FileNameTag(name));
    }
    return name;
}


class Image
{
public:
    static Image fromFile(const std::string & name)
    {
        CheckExtension(name);
        return Parse(ReadFile(name));        
    }
    
private:
    static Image Parse(const std::string& name)
    {
        if (name.back() == '1')
        {
            BOOST_THROW_EXCEPTION(ImageParseError() << FileNameTag(name));
        }
        return Image{};
    }
};

typedef std::vector<Image> Images;


Images LoadImagesFromDisk(const std::string & path)
{
    Images result;
    int exceptionCounter = 0;
    for (int i = 0; i != 100; ++i)
    {
        try 
        {
            result.push_back(Image::fromFile(path + std::to_string(i)));
        }
        catch (boost::exception & exc)
        {
            exc << ProgressTag(i);
            if (const std::string * fileName = boost::get_error_info<FileNameTag>(exc))
            {
                std::cerr << "Failed to load image " << i << "/100: " << *fileName << "." << std::endl;
                if (++exceptionCounter >= 10)
                {
                    BOOST_THROW_EXCEPTION(TooManyErrors());
                }
            }
        }
    }
    return result;    
}


int main()
{
    try
    {
        LoadImagesFromDisk("/path/to/images");
    }
    catch (...)
    {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
    }
}
