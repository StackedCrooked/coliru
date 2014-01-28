#include <vector>
#include "json.hpp"

struct X {
    static X from_json(JSON::Value const& v);

    std::string var1;
    double      var2;
};

int main()
{
    auto doc = as_object(JSON::parse(
        "{\n"
        "    // some values\n"
        "    \"mykey\": [\n"
        "        {\n"
        "            \"var1\": \"value1_str\",\n"
        "            \"var2\" : 3.14\n"
        "        }\n"
        "    ]\n"
        "    // some other values\n"
        "}\n"
        ));

    if (doc.has_key("mykey"))
    {
        X data = X::from_json(doc["mykey"]);
        std::cout << "X.var1: " << data.var1 << "\n";
        std::cout << "X.var2: " << data.var2 << "\n";
    }
}

X X::from_json(JSON::Value const& v)
{
    X result;
    auto& o = as_object(as_array(v)[0]);
    result.var1 = as_string(o["var1"]);
    result.var2 = as_double(o["var2"]);

    return result;
}
