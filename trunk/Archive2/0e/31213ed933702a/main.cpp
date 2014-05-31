    #include <iostream>
    #include <vector>
    #include <boost/variant.hpp>
    
    typedef boost::variant< std::vector<int>, 
                            std::vector<char>, 
                            std::vector<float> 
                           > VecRMPType;
     
    struct Widgets{
        int widget_id;
        VecRMPType rmps_vec ;
        
        template< typename T>
        Widgets(int wid, T rmps_vec_ ) : 
        widget_id(wid), rmps_vec( std::move(rmps_vec_) ) 
        {
        }
        
        Widgets( const Widgets&& wids_ ) :
        widget_id( wids_.widget_id), rmps_vec(wids_.rmps_vec )
        {
        }
        /*
        Widgets( const Widgets& wids_ ):
        widget_id( wids_.widget_id), rmps_vec( std::move(wids_.rmps_vec) )
        {
        }
        */
    };
    
    class Layers {
    
        int symb_id;
        std::vector< Widgets > widgets ;
        
        Layers(const Layers& ) ;
        Layers& operator=(const Layers& ) ;
        
        public:
            Layers(int sid_, std::vector<Widgets> wids_ ):
            symb_id(sid_), widgets(std::move(wids_) )
            { }
            
            Layers(const Layers&& L_ ): 
            symb_id(L_.symb_id), widgets( std::move(L_.widgets) )
            { }
    };

int main(){ return 0 ;}