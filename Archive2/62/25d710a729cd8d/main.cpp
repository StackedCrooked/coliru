template<int N = 1, class Fun, class... Args>
void timeExec(string name, Fun fun, Args&&... args) {

    auto const start = chrono::steady_clock::now();

    for(int i = 0; i < N; ++i) {
        fun(std::forward<Args>(args)...);
    }

    auto const end = chrono::steady_clock::now();

    auto const diff = chrono::duration<double, milli>(end - start);
    cout << name << ": "<< diff.count() << " ms.\n";
}
