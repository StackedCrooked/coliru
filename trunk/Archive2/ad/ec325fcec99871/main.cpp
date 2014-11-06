#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

typedef std::string CString ;
struct CComboBox {
    void InsertString(int,const CString&){}
    int GetCurSel() const {return 0;}
    void SetCurSel(int&) {}
} ;

template <typename T>
struct ComboBoxItem
{
  ComboBoxItem() {} 

  void SetOption( const T& t, const CString& dispString ) {
    m_ctrl.InsertString( static_cast<int>( m_options.size() ), dispString ) ;
    m_options.push_back( t ) ;
  } 
 
  T Current() const 
  {
    int id = m_ctrl.GetCurSel() ;
    return (0 <= id && id < (static_cast<int>( m_options.size())))
         ? m_options[id] : T() ;
  }

  void SetCurrent( const T& current ) 
  {
    int id = -1 ;
    for ( size_t i = 0 ; i < m_options.size() ; ++i ) {
      if( m_options[i] == current ) {
        id = static_cast<int>( i ) ; 
      }
    }
    if( id != -1 ) m_ctrl.SetCurSel( id ) ;
  }

  CComboBox m_ctrl ;
  std::vector< T > m_options ;
} ;

// 上のテンプレートと１つにしたいけれど、、、
template< typename T >
struct ComboBoxItem<boost::shared_ptr<T> >
{
  ComboBoxItem() {} 

  void SetOption( const boost::shared_ptr<T>& t, const CString& dispString ) {
    m_ctrl.InsertString( static_cast<int>( m_options.size() ), dispString ) ;
    m_options.push_back( t ) ;
  }
 
  boost::shared_ptr<T> Current() const 
  {
    int id = m_ctrl.GetCurSel() ;
    return (0 <= id && id < (static_cast<int>( m_options.size())))
         ? m_options[id] : boost::shared_ptr<T>() ;
  }

  void SetCurrent( const boost::shared_ptr<T>& current ) 
  {
    int id = -1 ;
    for ( size_t i = 0 ; i < m_options.size() ; ++i ) {
      if( *m_options[i] == *current ) {
        id = static_cast<int>( i ) ; 
      }
    }
    if( id == -1 ) return ;
    //std::vector< T >::const_iterator it = std::find( m_options.begin(), m_options.end(), current ) ;
    //if( it == m_options.end() ) return ;
    m_ctrl.SetCurSel( id ) ;
  }

  CComboBox m_ctrl ;
  std::vector< boost::shared_ptr<T> > m_options ;
} ;

int main() {}
