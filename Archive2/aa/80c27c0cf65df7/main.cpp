#define NDEBUG
#undef DEBUG
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/qi.hpp>
#include <thread>
#include <iomanip>

namespace io = boost::iostreams;
namespace qi = boost::spirit::qi;

template <typename Key, typename Value> 
struct text_multi_lookup {
    text_multi_lookup(char const* begin, char const* end)
        : _map_begin(begin), 
          _map_end(end)
    {
    }

  private:
    friend struct iterator;
    enum : char { nl = '\n' };
    
    using rawit = char const*;
    rawit _map_begin, _map_end;

    rawit start_of_line(rawit it) const {
        while (it > _map_begin) if (*--it == nl) return it+1;
        assert(it == _map_begin);
        return it;
    }

    rawit end_of_line(rawit it) const {
        while (it < _map_end) if (*it++ == nl) return it;
        assert(it == _map_end);
        return it;
    }

  public:
    struct value_type final {
        rawit beg, end;
        Key   key;
        Value value;
        
        boost::string_ref str() const { return { beg, size_t(end-beg) }; }
    };

    struct iterator : boost::iterator_facade<iterator, boost::string_ref, boost::bidirectional_traversal_tag, value_type> {

        iterator(text_multi_lookup const& d, rawit it) : _region(&d), _data { it, nullptr, Key{}, Value{} } { 
            assert(_data.beg == _region->start_of_line(_data.beg));
        }

      private:
        friend text_multi_lookup;

        text_multi_lookup const* _region;
        value_type mutable _data;

        void ensure_parsed() const {
            if (!_data.end) 
            {
                assert(_data.beg == _region->start_of_line(_data.beg));
                auto b = _data.beg;
                _data.end = _region->end_of_line(_data.beg);

                if (!qi::phrase_parse(
                            b, _data.end,
                            qi::auto_ >> qi::auto_ >> qi::eoi,
                            qi::space,
                            _data.key, _data.value)) 
                {
                    std::cerr << "Problem in: " << std::string(_data.beg, _data.end) 
                              << "at:         " << std::setw(_data.end-_data.beg) << std::right << std::string(_data.beg,_data.end);
                    assert(false);
                }
            }
        }

        static iterator mid_point(iterator const& a, iterator const& b) {
            assert(a._region == b._region);
            return { *a._region, a._region->start_of_line(a._data.beg + (b._data.beg -a._data.beg)/2) };
        }

      public:
        value_type const& dereference() const {
            ensure_parsed();
            return _data;
        }

        bool equal(iterator const& o) const {
            return (_region == o._region) && (_data.beg == o._data.beg);
        }

        void increment() {
            _data = { _region->end_of_line(_data.beg), nullptr, Key{}, Value{} };
            assert(_data.beg == _region->start_of_line(_data.beg));
        }
    };

    using const_iterator = iterator;

    const_iterator begin()  const { return { *this, _map_begin }; }
    const_iterator end()    const { return { *this, _map_end   }; }
    const_iterator cbegin() const { return { *this, _map_begin }; }
    const_iterator cend()   const { return { *this, _map_end   }; }

    template <typename CompatibleKey>
    const_iterator lower_bound(CompatibleKey const& key) const {
        auto f(begin()), l(end());
        while (f!=l) {
            auto m = iterator::mid_point(f,l);

            if (m->key < key)
                (f = m)++;
            else
                l = m;
        }
        return f;
    }

    template <typename CompatibleKey>
    const_iterator upper_bound(CompatibleKey const& key) const {
        return upper_bound(key, begin());
    }

  private:
    template <typename CompatibleKey>
    const_iterator upper_bound(CompatibleKey const& key, const_iterator f) const {
        auto l(end());
        while (f!=l) {
            auto m = iterator::mid_point(f,l);

            if (key < m->key)
                l = m;
            else
                (f = m)++;
        }
        return f;
    }

  public:
    template <typename CompatibleKey>
    std::pair<const_iterator, const_iterator> equal_range(CompatibleKey const& key) const {
        auto lb = lower_bound(key);
        return { lb, upper_bound(key, lb) };
    }

};

#include <iostream>

int main() {
    io::mapped_file_source map("input.txt");
    text_multi_lookup<double, unsigned int> tml(map.data(), map.data() + map.size());

    auto const e = tml.end();

    for(auto&& line : tml)
    {
        std::cout << line.str();

        auto er = tml.equal_range(line.key);

        if (er.first  != e) std::cout << " lower: " << er.first->str();
        if (er.second != e) std::cout << " upper: " << er.second->str();
    }
}
