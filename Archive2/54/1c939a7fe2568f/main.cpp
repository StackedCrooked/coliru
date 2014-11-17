#include <iostream>
#include <cstring>
#include <typeinfo>

typedef unsigned char uint8_T;
typedef unsigned short uint16_T;
typedef int int32_T;
typedef float real32_T;
typedef unsigned int uint32_T ;

template< typename T,  std::ostream& logger = std::cout >
struct var 
{
    static_assert( std::is_same<T, int32_T >::value 
                || std::is_same<T, real32_T >::value 
                || std::is_same<T, uint16_T >::value 
                || std::is_same<T, uint8_T >::value
                || std::is_same<T, uint32_T >::value ,
                "Not a Supported Type" ) ;
    var( ): _x( ), _os( logger ) { }
    var& operator = ( const T& t ) 
    {
        if( _x != t )
        {
            isChanged = true ;
            _x = t ;
            _os << "Changed \n";
        }
        else
        {
            isChanged = false ;
            _os << "UnChanged \n";
        }
        return *this ;
    }
    
    operator T& ( ) 
    {
        return _x  ;
    }
    
    private:
        T _x ;
        bool isChanged ;
        std::ostream& _os ;
};


template< typename T,std::size_t N, std::ostream& logger  >
struct var <T[N], logger >
{
    var( ) :_x(),_os( logger )
    {  
    }
    var& operator = (  const T t[N] ) 
    {
        if( !std::memcmp(_x, t, N ) )
        {   
            isChanged = true ;
            std::memcpy( _x, t, N ) ;
        }
        else
        {
            isChanged = false ;
        }
        return *this ;
    }

    var& operator = (  const char* const label ) 
    {
        std::size_t len = std::strlen( label ) ;
        if( std::memcmp(_x, label, len ) != 0 )
        {    
            isChanged = true ;
            std::memcpy( _x, label, len ) ;
            _os << "Changed \n";
        }
        else
        {
            isChanged = false ;
            _os << "UnChanged \n";
        }  
        return *this ;
    }
    
    operator T* ( ) 
    {
        return _x  ;
    }
    
    private:
        T _x[N] ;
        bool isChanged ;
        std::ostream& _os ;
};


struct Bus_P_Airspeed
{
  var<uint8_T> Airspeed_Fail_Flag_Cont__Vis;
  var<uint8_T> Airspeed_Max_Allowable_Tape_Cont__Vis;
  var<int32_T> Airspeed_Max_Allowable_Tape__Warning_Region__PosnY;
  var<uint32_T> Airspeed_Max_Allowable_Tape__Warning_Region__SizY;
  var<int32_T> Airspeed_Max_Allowable_Tape__Caution_Region__PosnY;
  var<uint32_T> Airspeed_Max_Allowable_Tape__Caution_Region__SizY;
  var<uint8_T> Airspeed_Max_Allowable_Tape__Caution_Region__Color;
  var<uint8_T> Airspeed_Max_Allowable_Tape__Caution_Region__FillIdx;
  var<uint8_T> Airspeed_Max_Allowable_Tape__Warning_Region__FillIdx;
  var<uint8_T> Airspeed_Max_Allowable_Tape__Warning_Region__Color;
  var<uint8_T> Airspeed_Digital_Readout__Ones_Sym__Color;
  var<uint8_T> Airspeed_Digital_Readout__Hundreds_Sym__Color;
  var<uint8_T> Airspeed_Digital_Readout__Tens_Sym__Color;
  var<int32_T> Airspeed_Digital_Readout__Tens_Sym__PosnY;
  var<int32_T> Airspeed_Digital_Readout__Ones_Sym__PosnY;
  var<int32_T> Airspeed_Digital_Readout__Hundreds_Sym__PosnY;
  var<uint8_T> Airspeed_Readout_Cont__Vis;
  var<int32_T> Airspeed_Reference_Bug_Cont__PosnY;
  var<uint8_T> Airspeed_Reference_Bug_Cont__Vis;
  var<uint8_T[16]> Airspeed_Reference_Readout__Readout_Value_Label__LblStr;
  var<uint8_T> Airspeed_Reference_Readout_Cont__Vis;
  var<int32_T> Airspeed_Tape__Tape_MutEx__PosnY;
  var<uint16_T> Airspeed_Tape__Tape_MutEx__VisChild;
  var<uint8_T> Airspeed_Tape__Tape_MutEx__Vis;
  var<uint16_T> Airspeed_Readout_Window__Readout_MutEx__VisChild;
  var<uint8_T> Airspeed_Readout_Window_Cont__Vis;
  var<uint8_T> Airspeed_Declutter_Cont__Vis;
} ;

Bus_P_Airspeed Bus_P_Airspeed_Data ;


void some_process()
{ 
    Bus_P_Airspeed_Data.Airspeed_Max_Allowable_Tape_Cont__Vis = 1; // Changed
    Bus_P_Airspeed_Data.Airspeed_Max_Allowable_Tape__Caution_Region__PosnY = -550 ;// Changed
    Bus_P_Airspeed_Data.Airspeed_Reference_Readout__Readout_Value_Label__LblStr = "ABC 42";// Changed
    Bus_P_Airspeed_Data.Airspeed_Max_Allowable_Tape__Warning_Region__SizY = 653;
}

void other_func( uint8_T x  )
{
   //....
   
    Bus_P_Airspeed_Data.Airspeed_Max_Allowable_Tape__Caution_Region__PosnY = x; // Changed
    Bus_P_Airspeed_Data.Airspeed_Max_Allowable_Tape_Cont__Vis =  1 ; // Unchanged
    Bus_P_Airspeed_Data.Airspeed_Reference_Readout__Readout_Value_Label__LblStr = "ABC 42";// UnChanged
}

int main()
{
    some_process ( );
    other_func( 56 );
}
