#include <boost/variant.hpp>
#include <iostream>
#include <string>


struct QuietMode
{
    void beep() { std::cout << "..." << std::endl; }
};

struct NormalMode
{
    void beep() { std::cout << "beep" << std::endl; }
};

struct VerboseMode
{
    void beep() { std::cout << "beep beep beep" << std::endl; }
};


struct Machine
{
    template<typename ModeType>
    void setMode(ModeType mode)
    {
        mode_variant = mode;
    }
    
    void beep()
    {
        boost::apply_visitor(mode_visitor, mode_variant);
    }

private:
    boost::variant<NormalMode, QuietMode, VerboseMode> mode_variant;
    struct : boost::static_visitor<void>
    {
        template<typename ModeType>
        void operator()(ModeType& mode) const
        {
            mode.beep();
        }
    } mode_visitor;
};


int main()
{
    Machine machine;
    
    machine.setMode(VerboseMode{});
    machine.beep();
    
    machine.setMode(NormalMode{});
    machine.beep();
    
    machine.setMode(QuietMode{});
    machine.beep();
}
