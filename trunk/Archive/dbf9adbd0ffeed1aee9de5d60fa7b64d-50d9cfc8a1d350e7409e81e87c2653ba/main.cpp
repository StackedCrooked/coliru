template <typename T, typename TContainer = std::vector<T>>
class BlockingQueue {
private:
	typedef std::lock_guard<std::mutex> TLockGuard;

	std::mutex op;
	Threading::AutoResetEvent qblock;
	std::queue<T, TContainer> q;

public:
	BlockingQueue ( ) {

	}

	BlockingQueue ( BlockingQueue&& mov ) {
		TLockGuard guard( mov.op );
		qblock = std::move( mov.qblock );
		q = std::move( mov.q );
	}

	BlockingQueue& operator= ( BlockingQueue&& mov ) {
		TLockGuard guard( mov.op );
		qblock = std::move( mov.qblock );
		q = std::move( mov.q );
	}

	template <typename ...T>
	void Emplace ( T&&... args ) {
		TLockGuard guard( op );
		q.emplace( std::forward<T>( args )... );
		qblock.Set();
	}

	template <typename T0>
	void Emplace ( T0&& arg0 ) {
		TLockGuard guard( op );
		q.emplace( std::forward<T0>( arg0 ) );
		qblock.Set();
	}

	void Push ( const T& item ) {
		TLockGuard guard( op );
		q.push( item );
		qblock.Set();
	}

	void Push ( T&& item ) {
		TLockGuard guard( op );
		q.push( item );
		qblock.Set();
	}

	void Pop () {
		TLockGuard guard( op );
		q.pop();
	}

	T& Top ( ) {
		if ( Empty() ) {
			qblock.Wait( );
		}
		TLockGuard guard( op );
		return q.top();
	}

	const T& Top ( ) const {
		if ( Empty() ) {
			qblock.Wait( );
		}
		TLockGuard guard( op );
		return q.top();
	}

	bool Empty () const {
		TLockGuard guard( op );
		return q.empty();
	}
};
