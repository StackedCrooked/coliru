    #include <string>
    #include <vector>
    #include <unordered_map>
    
    typedef std::size_t ulword;
    
    template <typename key_type = std::string>
    class ResourceCache {
	public:
		typedef key_type TKey;

	private:
		struct ResourceBase { 

			virtual ~ResourceBase() {

			}

		};

		template < typename T, typename TDx = std::default_delete<T> > 
		struct ResourceHolder : public ResourceBase {
			ptr<T, TDx> resource;

			ResourceHolder( ) : resource( null ) {

			}

			ResourceHolder( T resource ) : resource( std::move( resource ) ) {

			}

			ResourceHolder( T&& res ) : resource( std::move( res ) ) {

			}

			ResourceHolder( T* res ) : resource( res ) {

			}

			ResourceHolder( T* res, TDx deleter ) : resource( res, deleter ) {

			}

			ResourceHolder( T* res, TDx&& deleter ) : resource( res, deleter ) {

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
			if ( value == null )
				return;

			auto index = resourceindices.find( key );
			if ( index != resourceindices.end() )
				throw Exception( String::Format( "Key \"{0}\" already exists in the cache", key ) );

			resourceindices.insert( std::make_pair( key, resources.size() ) );
			resources.emplace_back( new ResourceHolder<T>( value ) );
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
			if ( index != resourceindices.end() )
				return false;

			resourceindices.insert( std::make_pair( key, resources.size() ) );
			resources.emplace_back( new ResourceHolder<T>( value ) );

			return true;
		}

		template <typename T> 
		bool TryGet ( const TKey& id, T*& resource ) {
			auto index = resourceindices.find( id );
			if ( index != resourceindices.end() ) {
				ResourceHolder<T>* cacheholder = dynamic_cast<ResourceHolder<T>*>( resources[ index->second ].get() );
				if ( cacheholder != null ) {
					resource = &(cacheholder->resource);
					return true;
				}
			}
			return false;
		}

		template <typename T> 
		T* TryGet ( const TKey& id ) {
			T* res = null;
			TryGet( id, res );
			return res;
		}

		template <typename T> 
		T& Get ( const TKey& id ) {
			ResourceBase* base = null;
			ResourceHolder<T>* resourceholder = null;
			auto index = resourceindices.find( id );
#ifdef FURROVINE_DEBUG
			furrovineassert( index != resourceindices.end() && index->second < resources.size(), "Resource with specific id does not exist" );
#endif // FURROVINE_DEBUG
			base = resources[ index->second ].get();
#ifdef FURROVINE_DEBUG
			furrovineassert( base != null, "Resource for id is null" );
#endif // FURROVINE_DEBUG
			resourceholder = dynamic_cast<ResourceHolder<T>*>( base );
#ifdef FURROVINE_DEBUG
			furrovineassert( resourceholder != null, "Resource is not of the specified type T" );
#endif // FURROVINE_DEBUG
			return *(resourceholder->resource);
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
			return *(resourceholder->resource);
		}

		template <typename T>
		T& operator [] ( ulword index ) {
			return At<T>( index );
		}

		template <typename T>
		T& operator [] ( const TKey& id ) {
			return Get<T>( id );
		}

		bool Remove ( const TKey& id ) {
			auto index = resourceindices.find( id );
			if ( index == resourceindices.end() || index->second >= resources.size() )
				return false;

			resourceindices.erase( index );
			resources[ index->second ].reset( null );
			return true;
		}

		template <typename T>
		bool Replace ( const TKey& key, std::unique_ptr<T> value ) {
			return Replace( key, value.release() );
		}

		template <typename T>
		bool Replace ( const TKey& key, ptr<T> value ) {
			return Replace( key, value.release() );
		}

		template <typename T>
		bool Replace ( const TKey& key, T* value ) {
			ResourceHolder<T>* resourceholder = null;
			if ( value == null )
				return false;

			auto index = resourceindices.find( key );
			if ( index != resourceindices.end() ) {
				ptr<ResourceBase>& resourcebase = resources[ index->second ];
				resourceholder = dynamic_cast<ResourceHolder<T>*>( resourcebase.get() );
				if ( resourceholder == null || resourceholder->resource == null ) {
					resourcebase.reset( new ResourceHolder<T>( value ) );
				}
				else {
					*(resourceholder->resource) = std::move( *value );
				}
				return true;
			}
			else {
				resourceindices.insert( std::make_pair( key, resources.size() ) );
				resources.emplace_back( new ResourceHolder<T>( value ) );
				return false;
			}
		}
	};

int main (int, char*[] ) {
 
}