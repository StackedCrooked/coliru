#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <unordered_map>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost { namespace serialization {

    template<class Archive, typename... TArgs >
        inline void save(Archive & ar, std::unordered_map<TArgs...> const&t, unsigned) {
            boost::serialization::stl::save_collection<Archive, std::unordered_map<TArgs...> >(ar, t);
        }

    template<class Archive, typename... TArgs >
        inline void load(Archive & ar, std::unordered_map<TArgs...> &t, unsigned) {
            boost::serialization::stl::load_collection<Archive,
                std::unordered_map<TArgs...>,
                boost::serialization::stl::archive_input_map<
                    Archive, std::unordered_map<TArgs...> >,
                boost::serialization::stl::no_reserve_imp<std::unordered_map<TArgs...> >
                    >(ar, t);
        }

    // split non-intrusive serialization function member into separate
    // non intrusive save/load member functions
    template <class Archive, typename... TArgs>
        inline void serialize(Archive & ar, std::unordered_map<TArgs...> &t, unsigned file_version) {
            boost::serialization::split_free(ar, t, file_version);
        }
} }

#include <boost/serialization/base_object.hpp>

class StringItem;

class Item {
  protected:
    unsigned int _refc;
    static unsigned int _total_alloc;

    //other code
    Item() : _refc(0) { }
    virtual ~Item() {}

  private:
    friend class boost::serialization::access;

    template<class Archive>
        void serialize(Archive & ar, unsigned)
    {
        ar & _refc;
        //ar & _total_alloc; // wut? a static?!
    }
};

/*static*/ unsigned int Item::_total_alloc;

class StringItem : public Item {
  public:
    StringItem(std::string s = "") : _s(std::move(s)) { }
  private:
    std::string _s;

    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & boost::serialization::base_object<Item>(*this);    
            ar & _s;
        }
};


struct Model {
    virtual ~Model() {}
    template<class Archive> void serialize(Archive&r, unsigned) { }
};

class TokenFinder : public Model
{
  public:
    TokenFinder(void) : _element_count(0) {}

    virtual ~TokenFinder(void) {}

    virtual void insert_item(Item *item) { _elements[item] = _elements.size()+1; }

  private:
    /** Map to store tokens together with their number of occurrences. */
    std::unordered_map<Item*, unsigned long> _elements;
    unsigned long _element_count;

    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar.template register_type<StringItem>();
            ar & boost::serialization::base_object<Model>(*this);    
            ar & _elements;
            ar & _element_count;
        }
};

int main()
{
    boost::archive::text_oarchive oa(std::cout);

    std::vector<StringItem> seed_data {
        {"hello"},{"world"},{"the"},{"lazy"},{"moon"}, {"cow-jumped"} 
    };



    TokenFinder tf;
    for(auto& si : seed_data)
        tf.insert_item(&si);
 
    oa << tf;

}
