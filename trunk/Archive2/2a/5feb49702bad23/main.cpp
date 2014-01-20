#include <string>
#include <list>
#include <map>
#include <memory>
#include <ctime>

namespace jobserver
{
    class QueueItem;
    typedef std::shared_ptr<QueueItem> QueueItemPtr;
    typedef std::list<QueueItemPtr> QueueItemPtrs;

    typedef uint64_t ItemId;
    typedef int32_t  Priority;
    typedef uint64_t AgeSeconds;

    typedef std::multimap< Priority, ItemId >  ItemPriorityMap;
    typedef std::map<std::string, std::string> UriNameValueMap;

    class QueueItem
    {
    public:
        QueueItem( const ItemId&        id,
                   const std::string&   body,
                   const Priority&      priority,
                   const std::time_t&   insertTime,
                   const std::time_t&   scheduledTime,
                   const std::time_t&   expiryTime )
        :   m_id( id ),
            m_body( body ),
            m_priority( priority ),
            m_insertTime( insertTime ),
            m_scheduledTime( scheduledTime ),
            m_inProgressTime( 0 ),
            m_expiryTime( expiryTime ),
            m_requeueCount( 0 ),
            m_uriMap( ),
            m_backoffSeconds( 0 )
        {
        }
        
        QueueItem( QueueItem&& rvalue )
        :   m_id( rvalue.m_id ),
            m_body( rvalue.m_body ),
            m_priority( rvalue.m_priority ),
            m_insertTime( rvalue.m_insertTime ),
            m_scheduledTime( rvalue.m_scheduledTime ),
            m_inProgressTime( rvalue.m_inProgressTime ),
            m_expiryTime( rvalue.m_expiryTime ),
            m_requeueCount( rvalue.m_requeueCount ),
            m_uriMap( rvalue.m_uriMap ),
            m_backoffSeconds( rvalue.m_backoffSeconds )
        {
        }
                   
        QueueItem( const QueueItem& ) = delete;
        QueueItem& operator=( const QueueItem& ) = delete;

        ItemId GetId( )                  const { return m_id;             }
        const std::string& GetBody( )    const { return m_body;           }
        Priority GetPriority( )          const { return m_priority;       }
        std::time_t GetInsertTime( )     const { return m_insertTime;     }
        std::time_t GetScheduledTime( )  const { return m_scheduledTime;  }
        std::time_t GetInProgressTime( ) const { return m_inProgressTime; }
        std::time_t GetExpiryTime( )     const { return m_expiryTime;     }
        uint32_t GetRequeueCount( )      const { return m_requeueCount;   }
        uint32_t GetBackoffSeconds( )    const { return m_backoffSeconds; }

        void SetBody( const std::string& body )                    { m_body = body;                     }
        void SetPriority( const Priority&  priority )              { m_priority = priority;             }
        void SetScheduledTime( const std::time_t& scheduledTime )   { m_scheduledTime = scheduledTime;   }
        void SetInProgressTime( const std::time_t& inProgressTime ) { m_inProgressTime = inProgressTime; }
        void SetExpiryTime( const std::time_t& expiryTime )         { m_expiryTime = expiryTime;         }
        void SetBackoffSeconds( const uint32_t backoffSeconds )    { m_backoffSeconds = backoffSeconds; }

        void IncrementRequeueCount( ) { ++m_requeueCount; }

        ItemId            m_id;
        std::string       m_body;
        Priority          m_priority;
        std::time_t       m_insertTime;
        std::time_t       m_scheduledTime;
        std::time_t       m_inProgressTime;
        std::time_t       m_expiryTime;
        uint32_t          m_requeueCount;
        UriNameValueMap   m_uriMap;
        uint32_t          m_backoffSeconds;
    };
} // end namespace


jobserver::QueueItem CreateQueueItem( )
{
    return jobserver::QueueItem( 1, "body", 0, 0, 0, 0 );
}

int main()
{
    auto queueItem( CreateQueueItem( ) );
}
