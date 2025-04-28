/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 09:46:34
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-27 14:42:25
 * @FilePath: \code\ReadAndWrite\include\log.h
 * @Description: 
 *      在服务器和客户端整体连接的过程上添加数据的读取和发送
 */

#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include "ReadWrite.h"

#include "Client.h"
#include "Sever.h"

namespace test
{
std::string GetPorNumber()
{
    std::string port;
    while (true)
    {
        std::cout<<"请输入端口号:";
        std::getline(std::cin,port);
        size_t pos = 0;
        auto value = std::stol(port,&pos);
        if (
            pos!=port.size()
            ||
            value>std::numeric_limits<uint32_t>::max()
        )
        {
            std::cout<<"输入错误\n";
            continue;
        }
        break;
    }
    return port;
}
std::string GetIpArr()
{
    std::string ipArr;
    while (true)
    {
        std::cout<<"请输入ip地址:";
        std::getline(std::cin,ipArr);
        try
        {
            auto arr = boost::asio::ip::make_address_v4(ipArr);
            if(!arr.is_unspecified())
            {
                break;
            }else
            {
                std::cout<<"请输入一个合法的ipv4地址\n";
                continue;
            }
        }
        catch(const boost::system::system_error& e)
        {
            std::cout<<"请输入一个合法的ipv4地址\n";
            continue;
        }
    }
    return ipArr;
}
int TestExe(int argc, const char* argv[])
{
    if (argc == 1)
    {
        std::string model;
        std::string portNumber;
        std::string ipArr;
        std::cout<<"请选择要运行的模式(0:服务器/1:客户端):";
        while (true)
        {
            std::getline(std::cin,model);
            if (
                model == "1" 
                || 
                model == "0"
            )
            {
                break;
            }
            std::cout<<"输入错误，选择要运行的模式(0:服务器/1:客户端):";
        }
        if (model == "0")
        {
            portNumber = GetPorNumber();
            Sever_Exe(portNumber);
        }
        else if (model == "1")
        {
            ipArr = GetIpArr();
            portNumber = GetPorNumber();
            Client_Exe(ipArr,portNumber);
        }
        else{
            throw "error input\n";
        }
        
        
    }
    else
    {

    }
    return 0;
}
} // namespace test
