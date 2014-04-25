auto takeWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable -> decltype(xs()){
        if (p)
        {
            decltype(xs()) v;
            if (p && (v = xs()) && p(*v))
                return v;
            p = boost::none;
        }
        return boost::none;
    };
};};

auto dropWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable {
        if (p)
        {
            decltype(xs()) v;
            while ((v = xs()) && p(*v))
                ;
            p = boost::none;
        }
        return xs();
    };
};};