#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

const/*expr*/ int TRANS_TUPLE_SIZE  = 15;
const/*expr*/ int TRANS_BUFFER_SIZE = 5120 / TRANS_TUPLE_SIZE * TRANS_TUPLE_SIZE;

namespace AsioTrans
{
    typedef boost::asio::io_service      service_t;
    typedef boost::asio::ip::tcp::socket socket_t;
    typedef boost::ptr_vector<socket_t>  socket_list;

    using boost::system::error_code;
    using namespace boost::asio;

    class Broadcaster
    {
    private:
        boost::array<char, TRANS_BUFFER_SIZE> trans_buffer;

        int node_id;
        int mpi_rank;

        socket_t&    dbsocket;
        socket_list& sender_sockets;

        int n_send;
        boost::mutex mutex;
        bool done;
    public:
        Broadcaster(
            socket_t& dbskt,
            socket_list& senderskts,
            int mrank,
            int id) : 
                node_id(id),
                mpi_rank(mrank),
                dbsocket(dbskt),
                sender_sockets(senderskts),
                n_send(-1),
                done(false)
        {
            // count=0;
        }

        static size_t completion_condition(const error_code& error, size_t bytes_transferred)
        {
            // TODO FIXME handler error_code here
            int remain = bytes_transferred % TRANS_TUPLE_SIZE;

            if(bytes_transferred && !remain)
            {
                return 0;
            }
            else
            {
                return TRANS_BUFFER_SIZE - bytes_transferred;
            }
        }

        void write_handler(const error_code &ec, size_t bytes_transferred)
        {
            // TODO handle errors
            // TODO check bytes_transferred
            boost::lock_guard<boost::mutex> lk(mutex);

            if(!(done || --n_send))
                broadcast();
        }

        void broadcast_handler(const error_code &ec, size_t bytes_transferred)
        {
            fprintf(stdout, "@%d, broadcast_handler: %lu bytes, mpi_size:%lu, mpi_rank: %d\n", node_id, bytes_transferred, sender_sockets.size(), mpi_rank);

            if(!ec)
            {
                for(size_t pos = 0; (pos < bytes_transferred && pos < TRANS_BUFFER_SIZE); pos += TRANS_TUPLE_SIZE)
                {
                    int id = -1;
                    memcpy(&id, &trans_buffer[pos], sizeof(id));

                    if(id < 0)
                    {
                        done = true;
                        fprintf(stdout, "@%d, broadcast_handler: done!\n", mpi_rank);
                        break;
                    }
                }

                {
                    boost::lock_guard<boost::mutex> lk(mutex);
                    n_send = sender_sockets.size() - 1;
                }

                for(int i = 0; size_t(i) < sender_sockets.size(); i++)
                {
                    if(i != mpi_rank)
                    {
                        async_write(
                                sender_sockets[i], 
                                buffer(trans_buffer, bytes_transferred),
                                boost::bind(&Broadcaster::write_handler, this, placeholders::error, placeholders::bytes_transferred));
                    }
                }
            }
            else
            {
                std::cerr << mpi_rank << " error: " << ec.message() << std::endl;
                delete this;
            }
        }

        void broadcast()
        {
            async_read(
                    dbsocket,
                    buffer(trans_buffer),
                    Broadcaster::completion_condition, 
                    boost::bind(&Broadcaster::broadcast_handler, this,
                        placeholders::error,
                        placeholders::bytes_transferred));
        }
    };

    struct service_wrap {
        service_wrap(int threads) {
            while(threads--)
                _pool.create_thread(boost::bind(&service_t::run, boost::ref(_service)));
        }

        ~service_wrap() {
            _service.post(boost::bind(&service_wrap::stop, this));
            _pool.join_all();
        }

        service_t& service() { return _service; }

    private: // mind the initialization order!
        service_t                        _service;
        boost::optional<service_t::work> _work;
        boost::thread_group              _pool;

        void stop() { 
            _work = boost::none;
        }
    };

    extern void AsioConnectToRemote(int, int, service_t&, socket_t&, bool);
    extern void SetupAsioConnectionsWIthOthers(service_t&, socket_list&, std::string, int, bool);
}

int main()
{
    using namespace AsioTrans;

    // there's no use in increasing #threads unless there are blocking operations
    service_wrap senders(boost::thread::hardware_concurrency()); 
    service_wrap receivers(1);

    socket_t receiver_socket(receivers.service());
    AsioConnectToRemote(5000, 1, receivers.service(), receiver_socket, true);

    socket_list send_sockets(30);
    /*hadoopNodes =*/ SetupAsioConnectionsWIthOthers(senders.service(), send_sockets, "hostFileName", 3000, false);

    int mpi_rank = send_sockets.size();
    AsioTrans::Broadcaster db_receiver(receiver_socket, send_sockets, mpi_rank, mpi_rank);
    db_receiver.broadcast();
}
