class Forwarder {
public:
    const time::steady_clock::TimePoint&
    getIStime() const;

    const time::steady_clock::TimePoint&
    getDRtime() const;
private:
    time::steady_clock::TimePoint IStime;
    time::steady_clock::TimePoint DRtime;
};


inline time::steady_clock::TimePoint&
Forwarder::getIStime()
{
  return IStime;
}

inline time::steady_clock::TimePoint&
Forwarder::getDRtime()
{
  return DRtime;
}