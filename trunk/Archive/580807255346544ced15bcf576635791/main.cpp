


template<typename T>
struct basic_scenario
{
    void begin() { static_cast<T&>(*this).do_begin(); }
    
    void middle() { static_cast<T&>(*this).do_middle(); }        
    
    void end() { static_cast<T&>(*this).do_end(); }
 };


struct my_scenario : basic_feature<my_scenario>, throat_scraper
{
    void do_begin() { this->clear_troat(); }
    void do_middle() { /* ... */  }
    void do_end() { /* ... */  }    
};


