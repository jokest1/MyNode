#pragma once
/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-04 11:26:53
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 11:45:54
 * @FilePath: \code\DoubleSever\include\Server.h
 * @Description: 
 * 
 */
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <map>

class Session;

class Server
{
public:
    Server(boost::asio::io_context& ioc,short port);
    ~Server();
    void clear_session(const std::string& uuid);
private:
    void _start_accept();
    void handel_accept(const boost::system::error_code& ec,std::shared_ptr<Session> session) ;

    boost::asio::io_context& _ioc;
    short _port;
    boost::asio::ip::tcp::acceptor _accept;
    std::map<std::string ,std::shared_ptr<Session>>_map_session;
};

