template <typename tkey = Furrovine::String>
    class ResourceCache {
	public:
		typedef tkey TKey;

	private:
		struct ResourceBase { 
			
			virtual ~ResourceBase() {

			}

		};

		template <typename T> 
		struct ResourceHolder : ResourceBase {
			T resource;

			ResourceHolder( T t ) : t( std::move(resource) ) {

			}
		};

		std::unordered_map<TKey, ulword> resourceindices;
		std::vector<ptr<ResourceBase>> resources;

	public:
		template <typename T>
		void Add ( const TKey& key, std::unique_ptr<T> value ) {
			Add( key, value.release() );
		}

		template <typename T>
		void Add ( const TKey& key, ptr<T> value ) {
			Add( key, value.release() );
		}

		template <typename T>
		void Add ( const TKey& key, T* value ) {

		}

		template <typename T>
		bool TryAdd ( const TKey& key, std::unique_ptr<T> value ) {
			return TryAdd( key, value.release() );
		}

		template <typename T>
		bool TryAdd ( const TKey& key, ptr<T> value ) {
			return TryAdd( key, value.release() );
		}

		template <typename T>
		bool TryAdd ( const TKey& key, T* value ) {
			if ( value == null )
				return false;

			auto index = resourceindices.find( key );
			if ( index == resourceindices.end() ) {
				resourceindices.insert( std::make_pair( key, resources.size() ) );
				resources.push_back( make_ptr( ResourceHolder<T>( *value ) ) );
				return true;
			}
			return false;
		}

		template <typename T> 
		bool TryGet ( const TKey& id, T*& resource ) {
			auto index = resourceindices.find( id );
			if ( index != resourceindices.end() ) {
				ResourceHolder<T>* cacheholder = dynamic_cast<ResourceHolder<T>*>( resources[ index->second ].get() );
				if ( cacheholder != null ) {
					resource = &(cacheholder->resource);
				}
			}
		}

		template <typename T> 
		T* TryGet ( const TKey& id ) {
			T* res = null;
			TryGet( id, res );
			return res;
		}

		template <typename T> 
		T& Get ( const TKey& id ) {
			ResourceHolder<T>* resourceholder = null;
			auto index = resourceindices.find( id );
#ifdef FURROVINE_DEBUG
			furrovineassert( index != resourceindices.end() && index->second < resources.size(), "Resource with specific id does not exist" );
			furrovineassert( resources[ index->second ].get() != null, "Resource for id is null" );
#endif // FURROVINE_DEBUG
			resourceholder = dynamic_cast<ResourceHolder<T>*>( resources[ index->second ].get() );
#ifdef FURROVINE_DEBUG
			furrovineassert( resourceholder != null, "Resource is not of the specified type T" );
#endif // FURROVINE_DEBUG
			return resourceholder->resource;
		}

		template <typename T> 
		T& At ( ulword index ) {
			ResourceHolder<T>* resourceholder = null;
#ifdef FURROVINE_DEBUG
			furrovineassert( index < resources.size(), "Index outside the resources bounds" );
#endif // FURROVINE_DEBUG
			resourceholder = dynamic_cast<ResourceHolder<T>*>( resources[ index ].get() );
#ifdef FURROVINE_DEBUG
			furrovineassert( resourceholder != null, "Resource is not of the specified type T" );
#endif // FURROVINE_DEBUG
			return resourceholder->resource;
		}

		template <typename T>
		T& operator [] ( ulword index ) {
			return At( index );
		}

		template <typename T>
		T& operator [] ( const TKey& id ) {
			return Get( id );
		}

		bool Remove ( const TKey& id ) {
			auto index = resourceindices.find( id );
			if ( index == resourceindices.end() || index->second >= resources.size() )
				return false;
			
			resources[ index->second ].reset( null );
			return true;
		}
	};


int main (int, char*[] ) {
    RVector3<float> arf = { 1, 1, 1 };
    arf.x *= 2;
}