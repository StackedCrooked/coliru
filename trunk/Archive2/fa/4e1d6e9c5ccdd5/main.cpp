

namespace detail {


void get(lua_State* L, int i, bool& b)
{
    b = lua_toboolean(L, i);
}


void get(lua_State* L, int i, std::string& s)
{
    std::string::size_type len = 0;
    if (auto b = lua_tolstring(L, i, &len))
    {
        s.assign(b, b + len);
    }
}


// etc...


} // namespace detail



template<typename T>
T get(lua_State* L, int i)
{
    T t;
    detail::get(L, i, t);
    return t;
}