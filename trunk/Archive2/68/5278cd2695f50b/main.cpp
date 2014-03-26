#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

struct Content
{
    std::string id, name;
    boost::shared_ptr<Content> mycontent;

  private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive &ar, const unsigned int /*version*/)
        {
            ar & id;
            ar & name;
            ar & mycontent;
        }   

  public:
    Content() {}
    typedef int parameter_strings;
    Content(const parameter_strings & parms) { }

    ~Content() {}
};

int main()
{
    boost::archive::text_oarchive ao(std::cout);

    Content x;
    ao << x;
}
