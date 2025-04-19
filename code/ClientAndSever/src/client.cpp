#include "client.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <boost/locale.hpp>

int Client_exe(const std::string &ip, const std::string &portNumber)
{
    using namespace boost::asio;

    ip::address_v4 ip_address =ip::make_address_v4(ip);
    auto port = std::stoul(portNumber);
    try
    {
        ip::tcp::endpoint ep(ip_address,port);
        io_context ios;
        ip::tcp::socket sock(ios,ep.protocol());
        std::cout<<"连接服务器\n";
        sock.connect(ep);
        sock.close();
        std::cout<<"断开连接服务器\n";
    }
    catch(boost::system::error_code& e)
    {
        std::cout<<"ErrorLog: " << e.what() << '\n';
        return e.value();
    }
    catch(boost::system::system_error& e)
    {
        std::cout<<"ErrorLog: " << e.what() << '\n';
        return e.code().value();
    }
    
    return 0;
}