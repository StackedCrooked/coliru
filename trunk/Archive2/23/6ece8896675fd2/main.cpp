#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/asio.hpp>

static std::string const server_ip = "10.0.0.4";
static std::string const client_ip = "10.0.0.5";
static int base_port = 2345;

using std::cout;
using std::endl;

struct Location {
    double rent[6];
    double cost[7];
    std::string name, group;
    std::string locationOfObjectFile;
    int locationNo;

    template <typename Ar> void serialize(Ar &ar, unsigned) {
        ar &rent;
        ar &cost;
        ar &name;
        ar &group;
        ar &locationOfObjectFile;
        ar &locationNo;
    }
};

struct Player {
    int currentPosition;
    double currentMoney;

    template <typename Ar> void serialize(Ar &ar, unsigned) {
        ar &currentPosition;
        ar &currentMoney;
    }
};

struct Monopoly {
    std::vector<Location> locations;
    std::vector<Player> players;
    std::string currency;

    template <typename Ar> void serialize(Ar &ar, unsigned) {
        ar &locations;
        ar &players;
        ar &currency;
    }
};

Location l1;
Player p1;
Monopoly game, game2;

void readData(uint16_t port) {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(
        io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4(), port));

    /* code */

    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);
    std::cout << "connection from " << socket.remote_endpoint() << std::endl;

    // read header
    size_t header;
    boost::asio::read(socket, boost::asio::buffer(&header, sizeof(header)));
    std::cout << "body is " << header << " bytes" << std::endl;

    // read body
    boost::asio::streambuf buf;
    const size_t rc = boost::asio::read(socket, buf.prepare(header));
    buf.commit(header);
    std::cout << "read " << rc << " bytes" << std::endl;

    // deserialize
    std::istream is(&buf);
    boost::archive::text_iarchive ar(is);
    ar &game2;

    cout << game2.locations[0].rent[1] << endl;
    cout << game2.players[0].currentPosition << "how cool is this?";
    socket.close();
}

void sendData() {
    for (int i = 0; i <= 1; i++) {
        boost::asio::streambuf buf;
        std::ostream os(&buf);
        boost::archive::text_oarchive ar(os);
        ar &game;

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket(io_service);
        short port = i + base_port;
        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(client_ip), port));

        const size_t header = buf.size();
        std::cout << "buffer size " << header << " bytes" << std::endl;

        // send header and buffer using scatter
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(&header, sizeof(header)));
        buffers.push_back(buf.data());
        const size_t rc = boost::asio::write(socket, buffers);
        std::cout << "wrote " << rc << " bytes" << std::endl;
        ;
        socket.close();
    }
}

int main(int argc, char **argv) {
    l1.name = "soemthig";
    l1.group = 2;
    p1.currentMoney = 300;
    p1.currentPosition = 422;
    for (int i = 0; i < 7; ++i) {
        l1.cost[i] = i;
        /* code */
    }
    for (int i = 0; i < 6; ++i) {
        l1.rent[i] = 2 * i;
        /* code */
    }
    l1.locationOfObjectFile = "ajhsdk/asdc.obj";
    l1.locationNo = 5;
    game.locations.push_back(l1);
    game.players.push_back(p1);
    game.currency = "dollar";
    cout << game.currency;
    if (atoi(argv[1]) ==
        1) // argv[0]=0 implies server, argv[0]==1 implies client while argv[1] specifies 1st or second client
    {
        cout << "reading data";

        if (atoi(argv[2]) == 0) {
            readData(base_port);
            /* code */
        } else {
            readData(1235);
        }

    } else {
        cout << "writing data";
        sendData();
    }
}
