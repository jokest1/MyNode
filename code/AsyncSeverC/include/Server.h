#include <boost/asio.hpp>
#include <map>
#include <string>
#include <memory>

class Session;
class Server
{
public:
    Server(boost::asio::io_context& ioc,short port);
    ~Server();
    void clear_session(const std::string& uuid);
private:
    void handle_accept(std::shared_ptr<Session> new_session,const boost::system::error_code& ec);
    void start_accept();
    boost::asio::io_context& _ioc;
    short _port;
    boost::asio::ip::tcp::acceptor _accept;
    std::map<std::string,std::shared_ptr<Session>> _sessions;
};
