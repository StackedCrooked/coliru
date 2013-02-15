#include <type_traits>
#include <iostream>
#include <locale>

template<class Object, typename CObject>
class friendly_factory
{
    public:
        static Object
        create(CObject *object)
        {
            return Object(object);
        }
};

namespace FMOD
{
struct Sound{};
struct System{};
}

class Sound : public friendly_factory<Sound,FMOD::Sound>
{
    public:
        Sound(const Sound&)=delete;
        ~Sound() { if (_object) delete _object; }

    protected:
        Sound(FMOD::Sound* object): _object(object) {}

    private:
        FMOD::Sound* _object;
};

int main()
{
    std::cout << std::boolalpha;
        
    return 0;
}