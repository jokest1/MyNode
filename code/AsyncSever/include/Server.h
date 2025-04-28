/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-28 20:36:51
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-28 20:39:52
 * @FilePath: \code\AsyncSever\include\Server.h
 * @Description: 
 * 
 */

#include <boost/asio.hpp>

class Session;

class Server
{
public:
    Server(boost::asio::io_context& ioc,short port);
    ~Server();
private:
    void start_accept();
    void handle_accept(Session* new_session,const boost::system::error_code& ec);
    boost::asio::io_context& _ioc;
    boost::asio::ip::tcp::acceptor _acceptor;
};

