#include <stdexcept>

template <typename T, typename Pred>
class limited {
private:
    Pred pred;
	T t;
public:
	limited() : pred{}, t{} {}
	
	limited(T t) : pred{}, t{pred(t) ? t : (throw std::domain_error("not a valid value"))} {}	
	
	template <typename ...Args>
	limited(Args ...args) : pred{}, t(args...) {}
	
	limited<T, Pred> operator=(T rhs)
	{
		if (!pred(rhs))
			throw std::domain_error("not a valid value");
			
		t = rhs;
	}
	
	operator T () const
	{
		return t;
	}
};

struct valid_color_range {
    bool operator()(float c) {
        return c >= 0.0f && c <= 1.0f;
    }
};

using component = limited<float, valid_color_range>;

struct color {
    component red;
    component green;
    component blue;
    component alpha;
    
    color(float red, float green, float blue, float alpha)
      : red{red}, green{green}, blue{blue}, alpha{alpha}
    {}	
};

int main()
{
	color red = {1.0f, 0.0f, 0.0f, 1.0f};
	color blue = {0.0f, 0.0f, 2.0f, 1.0f};
}
