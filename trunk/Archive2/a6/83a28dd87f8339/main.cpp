#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,N,...) N
#define TOKENIZE_ARGS(...) #__VA_ARGS__

TOKENIZE_ARGS(baz,boo)

namespace std { class string; }

struct Foo
{
    double baz;
    std::string boo;
}

struct Node
{
    Node(const std::string &nmspace) : ns(nmspace) {}
    std::string ns;
    
    void param(const std::string &name, double &out, const double &defaultVal) const
    {
        if (name == "baz") out = 42.0;   
    }
    
    void param(const std::string &name, std::string &out, const std::string &defaultVal) const
    {
        if (name == "boo") out = "yesindeedy";
    }
}

template<typename T, typename Args...>
Node &get_param_from(const Node &node, const std::string &name, T &out, const T &defaultVal)
{
    node.param(name,out,defaultVal);
    return node;
}

template<typename T, typename... Args>    	// note the "..."
void am3p_get_ros_params(const char* s, T value, Args... args)	// note the "..."
{
	while (s && *s) {
		if (*s=='%' && *++s!='%') {	// a format specifier (ignore which one it is)
			std::cout << value;		// use first non-format argument
			return printf(++s, args...); 	// ``peel off'' first argument
		}
		std::cout << *s++;
	}
	throw std::runtime error("extra arguments provided to printf");
}

// to verify, run the preprocessor alone (g++ -E):
VA_NUM_ARGS(x,y,z,w)

#define AM3P_GET_ROS_PARAMS(ns,...) am3p_get_ros_params(Node(ns),