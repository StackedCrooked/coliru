#include <string>
#include <sstream>
#include <boost/utility/string_ref.hpp>

template <typename Range>
std::string expand(Range const& key)
{
    thread_local std::ostringstream oss;
    oss.str().clear();
    oss.clear();
    oss.seekp(0);
    oss << " (subst_for_" << key.to_string() << ':' << (rand()%42) << ") ";
    return oss.str();
}

#include <iostream>
int main()
{
    static const std::string msg_template = "{A}jahshs{b}jwuw{c}wuqjwhaha{d}{e}{f}jsj{g}\n";

    std::ostringstream builder;
    builder.str().reserve(1024); // reserve ample room, not crucial since we reuse it anyways

    for (size_t iterations = 1ul << 14; iterations; --iterations)
    {
        builder.str().resize(0);
        std::ostreambuf_iterator<char> out(builder);

        for(auto f(msg_template.begin()), l(msg_template.end()); f != l;)
        {
            switch(*f)
            {
                case '{' : 
                    {
                        auto s = ++f;
                        size_t n = 0;

                        while (f!=l && *f != '}')
                            ++f, ++n;

                        // key is [s,f] now
                        builder << expand(boost::string_ref(&*s, n));
                        
                        if (f!=l)
                            ++f; // skip '}'
                    }
                    break;
                default:
                    *out++ = *f++;
            }
        }
        // to make it slow, uncomment:
        std::cout << builder.str();
    }
}

