template <typename First, typename Second>
struct Whatever{};

template <typename First, typename Second>
Whatever<First, Second> operator + (const First&, const Second&){
    return Whatever<First, Second>{};
}

auto lambda = [](){
    return "ciao" + 4;
};

int main()
{
    auto a = lambda();
    (void) sizeof a;
	return 0;
}