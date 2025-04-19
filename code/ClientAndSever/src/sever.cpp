#include "sever.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/system.hpp>

int Sever_exe(const std::string &portNumber)
{
    using namespace boost::asio;
    //TODO:创建客户端监听
    ip::address_v4 ip_address = ip::address_v4::any();
    auto port = std::stoul(portNumber);

    ip::tcp::endpoint ep(ip_address,port);
    io_context ios;
    try
    {
        ip::tcp::acceptor accept(ios,ep.protocol());
        boost::system::error_code ec;
        accept.bind(ep,ec);
        accept.listen();
        while (true)
        {
            ip::tcp::socket sock(ios);
            accept.accept(sock);
            std::cout
                <<"对方的ip地址:"
                <<sock.remote_endpoint().address().to_string()
                <<"\n"
                ;
        }
    }
    catch(boost::system::error_code& e)
    {
        std::cout<<"ErrorLog: " << e.what() << '\n';
        return e.value();
    }
    return 0;
}