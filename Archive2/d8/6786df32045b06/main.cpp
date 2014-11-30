#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// PACK UTILS (TAG VERSION) =============================

/*  find type T in a pack (recursive)
    This is used to find a TAG
*/
template<typename T, typename head, typename... tail>
struct type_at
{
	enum { _tmp = (std::is_same<T, typename std::decay<head>::type>::value) ? 0 : type_at<T, tail...>::_pos };
	enum { _pos = _tmp == -1 ? -1 : 1 + _tmp };
};

//  find type T in a pack (base)
template<typename T, typename head>
struct type_at<T, head>
{
	enum { _pos = (std::is_same< T, typename std::decay<head>::type>::value ? 1 : -1) };
};

/*  get the value at position pos in a pack
    This is used to retrieve a mandatory TAG parameter
*/
template<int pos, int curr>
struct get_at
{
	static_assert(pos >= 0, "Required parameter");

	template<typename head, typename... tail>
	static decltype(auto) get(head && h, tail && ... t) 
	{
		return get_at<pos, curr + 1>::get(std::forward<tail>(t)...);
	}
};

//  get the value at position pos in a pack (base)
template<int pos>
struct get_at<pos, pos>
{
	static_assert(pos >= 0, "Required parameter");
	
	template<typename head, typename... tail>
	static decltype(auto) get(head && h, tail && ...t)
	{
		return std::forward<head>(h);
	}
};

/*  as before, but this supports a default value in case
    pos is -1
    This is used to get an optional TAG parameter
*/
template<int pos, int curr>
struct get_optional
{
	template<typename T, typename... pack>
	static decltype(auto) get(T && def, pack && ... _pack)
	{
		return get_at<pos, curr>::get(std::forward<pack>(_pack)...);
	}
};

template<int curr>
struct get_optional<-1, curr>
{
	template<typename T, typename... pack>
	static decltype(auto) get(T && _default, pack && ...)
	{
		return std::forward<T>(_default);
	}
};
// =================================================

// PACK UTILS (PROXY VERSION) ======================

// Proxy containing [tag, value]
template<typename tag, typename type>
struct named_param_t
{
	using _tag = tag;
	using _type = type;

	template<typename T>
	named_param_t(T && value) 
	    : _value(std::forward<T>(value))
	{}

	type _value;
};

/*  Tagged proxy that allows syntax _name = value 
    operator=(T&&) returns a named_param_t instance
*/
template<typename tag>
struct named_param_proxy
{
	using _tag = tag;

	template<typename T>
	decltype(auto) operator=(T && value)
	{
		return named_param_t<tag, decltype(value)>{ std::forward<T>(value) };
	}
};

/*  Same as type_at but it's supposed to be used by passing
    a pack of named_param_t (_tag is looked for instead of a 
    plain type). This and type_at should be refactored.
*/
template<typename T, typename head, typename... tail>
struct named_type_at_p
{
	enum { _tmp = (std::is_same<T, typename head::_tag>::value) ? 0 : named_type_at_p<T, tail...>::_pos };
	enum { _pos = _tmp == -1 ? -1 : 1 + _tmp };
};

template<typename T, typename head>
struct named_type_at_p<T, head>
{
	enum { _pos = (std::is_same< T, typename head::_tag>::value ? 1 : -1) };
};

template<typename T, typename head, typename... tail>
struct named_type_at
{
	enum { _tmp = named_type_at_p<T, head, tail...>::_pos };
	enum { _pos = _tmp == 1 ? 0 : (_tmp == -1 ? -1 : _tmp-1) };
};

/*  Same as get_at but it's supposed to be used by passing
    a pack of named_param_t (_type is retrieved instead) 
    This and get_at should be refactored.
*/
template<int pos, int curr>
struct named_get_at
{
	static_assert(pos >= 0, "Required parameter");

	template<typename head, typename... tail>
	static decltype(auto) get(head && h, tail && ... t)
	{
		return named_get_at<pos, curr + 1>::get(std::forward<tail>(t)...);
	}
};

template<int pos>
struct named_get_at<pos, pos>
{
	static_assert(pos >= 0, "Required parameter");

	template<typename head, typename... tail>
	static decltype(auto) get(head && h, tail && ...t)
	{
		return std::forward<typename head::_type>(h._value);
	}
};

// Optional version
template<int pos, int curr>
struct named_get_optional
{
	template<typename T, typename... pack>
	static decltype(auto) get(T && def, pack && ... _pack)
	{
		return named_get_at<pos, curr>::get(std::forward<pack>(_pack)...);
	}
};

template<int curr>
struct named_get_optional<-1, curr>
{
	template<typename T, typename... pack>
	static decltype(auto) get(T && _default, pack && ...)
	{
		return std::forward<T>(_default);
	}
};
// =================================================

// CONVENIENCE MACROS FOR CLASS DESIGNERS ==========

#define TAG_OF(name) p_##name

#define REQUIRED_NAME(type) named_get_at< named_type_at<TAG_OF(type), pack...>::_pos, 0>::get(std::forward<pack>(_pack)...)
#define OPTIONAL_NAME(type, _defaultVal) named_get_optional< named_type_at<TAG_OF(type), pack...>::_pos, 0>::get(_defaultVal, std::forward<pack>(_pack)...)

#define REQUIRED_TAG(type) get_at< type_at<TAG_OF(type), pack...>::_pos, 0>::get(std::forward<pack>(_pack)...)
#define OPTIONAL_TAG(type, _defaultVal) get_optional< type_at<TAG_OF(type), pack...>::_pos, 0>::get(_defaultVal, std::forward<pack>(_pack)...)

#define CREATE_TAG(name)\
    struct p_##name{}; \
	named_param_proxy<p_##name> _##name; \
	p_##name __##name;

struct use_tags_t {} use_tags;
struct use_named_t {} use_named;

// FULL EXAMPLE ====================================

// step 1) generate tags you need
namespace 
{
	CREATE_TAG(title);
	CREATE_TAG(h);
	CREATE_TAG(w);
	CREATE_TAG(posx);
	CREATE_TAG(posy);
	CREATE_TAG(handle);
}

// step 2) use tags/proxies in your class
class window
{
public:
    // classic constructor
	window( string pTitle, int pH, int pW, 
	        int pPosx, int pPosy, int& pHandle)
	    :   title(move(pTitle)), h(pH), w(pW), posx(pPosx), posy(pPosy), handle(pHandle)
	{
	}

    // constructor using proxies (e.g. _title = "title")
	template<typename... pack>
	window(use_named_t, pack&&... _pack)
		:	window { REQUIRED_NAME(title), // required
			         OPTIONAL_NAME(h, 100), // optional
			         OPTIONAL_NAME(w, 400), // optional
			         OPTIONAL_NAME(posx, 0), // optional
			         OPTIONAL_NAME(posy, 0), // optional
			         REQUIRED_NAME(handle) } // required
	{

	}

    // constructor using tags (e.g. __title, "title")
	template<typename... pack>
	window(use_tags_t, pack&&... _pack)
		:	window { REQUIRED_TAG(title), // required
			         OPTIONAL_TAG(h, 100), // optional
			         OPTIONAL_TAG(w, 400), // optional
			         OPTIONAL_TAG(posx, 0), // optional
			         OPTIONAL_TAG(posy, 0), // optional
			         REQUIRED_TAG(handle) } // required
	{

	}

	friend ostream& operator<<(ostream& os, const window&);

private:
	string title;
	int h, w;
	int posx, posy;
	int& handle;
};

ostream& operator<<(ostream& os, const window& w)
{
	os << "WINDOW: " << w.title << " (" << w.h << "x" << w.w << "), at " << 
		w.posx << "," << w.posy << "->" << w.handle;
	return os;
}

int main()
{
    int i=5;
    {
        window w {use_tags, __title, "Title", __h, 10,  __w, 100, __handle, i};
        cout << w << endl;
    }
    
    {
        window w {use_named, _h = 10, _title = "Title", _handle = i, _w = 100};
        cout << w << endl;
    }
    
    {
        window w {"Title", 10, 400, 0, 0, i};
        cout << w << endl;
    }
}


