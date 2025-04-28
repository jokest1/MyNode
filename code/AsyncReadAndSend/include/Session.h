/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 22:08:39
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-28 13:56:12
 * @FilePath: \code\AsyncReadAndSend\include\Session.h
 * @Description: 
 * 
 */
#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <string>
#include <queue>
#include <iostream>
class MsgNode;

class Session
{
public:
    Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    ~Session();
    void Connect(const boost::asio::ip::tcp::endpoint& ep);
    //不是线程安全并且保证发送顺序
    void WriteCallBackErr(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<MsgNode> data);
    void WriteToSocketErr(const std::string& buf);
    //线程安全并且保证发送顺序
    void WriteCallBack(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<MsgNode> data);
    void WriteToSocket(const std::string& buf);
    void WriteAllCallBack(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<MsgNode> data);
    void WriteAllToSocked(const std::string& buf);
    void ReadCallBack(const boost::system::error_code& ec,std::size_t bytes_transferred);
    void ReadToSocket();
    void ReadAllCallBack(const boost::system::error_code& ec,std::size_t bytes_transferred);
    void ReadAllToSocket();
private:
    std::shared_ptr<MsgNode> _node;
    std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
    std::queue<std::shared_ptr<MsgNode>> _send_queue;
    bool _send_panding;
    bool _read_panding;
    std::shared_ptr<MsgNode> _read_node;
};
