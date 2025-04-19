#pragma one
/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-19 19:14:06
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-19 20:02:20
 * @FilePath: \code\ClientAndSever\include\log.h
 * @Description: 
 * 
 */
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "client.h"
#include "sever.h"


 namespace test
 {
std::string GetPortNumber()
{
    std::string portNumber;
    std::cout<<"请输入监听的端口:";
    while (true)
    {
        std::getline(std::cin,portNumber);
        size_t pos = 0;
        auto value = std::stoul(portNumber,&pos);
        if(
            pos!=portNumber.size()
            ||
            value > std::numeric_limits<uint32_t>::max()
        )
        {
            std::cout<<"请输入正确的端口:";
            continue;
        }
        break;
    }
    return portNumber;
}
std::string GetIpArr()
{
    std::string ipAddr;
    std::cout<<"请输入Ipv4的地址:";
    while (true)
    {
        std::getline(std::cin,ipAddr);
        try {
            boost::asio::ip::make_address_v4(ipAddr);
            return ipAddr;
        } catch (const boost::system::system_error&) {
            std::cout<<"请输入一个合法的ipv4地址\n"<<std::endl;
            continue;
        }
    }
    
}
 void TestExe(int argc ,const char* argv[])
 {
    if (argc == 1)
    {
        //TODO:自己选择运行模式
        std::string model;
        std::string portNumber;
        std::string ipArr;

        std::cout<<"请选择要运行的模式(0:服务器/1:客户端):";
        while (true)
        {
            std::getline(std::cin,model);
            if (
                model == "0"
                ||
                model == "1"
            )
            {
                break;
            }
            else
            {
                std::cout<<"选择错误,请选择要运行的模式(0:服务器/1:客户端):";
            }
        }
        //判断是服务器还是客户端
        if (model == "0")
        {
            portNumber = GetPortNumber();
            Sever_exe(portNumber);
        }
        else if (model == "1")
        {
            ipArr = GetIpArr();
            portNumber = GetPortNumber();
            Client_exe(ipArr,portNumber);
        }
    }
    else
    {
        //TODO:提示命令行内容和对应的信息
        std::cout<<"args Error\n"<<std::endl;
        std::string end;
        std::cout<<"\"Enter\" End Windows.."<<std::endl;
        std::getline(std::cin,end);
    }
 }


 } // namespace test
 
