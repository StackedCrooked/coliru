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

auto dropWhile = [](auto pred){ 
    auto betterpred = [=](auto&& f) { if (!f) return false; return pred(f); };      
    return [=](auto xs){    
        return [=, p = boost::make_optional(betterpred)]() mutable {
            if (p)
            {
                while((*p)(xs()));
                p = boost::none;
            }
            return xs();
        };
    };
};