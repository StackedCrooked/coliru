#include <iostream>
#include <string>
namespace KHR_debug
{

    enum class Source {
        API             /*= GL_DEBUG_SOURCE_API            */,
        WINDOW_SYSTEM   /*= GL_DEBUG_SOURCE_WINDOW_SYSTEM  */,
        SHADER_COMPILER /*= GL_DEBUG_SOURCE_SHADER_COMPILER*/,
        THIRD_PARTY     /*= GL_DEBUG_SOURCE_THIRD_PARTY    */,
        APPLICATION     /*= GL_DEBUG_SOURCE_APPLICATION    */,
        OTHER           /*= GL_DEBUG_SOURCE_OTHER          */
    };

    std::string to_string(Source source) {
        switch(source) {
            case Source::API:             return "GL_DEBUG_SOURCE_API";
            case Source::WINDOW_SYSTEM:   return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
            case Source::SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
            case Source::THIRD_PARTY:     return "GL_DEBUG_SOURCE_THIRD_PARTY";
            case Source::APPLICATION:     return "GL_DEBUG_SOURCE_APPLICATION";
            case Source::OTHER:           return "GL_DEBUG_SOURCE_OTHER";
            default:                      return "INVALID_SOURCE_ENUM";
        }
    }
}

int main()
{
    using std::to_string;

    int ltuae = 42;
    std::cout << "The answer: " << to_string(ltuae) << std::endl;

    KHR_debug::Source s = KHR_debug::Source::APPLICATION;
    std::cout << "The source: " << to_string(s) << std::endl;
}
