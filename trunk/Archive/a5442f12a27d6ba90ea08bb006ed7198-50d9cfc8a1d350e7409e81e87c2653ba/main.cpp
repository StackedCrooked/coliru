template <typename T>
struct default_handle_deleter {
    void operator () ( T& handle ) {
        // No-op; handle will invoke default destructor upon exist. 
        // You should override this
    }
};

template <typename T, typename TDx = default_handle_deleter<T>>
class handle {
public:
    // I'm trying to default the below to `T` in the case that there is no handle_type on the deleter
	typedef typename TDx::handle_type handle_type;
	typedef TDx deleter_type;

}

int main ( int argc, char* argv[] ) {
    handle<int> testing;
}