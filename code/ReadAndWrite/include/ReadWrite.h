/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 13:42:44
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-27 14:13:37
 * @FilePath: \code\ReadAndWrite\include\ReadWrite.h
 * @Description: 
 * 
 */
#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

namespace test_tool
{
extern std::string ReadDataForSocker(boost::asio::ip::tcp::socket& s);
extern bool WriteDataToSocket(const std::string& data,boost::asio::ip::tcp::socket& s);
} // namespace test_tool
