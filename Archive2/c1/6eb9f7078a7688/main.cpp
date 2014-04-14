

    template <typename F, typename ... A>
    inline void
    conduce_back(F &&f, A && ... a)
    {
      ++size_v;

      // works
      T & t ( * (new (&back()) T(std::forward<A>(a)...)));

      // doesn't work:
      // T & t { * (new (&back()) T(std::forward<A>(a)...)) };

      f(t);
    }