#include <boost/asio.hpp>

class Session
{
public:
    Session(boost::asio::io_context& ioc);
    ~Session();
    boost::asio::ip::tcp::socket& Socket();
    void Start();
private:
    void handle_read(const boost::system::error_code& ec,std::size_t bytes_transfered);
    void handle_write(const boost::system::error_code& ec);
    boost::asio::ip::tcp::socket _socket;
    enum{max_length = 1024};
    char _data[max_length];
};
