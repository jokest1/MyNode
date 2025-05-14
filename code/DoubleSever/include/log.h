#pragma once
/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-03 14:09:18
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 11:48:59
 * @FilePath: \code\DoubleSever\include\log.h
 * @Description: 
 * 
 */
#include "MsgNode.h"
#include "Server.h"
namespace test
{
void TestExe(int argc ,const char* argv[])
{
    try
    {
        boost::asio::io_context ioc;
        Server s(ioc,10086);
        ioc.run();
    }
    catch(const boost::system::error_code& e)
    {
        std::cout << e.what() << '\n';
    }
    
}
} // namespace test
