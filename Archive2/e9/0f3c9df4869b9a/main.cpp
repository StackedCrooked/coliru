// An enum type
    enum class ENUMR : unsigned char {
        SYSTEM1,
        SYSTEM2,
        UNKNOWN
    };

// template class; will later be specialized based on ENUMR enumerators
    template<ENUMR S>
    class System
    {};

// specialized System class, for enumerator SYSTEM1
    template<>
    class System<ENUMR::SYSTEM1>
    {
    private:
        static constexpr char identifier { 'G' };
    };

// An observation class recorded from a certain System instance
    template<ENUMR Sys,short int Freq>
    class Obs {
    public:
        Obs():
        m_system {}, // does not work
        m_frequency {Freq}
        {};
        //{
        //    m_system = System<Sys> {};  // works
        //}
    private:
        System<Sys> m_system;
        short int   m_frequency;
    };

// dummy code to test the template classes
    int main ()
    {

        System<ENUMR::SYSTEM1> s1;

        System<ENUMR::UNKNOWN> s2;

        System<ENUMR::SYSTEM1> s3 (System<ENUMR::SYSTEM1>);

        Obs<ENUMR::SYSTEM1, 1> obs;
    }
    