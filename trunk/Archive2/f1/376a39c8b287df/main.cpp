    #include <iostream>
    #include <map>
    #include <stdexcept>
    
    typedef double float64_t;
    
    namespace neuralnetwork {
    
        class IConnection {
            float64_t _value = 0.0;
        public:
            IConnection( float64_t v ) : _value(v) {}
            friend inline bool operator< ( const IConnection & lhs, const IConnection & rhs ) { return & lhs < & rhs; }
        };
    
        class CPerceptron {
            std::map<const IConnection *, float64_t> m_inputValues;
            public:
            void inputEvent(const IConnection * origin, double value);
            void addInputConnection( const IConnection * inConn );
        };
    
        void CPerceptron::addInputConnection( const IConnection * inConn )
        {
            m_inputValues.insert( std::pair<const IConnection *, float64_t>( inConn, 0.0f ) );
        }
    
    } // namespace neuralnetwork
    
    void neuralnetwork::CPerceptron::inputEvent(const neuralnetwork::IConnection * origin, double value)
    {
        std::map< const neuralnetwork::IConnection *, float64_t >::iterator
            it = m_inputValues.find( origin );
        if ( it == m_inputValues.end() )
        {
            throw std::runtime_error("Some error");
        }
    //   ...
    }
    
    int main( int argc, char *argv[] )
    {
        auto icp = new neuralnetwork::IConnection( 1.0 );
        neuralnetwork::CPerceptron cp;
        cp.addInputConnection( icp );
        cp.inputEvent( icp, 2.0 );
        std::cout << "No stack overflow here!" << std::endl;
        return 0;
    }
