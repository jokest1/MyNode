#include "Client.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <boost/locale.hpp>

#include "ReadWrite.h"

void Client_Exe(const std::string &ip, const std::string &port)
{
    using namespace boost::asio;
    ip::address_v4 ip_address =ip::make_address_v4(ip);
    auto portNumber = std::stoul(port);
    try
    {
        ip::tcp::endpoint ep(ip_address,portNumber);
        io_context ios;
        ip::tcp::socket sock(ios,ep.protocol());
        std::cout<<"连接服务器\n";
        sock.connect(ep);
        std::string data;
        std::cout<<"请输入发送的数据(q退出):";
        while (true)
        {
            std::getline(std::cin,data);
            if(data =="q")
            {
                sock.close();
                std::cout<<"断开连接服务器\n";
                break;
            }
            else
            {
                test_tool::WriteDataToSocket(data,sock);
                data = test_tool::ReadDataForSocker(sock);
                std::cout<<data<<"\n";
            }
        }        
    }
    catch(const boost::system::error_code& e)
    {
        std::cout << e.what() << '\n';
        
    }
}
