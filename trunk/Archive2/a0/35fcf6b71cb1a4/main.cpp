auto takeWhile = [](auto pred){ return [=](auto xs){
    return [p = boost::make_optional(pred)]() mutable -> decltype(xs()){
        if (p)
            if (auto v = xs())
                if (p(*v))
                    return v;
                else
                    p = boost::none;
        return boost::none;
    }
};};