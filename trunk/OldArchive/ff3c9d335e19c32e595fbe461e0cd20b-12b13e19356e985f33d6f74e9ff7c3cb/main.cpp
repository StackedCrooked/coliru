int main()
{
    using std::get;

    std::istringstream stream { "0 1 2 3 4 5 6 7 8 9 10 11" };

    using acc_type = std::vector<int>;
    auto bindings = fix(
            // Parser
            [&stream](auto&& selves, acc_type acc) -> acc_type
            {
                auto& filter = get<1>(selves);
                int i;
                if(stream >> i) return filter(i, std::move(acc));
                return acc;
            },
            // Filter
            [](auto&& selves, int i, acc_type acc) -> acc_type
            {
                auto& parser = get<0>(selves);
                if(i % 2 == 0) acc.emplace_back(i);
                return parser(std::move(acc));
            }
    );

    auto& parser = get<0>(bindings);

    auto result = parser(acc_type {});
    assert( result.size() == 6 );
}
