#include <stdexcept>

struct MazeCreationException : public virtual std::runtime_error
{
    using std::runtime_error::runtime_error ;
};

namespace gnu_microsoft_work_around
{
    struct MazeCreationException : public virtual std::runtime_error
    {
        MazeCreationException( const char* message ) : std::runtime_error(message) {}
    };
}

namespace legacy_cpp
{
    struct MazeCreationException : public virtual std::runtime_error
    {
        MazeCreationException( const char* message ) : std::runtime_error(message) {}
    };
}

int main()
{
    legacy_cpp::MazeCreationException bye( "bye" ) ;
    gnu_microsoft_work_around::MazeCreationException poor( "poor" ) ;
    
    MazeCreationException hello( "hello" ) ; // the GNU and microsoft libraries choke on this
}
