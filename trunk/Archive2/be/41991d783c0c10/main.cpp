#include <boost/asio.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace boost;
using namespace boost::asio;

namespace /*convenience*/ {
    static mutex console_mx;

#define TRACEME(detail) do { lock_guard<mutex> lk(console_mx); std::cout << __FUNCTION__ << " " << detail << "\n"; } while(0)

    struct id_generator {
        protected:
            id_generator() = default;

            static int generate_id() {
                static int id = 0;
                return ++id;
            }
    };
}

namespace database
{
    // data types
    struct sql_statement { std::string dml; };
    struct sql_response { std::string echo_dml; }; // TODO cover response codes, resultset data etc.

    struct service
    {
        service(unsigned max_concurrent_requests = 10)
            : work(io_service::work(service_)),
              latency(mt19937(), uniform_int<int>(200, 1500)) // 0.2 ~ 1.5s
        {
            for (unsigned i = 0; i < max_concurrent_requests; ++i)
                svc_threads.create_thread(boost::bind(&io_service::run, &service_));
        }

        friend struct connection;

      private:
        void async_query(io_service& external, sql_statement query, boost::function<void(sql_response response)> completion_handler)
        {
            service_.post(bind(&service::do_async_query, this, ref(external), std::move(query), completion_handler));
        }
        
        void do_async_query(io_service& external, sql_statement q, boost::function<void(sql_response response)> completion_handler)
        {
            this_thread::sleep_for(chrono::milliseconds(latency())); // simulate the latency of a db-roundtrip

            external.post(bind(completion_handler, sql_response { q.dml }));
        }

        io_service service_;
        thread_group svc_threads; // note the order of declaration
        optional<io_service::work> work;

        // for random delay
        boost::random::variate_generator<mt19937, uniform_int<int> > latency;
    };

    struct connection // really, only a "facade" for this toy demo
    {
        connection(int connection_id, io_service& external, service& svc)
            : connection_id(connection_id),
              external_(external), 
              db_service_(svc)
        { }

        void async_query(sql_statement query, boost::function<void(sql_response response)> completion_handler)
        {
            TRACEME("id:" << connection_id << " dml:'" << query.dml << "'");
            db_service_.async_query(external_, std::move(query), completion_handler);
        }
      private:
        int connection_id;
        io_service& external_;
        service& db_service_;
    };
}

namespace domain
{
    struct business_process : id_generator
    {
        business_process(io_service& app_service, database::service& db_service_) 
            : id(generate_id()), phase(0), 
              in_progress(io_service::work(app_service)),
              db(id, app_service, db_service_)
        { 
            app_service.post([=] { start_select(); });
        }

      private:
        int id, phase;
        optional<io_service::work> in_progress;

        database::connection db;

        void start_select() {
            db.async_query({ "select * from tasks where completed = false" }, [=] (database::sql_response r) { handle_db_response(r); });
        }

        void handle_db_response(database::sql_response r) {
            if (phase++ < 4)
            {
                if ((id + phase) % 3 == 0) // vary the behaviour slightly
                {
                    db.async_query({ "insert into tasks (text, completed) values ('hello', false)" }, [=] (database::sql_response r) { handle_db_response(r); });
                } else
                {
                    db.async_query({ "update * tasks set text = 'update' where id = 123" }, [=] (database::sql_response r) { handle_db_response(r); });
                }
            } else
            {
                in_progress.reset();
                lock_guard<mutex> lk(console_mx);
                std::cout << "business_process " << id << " has completed its work\n";
            }
        }
    };

}

int main()
{
    io_service app;
    database::service db;

    ptr_vector<domain::business_process> bps;
    for (int i = 0; i < 10; ++i)
    {
        bps.push_back(new domain::business_process(app, db));
    }

#if defined(MULTITHREAD_BUSINESS_PROCESSES)
    thread_group g;
    for (unsigned i = 0; i < thread::hardware_concurrency(); ++i)
        g.create_thread(boost::bind(&io_service::run, &app));
    g.join_all();
#else
    app.run();
#endif
}
