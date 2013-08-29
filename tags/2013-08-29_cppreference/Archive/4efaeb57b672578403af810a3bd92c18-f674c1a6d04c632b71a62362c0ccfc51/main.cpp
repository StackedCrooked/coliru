

//
// wrapper function which has a name that more closely matches the user's intent
//
int bounded(int x, int lower)
{
    return std::max(x, y);    
}


//
// simple type wrapper
//
auto result = bounded<int, 0, 9>{};
result = x;


//
// goofy functor
//
auto result = at_least(10)(x);


//
// silly expression template
//
auto result = (0 <= boost::convolutions2::bondage::clamp{} <= 10);
result = x;
