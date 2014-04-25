auto takeWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable -> decltype(xs()){
        decltype(xs()) v;
        if (p && (v = xs()) && p(*v))
            return v;
        p = boost::none;
        return boost::none;
    };
};};

auto dropWhile = [](auto pred){ return [=](auto xs){
    return [=, p = boost::make_optional(pred)]() mutable {
        decltype(xs()) v;
        while (p && (v = xs()) && p(*v))
            ;
        p = boost::none;
        return xs();
    };
};};