#include <string>
#include <sstream>
#include <boost/utility/string_ref.hpp>

template <typename Record, typename Key>
void insert_expanded(Record const& data, std::ostream& os, Key const& key)
{
    if      ("title"    == key) os << data.title;
    else if ("greeting" == key) os << data.greeting;
    else if ("name"     == key) os << data.name;
    else if ("surname"  == key) os << data.surname;
    else if ("product"  == key) os << data.product;
    else if ("email"    == key) os << data.email;
    else if ("warranty" == key) os << data.warranty_months; // not just strings supported
    else os << "#ERR:" << key << "#";
}

#include <iostream>
int main()
{
    static const std::string msg_template = 
        "Mailmerge\nTo: {title} {name} {surname}\n\n{greeting} {title} {name},\n\n"
        "We'd like to congratulate you with your recent purchase of \"{product}\" in our shop. Your warranty expires in {warranty} months. Any support queries can be directed to {email}.\n\n"
        "We hope to see you back soon,\n"
        "Best regards,\n"
        "---------------------------------------------------------------------------------\n"
        "The Spam Department\n"
        "---------------------------------------------------------------------------------\n"
        ;

    std::ostringstream builder;
    builder.str().reserve(1024); // reserve ample room, not crucial since we reuse it anyways

    static struct { 
        const char *title, *greeting, *name, *surname, *product, *email;
        int warranty_months; } const database[] = 
    { 
        { "Ms.", "Hi there,", "Catherine", "Dumas", "Taxidermist Starter Set", "support@taxidermia-world.com", 24 },
        { "Mr.", "Dearest", "Michael", "Duchene", "Philips professional blender 210MW", "support@shop.com", 12 },
        { "Fam.", "Greetings,", "", "Ozbourne", "Slayer Greates Hits Vol. I", "support@cd-baby.com", 47 },
    };

    for (auto& record : database)
    {
        builder.seekp(0);
        builder.str("");
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
                        insert_expanded(record, builder, boost::string_ref(&*s, n));
                        
                        if (f!=l)
                            ++f; // skip '}'
                    }
                    break;
                default:
                    *out++ = *f++;
            }
        }
        //
        // to make it slow, uncomment:
        std::cout << builder.str();
    }
}

