#include "Session.h"
#include <iostream>

Session::Session(boost::asio::io_context &ioc)
    :_socket(ioc)
{
}
Session::~Session()
{

}
boost::asio::ip::tcp::socket &Session::Socket()
{
    return this->_socket;
}

void Session::Start()
{
    memset(_data,0,sizeof(char)*max_length);
    _socket.async_read_some(
        boost::asio::buffer(_data,max_length),
        std::bind(&Session::handle_read,this,std::placeholders::_1,std::placeholders::_2)
    );
}

void Session::handle_read(const boost::system::error_code &ec, std::size_t bytes_transfered)
{
    if (!ec)
    {
        std::cout<<"sever receive data is: "<<_data<<"\n"<<std::endl;
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(_data,bytes_transfered),
            std::bind(&Session::handle_write,this,std::placeholders::_1)
        );
    }else
    {
        std::cout<<"error code is: "<<ec.value()<<"\n"<<std::endl;
        delete this;
    }
    
}

void Session::handle_write(const boost::system::error_code &ec)
{
    if (!ec)
    {
        memset(_data,0,max_length*sizeof(char));
        _socket.async_read_some(boost::asio::buffer(_data,max_length),
            std::bind(&Session::handle_read,this,std::placeholders::_1,std::placeholders::_2)
        );
    }else
    {
        std::cout<<"error code is: "<<ec.value()<<"\n"<<std::endl;
        delete this;
    }
}
