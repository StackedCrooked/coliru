#include <boost/variant.hpp>
#include <iostream>

struct Machine
{
    enum Language { en, fr };
    Machine(Language language) : mVariant(MakeVariant(language)) {}
    
    const char* greet() const
    {
        return boost::apply_visitor(Greeting(), mVariant);
    }
    
    const char* curse() const
    {
        return boost::apply_visitor(Curse(), mVariant);
    }
    
private:
    struct English : boost::static_visitor<const char*>
    {
        const char* greet() const { return "Hello!"; }
        const char* curse() const { return "Damnit!"; }
    };
    
    struct French
    {
        const char* greet() const { return "Bonjour!"; }
        const char* curse() const { return "Nom de Dieu!"; }
    };
    
    struct Greeting : boost::static_visitor<const char*>
    {
        template<typename Lang>
        const char* operator()(const Lang& lang) const { return lang.greet(); }
    };
    
    struct Curse : boost::static_visitor<const char*>
    {
        template<typename Lang>
        const char* operator()(const Lang& lang) const { return lang.curse(); }
    };
    
    typedef boost::variant<English, French> Variant;    
    
    Variant MakeVariant(Language lang)
    {
        if (lang == en) return Variant(English());
        return Variant(French());;
    }
    Variant mVariant;
};


int main()
{
    Machine english_machine(Machine::en); 
    std::cout << english_machine.greet() << std::endl;
    std::cout << english_machine.curse() << std::endl;
    
    Machine french_machine(Machine::fr); 
    std::cout << french_machine.greet() << std::endl;
    std::cout << french_machine.curse() << std::endl;
}