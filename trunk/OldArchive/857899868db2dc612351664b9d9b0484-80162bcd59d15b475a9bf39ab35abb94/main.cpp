template <typename Fun>
struct fuckQThread : QThread {
    fuckQThread() : fun{};
    template <typename FunF, DisableIfRelated<FunF, fuckQthread<Fun>>...>
    fuckQThread(FunF&& fun) : fun(std::forward<FunF>(fun)) {}

    void run() override { fun(); }

private:
    Fun fun;
}

template <typename FunF>
fuckQThread<Decay<FunF>> make_fuckQThread(FunF&& fun) {
    return { std::forward<FunF>(fun) };
}