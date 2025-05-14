#include "Server.h"
#include "Session.h"
Server::Server(boost::asio::io_context& ioc,short port)
    :_ioc(ioc)
    ,_port(port)
    ,_accept(
        ioc,
        boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::any(),
            _port
        )
    )
{
    _start_accept();
}
Server::~Server()
{

}
void Server::clear_session(const std::string& uuid)
{
    auto session = _map_session.find(uuid);
    if (session!=_map_session.end())
    {
        _map_session.erase(uuid);
    }
}
void Server::_start_accept()
{
    auto socket = std::make_shared<Session>(_ioc,this);
    _accept.async_accept(socket->Socket(),std::bind(&Server::handel_accept,this,std::placeholders::_1,socket));
}
void Server::handel_accept(const boost::system::error_code& ec,std::shared_ptr<Session> session) 
{
    if (!ec)
    {
        session->start();
        _map_session.insert(std::make_pair<>(session->get_uuid(),session));
    }else
    {
        std::cout<<"connet fail error code:"<<ec.value();
    }
    _start_accept();
}