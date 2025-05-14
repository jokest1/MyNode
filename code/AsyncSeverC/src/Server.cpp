/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-29 10:05:12
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-29 17:31:46
 * @FilePath: \code\AsyncSeverC\src\Server.cpp
 * @Description: 
 * 
 */
#include "Server.h"
#include "Session.h"

Server::Server(boost::asio::io_context& ioc,short port)
    :_ioc(ioc)
    ,_port(port)
    ,_accept(ioc,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))
{
    start_accept();
}
Server::~Server()
{

}
void Server::clear_session(const std::string& uuid)
{
    _sessions.erase(uuid);
}
void Server::handle_accept(std::shared_ptr<Session> new_session,const boost::system::error_code& ec)
{
    /*
    当accept触发的时候进入了回调函数，已经用socket与客户端建立了连接
        1.将事件开启
        2.将连接放入容器中
    */
   if (!ec.value())
   {
    new_session->start();
    _sessions.insert(std::make_pair<>(new_session->uuid(),new_session));
   }else
   {
    std::cout<<"accept error code: "<<ec.value();
   }
   start_accept();
   
}
void Server::start_accept()
{
    /*
    开始进行监听：
        1.创建一个接受请求连接session
        2.绑定接受连接的回调函数
    */
   auto new_session = std::make_shared<Session>(_ioc,this);
   _accept.async_accept(
        new_session->Socket()
        ,
        std::bind(&Server::handle_accept,this,new_session,std::placeholders::_1)
    );
}