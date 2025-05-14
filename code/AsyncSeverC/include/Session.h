#pragma once
#include <boost/asio.hpp>
#include <boost/uuid.hpp>
#include <memory>
#include <string>
#include <queue>
#include <iostream>

class Server;
class MsgNode;
class Session :public std::enable_shared_from_this<Session>
{

public:
    Session(boost::asio::io_context& ioc,Server* p);
    ~Session();
    boost::asio::ip::tcp::socket& Socket();
    void start();
    void send(const std::string& buf);
    const std::string& uuid()const;
private:
    void handle_read(const boost::system::error_code& ec,std::size_t bytes_transfered);
    void handle_write(const boost::system::error_code& ec);
    Server* _parent;
    boost::asio::ip::tcp::socket _socket;
    std::string _uuid;
    std::queue<std::shared_ptr<MsgNode>> _send_node;
    std::shared_ptr<MsgNode> _read_node;
    std::mutex _send_lock;
};


