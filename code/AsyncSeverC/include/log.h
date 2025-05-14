/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-29 10:04:26
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-29 17:34:34
 * @FilePath: \code\AsyncSeverC\include\log.h
 * @Description: 
 * 
 */
#pragma once

#include <iostream>
#include "Server.h"
#include "Session.h"

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
        std::cerr << e.what() << '\n';
    }
    
}
} // namespace test
