#include <iostream>
#include <vector>
#include <map>

typedef int minutes;

namespace Jungle
{
    class Puma
    {
        int size;
    };
    
    class Cheetah
    {
        public:
        int nap (unsigned hours)
        {
            return 10;
        }
        
        Puma stretch (minutes m)
        {
            Puma p;
            return p;
        }
    };
    
    template <typename T>
    class Lion
    {
    public:
        Lion(){}
        Lion(T age, T weight) : age(age), weight(weight) {}

        int sleep(unsigned hours)
        {
            return 1;
        }

        //void walk(std::vector<std::string> eat_list)
        //void walk(std::basic_string<wchar_t > eat_list)
        //void walk(std::vector<std::string> eat_list)
        //void walk(std::vector<int> eat_list)
        //void walk(std::vector<std::basic_string<wchar_t>> eat_list)
        //void walk(int food_plate_id, Puma p, std::vector<std::basic_string<wchar_t>> eat_list)
        std::vector<std::basic_string<wchar_t>> walk(int food_plate_id, Puma p, std::vector<std::basic_string<wchar_t>> eat_list)
        {
            std::vector<std::basic_string<wchar_t>> v;
            return v;
        }

        void jump(double* height)
        {

        }

        void eat(std::vector<std::string> eat_list)
        {
//            Tiger t;
//            t.growl<int>(23);
        }

        T purr(T pitch)
        {
            return pitch;
        }
        
        template <typename U>
        U meow(U pitch)
        {
            return pitch;
        }
        
    private:
        T age;
        T weight;
    };

    template class Lion<std::vector<std::basic_string<wchar_t>>>;
    //template std::vector<int> Lion<std::vector<std::basic_string<wchar_t>>>::meow<std::vector<int> >(std::vector<int> pitch);
    //template std::vector<int> Lion<float>::meow<std::vector<int> >(std::vector<int> pitch);
    template Puma Lion<float>::meow<Puma >(Puma pitch);
    
    template <typename T>
    class Jaguar
    {
    public:
        T look(double* seconds)
        {
            return 3;
        }

        const int hear(const double* const seconds) const
        {
            return 3;
        }
    };

    template class Jaguar<const int>;
}

int addNumbers(int a, int b)
{
    return a + b;
}

template <typename T, typename U>
T playMusic(T t, U u)
{
    return t;
}

template float playMusic<float, double>(float freqA, double freqA2);
template int playMusic<int, unsigned int>(int freqB, unsigned int freqB2);
template std::vector<std::basic_string<char>> playMusic<std::vector<std::basic_string<char>>, unsigned int>(std::vector<std::basic_string<char>> v, unsigned int u);

int main()
{
   Jungle::Cheetah c;
   c.nap(4);
   c.stretch(4);
   
   addNumbers(10, 20);
   std::cout << "Hello World" << std::endl; 
   return 0;
}