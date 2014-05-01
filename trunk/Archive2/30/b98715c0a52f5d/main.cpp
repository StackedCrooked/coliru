auto toStream = [](auto xs){
    using std::begin;
    using std::end;
    return [curr = begin(xs), r = std::move(xs)]() mutable -> boost::optional<decltype(*begin(xs))>{
        if (curr != end(r))
            return *curr++;
        return boost::none;
    };
};