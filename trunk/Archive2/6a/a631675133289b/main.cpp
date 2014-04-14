    #include <iostream>
    #include <map>
    #include <stdexcept>
    #include <memory>

    typedef double float64_t;
    
    namespace neuralnetwork {
    
        class IConnection {
            float64_t _value = 0.0;
        public:
            IConnection( float64_t v ) : _value(v) {}
            IConnection( const IConnection & ) = delete;
            const float64_t & get() const { return _value; }
            friend inline bool operator< ( const IConnection & lhs, const IConnection & rhs ) { return & lhs.get() < & rhs.get(); }
        };
    
        class CPerceptron {
            std::map<const std::shared_ptr<IConnection>, float64_t>
            m_inputValues, m_isInputReady;
            public:
            void inputEvent( const std::shared_ptr<IConnection> &origin, double value);
            void addInputConnection( const std::shared_ptr<IConnection> &inConn );
        };
    
        void CPerceptron::addInputConnection( const std::shared_ptr<IConnection> &inConn )
        {
            m_inputValues.insert( std::pair<const std::shared_ptr<IConnection>, float64_t>( inConn, 0.0f ) );
        }
    
    } // namespace neuralnetwork
    
    void neuralnetwork::CPerceptron::inputEvent(const std::shared_ptr<neuralnetwork::IConnection> &origin, double value)
    {
        std::map< const std::shared_ptr<neuralnetwork::IConnection>, float64_t >::iterator
            it = m_inputValues.find( origin );
        if ( it == m_inputValues.end() )
        {
            throw std::runtime_error("Some error");
        }
    //   ...
    }
    
    int main( int argc, char *argv[] )
    {
        std::shared_ptr<neuralnetwork::IConnection> icp (new neuralnetwork::IConnection( 1.0 ));
        neuralnetwork::CPerceptron cp;
        cp.addInputConnection( icp );
        cp.inputEvent( icp, 2.0 );
        std::cout << "No stack overflow here!" << std::endl;
        return 0;
    }
