#include <boost/any.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <iostream>
#include <memory>
#include <string>

struct ip_stats_t {
    std::string canary;
};

enum class EventId : uint32_t {
    // Place your new EventManager events here
    StatsData             = 0,
    StatsRequest          = 1,
    StatsReply            = 2,
    ApplianceStatsRequest = 3,
    ApplianceStatsReply   = 4,
    NullEvent             = 5, // Not implemented
};

namespace Events {

    template <EventId> struct Traits;

    template <> struct Traits<EventId::StatsData>             { using signal_type = boost::signals2::signal<void(int)>;                 } ;
    template <> struct Traits<EventId::StatsRequest>          { using signal_type = boost::signals2::signal<void(bool, bool)>;          } ;
    template <> struct Traits<EventId::StatsReply>            { using signal_type = boost::signals2::signal<void(std::string)>;         } ;
    template <> struct Traits<EventId::ApplianceStatsRequest> { using signal_type = boost::signals2::signal<void(double, ip_stats_t&)>; } ;
  //template <> struct Traits<EventId::NullEvent>             { using signal_type = boost::signals2::signal<void()>;                    } ;

    template <> struct Traits<EventId::ApplianceStatsReply> : Traits<EventId::ApplianceStatsRequest> { }; 
}

class EventManager {
  public:
    static EventManager& instance() {
        static EventManager instance;
        return instance;
    };

    template <EventId event, typename F>
    bool consume_event(F&& func) {
        get_slot<event>().connect(std::forward<F>(func));
        return true;
    }

    template <EventId event, typename... Args>
    void emit(Args&&... args) {
        get_slot<event>()(std::forward<Args>(args)...);
    }

  private:
    template <EventId event, typename Slot = typename Events::Traits<event>::signal_type, typename SlotPtr = boost::shared_ptr<Slot> >
    Slot& get_slot() {
        try {
            if (_event_map.find(event) == _event_map.end())
                _event_map.emplace(event, boost::make_shared<Slot>());

            return *boost::any_cast<SlotPtr>(_event_map[event]);
        }
        catch (boost::bad_any_cast const &e) {
            std::cerr << "Caught instance of boost::bad_any_cast: " << e.what() << " on event #" << static_cast<uint32_t>(event) << "\n";
            abort();
        }
    }

    EventManager() = default;
    std::map<EventId, boost::any> _event_map;
};

int main() {
    auto& emgr = EventManager::instance();

    emgr.consume_event<EventId::ApplianceStatsRequest>([](double d, ip_stats_t& v) { 
            std::cout << "d: " << d << ", v.canary: " << v.canary << "\n";
        });
    emgr.consume_event<EventId::ApplianceStatsRequest>([](double d, ip_stats_t& v) { 
            std::cout << "And you can register more than one\n";
        });


    ip_stats_t v { "This is statically checked" };
    emgr.emit<EventId::ApplianceStatsRequest>(3.142f, v);

    emgr.emit<EventId::StatsData>(42); // no connection, but works
    emgr.consume_event<EventId::StatsData>([](int) { std::cout << "Now it's connected\n"; });
    emgr.emit<EventId::StatsData>(42); // now with connection!

#if 0
    emgr.emit<EventId::ApplianceStatsRequest>();  // error: no match for call to ‘(boost::signals2::signal<void(double, ip_stats_t&)>) ()’
    emgr.consume_event<EventId::NullEvent>([]{}); // use of incomplete type Traits<NullEvent>
#endif
}
