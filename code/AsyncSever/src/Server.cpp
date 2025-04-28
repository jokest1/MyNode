#include <iostream>
#include "Server.h"
#include "Session.h"

Server::Server(boost::asio::io_context &ioc, short port)
    :_ioc(ioc)
    ,_acceptor(ioc,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))

{
    start_accept();
}

Server::~Server()
{
}

void Server::start_accept()
{
    auto session = new Session(_ioc);
    _acceptor.async_accept(session->Socket(),std::bind(&Server::handle_accept,this,session,std::placeholders::_1));
}

void Server::handle_accept(Session* new_session,const boost::system::error_code& ec)
{
    if (!ec)
    {
        new_session->Start();
    }else
    {
        std::cout<<"error code:"<<ec.value()<<"\n";
        delete new_session;
    }
    start_accept();
}
