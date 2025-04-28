/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 10:07:23
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-27 19:48:33
 * @FilePath: \code\ReadAndWrite\src\Sever.cpp
 * @Description: 
 * 
 */
#include "Sever.h"
#include <iostream>
#include <boost/system.hpp>
#include <memory>
#include <thread>
#include <set>
#include "ReadWrite.h"

#define MAX_LENGTH 1024

using socket_node = std::shared_ptr<boost::asio::ip::tcp::socket>;
std::set<std::shared_ptr< std::thread>> set_sockets;

void session(socket_node sock)
{
    try
    {
        while (true)
        {
            char data[MAX_LENGTH];
            memset(data,0,sizeof(char)*MAX_LENGTH);
            boost::system::error_code ec;
            size_t data_length = sock->read_some(boost::asio::buffer(data,MAX_LENGTH),ec);
            if(ec == boost::asio::error::eof)
            {
                std::cout<<"connect end\n";
                break;
            }
            else if(ec)
            {
                throw boost::system::system_error(ec);
            }
            std::cout<<"data size:"<<data_length<<"\n";
            std::cout<<"receive form:"<<sock->remote_endpoint().address().to_string()<<"\n";
            std::cout<<"receive data:"<<data;
            boost::asio::write(*sock,boost::asio::buffer(data,data_length));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Sever_Exe(const std::string &portNumber)
{
    using namespace boost::asio;
    auto localIp = ip::address_v4::any();
    auto port = std::stoul(portNumber);
    try
    {
        ip::tcp::endpoint ep(localIp,port);
        io_context ios;
        ip::tcp::acceptor accept(ios,ep.protocol());
        boost::system::error_code ec;
        accept.bind(ep,ec);
        accept.listen();
        while (true)
        {
            socket_node sock(new boost::asio::ip::tcp::socket(ios));
            accept.accept(*sock);
            auto t = std::make_shared<std::thread>(session,sock);
            set_sockets.insert(t);
        }
    }
    catch(boost::system::error_code& e)
    {
        std::cout<<"ErrorLog: " << e.what() << '\n';
    }
}