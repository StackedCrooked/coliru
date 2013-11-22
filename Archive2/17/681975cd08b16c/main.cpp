#include <iostream>
#include <initializer_list>

#include <string>
#include <sstream>
#include <map>
using std::string;

class text_thing
{
private:
    string m_text;

public:
    text_thing()
    {

    }

    text_thing(text_thing& other);
    text_thing(std::initializer_list< std::pair<const string, const string> > il);

    text_thing& operator=(std::initializer_list< std::pair<const string, const string> > il);

    operator string()
    {
        return m_text;
    }

};


class static_base
{
private:
    std::map<string, string> m_test_map;
    text_thing m_thing;

    static_base();


public:
    static static_base& getInstance()
    {
        static static_base instance;
        return instance;
    }

    string getText()
    {
        return (string)m_thing;
    }

};


typedef std::pair<const string, const string> spair;

text_thing::text_thing(text_thing& other)
{
    m_text = other.m_text;
}

text_thing::text_thing(std::initializer_list< std::pair<const string, const string> > il)
{
    std::stringstream text_gen;
    for (auto& apair : il)
    {
        text_gen << "{" << apair.first << ", " << apair.second << "}" << std::endl;
    }
}

text_thing& text_thing::operator=(std::initializer_list< std::pair<const string, const string> > il)
{
    std::stringstream text_gen;
    for (auto& apair : il)
    {
        text_gen << "{" << apair.first << ", " << apair.second << "}" << std::endl;
    }

    return *this;
}

static_base::static_base() :
        m_test_map{{"test", "1"}, {"test2", "2"}},  // Compiler fine with this
        m_thing{{"test", "1"}, {"test2", "2"}}      // Compiler doesn't like this
{

}

int main()
{

    std::cout << "Starting the program" << std::endl;

    std::cout << "The text thing: " << std::endl << static_base::getInstance().getText();

}
