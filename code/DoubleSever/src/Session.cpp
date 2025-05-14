/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-03 14:31:08
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 13:41:16
 * @FilePath: \code\DoubleSever\src\Session.cpp
 * @Description: 
 * 
 */
#include "Session.h"
#include "MsgNode.h"
#include "Server.h"

Session::Session(boost::asio::io_context& ioc,Server* p)
    :_socket(ioc)
    ,_parent(p)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    _uuid = boost::uuids::to_string(uuid);
    _read_data = std::make_shared<MsgNode>(MAX_READ_DATA_LENGTH);
}
Session::~Session()
{

}
void Session::start()
{
    std::cout<<"start session "<<_uuid<<"\n";
    _read_data->clear();
    _socket.async_read_some(
        boost::asio::buffer(
            _read_data->get_msg()
            ,_read_data->get_total_length()
        )
        ,
        std::bind(
            &Session::handle_read,shared_from_this()
            ,std::placeholders::_1
            ,std::placeholders::_2
        )
    );
}
const std::string& Session::get_uuid()const
{
    return _uuid;
}
boost::asio::ip::tcp::socket& Session::Socket()
{
    return _socket;
}
void Session::send(const std::string& data)
{
    send(data.c_str(),data.size());
}
void Session::send(const char* data,std::size_t length)
{
    {
        std::lock_guard<std::mutex> mutex(_mutex);
        auto cache_send_data = std::make_shared<MsgNode>(data,length);
        _data_que.emplace(cache_send_data);
    }
    if (_data_que.size() == 1)
    {
        _start_send_que_data();
    }
}
void Session::handle_read(const boost::system::error_code& ec,std::size_t bytes_transfered)
{
    if (!ec)
    {
        std::cout<<"read data:"<<_read_data->get_msg()<<"\n";
        send(_read_data->get_msg(),_read_data->get_total_length());
        _read_data->clear();
        _socket.async_read_some(
            boost::asio::buffer(_read_data->get_msg(),_read_data->get_total_length())
            ,
            std::bind(&Session::handle_read,shared_from_this(),std::placeholders::_1,std::placeholders::_2)
        );
    }
    else
    {
        std::cout<<"read error code : "<<ec.value();
        _parent->clear_session(_uuid);
    }
}
void Session::handle_write(const boost::system::error_code& ec)
{
    if (!ec)
    {
        if (!_data_que.empty())
        {
            _start_send_que_data();
        }else
        {
            std::cout <<"send queue is empty \n";
        }
    }
    else
    {
        std::cout<<"write error code : "<<ec.value();
        _parent->clear_session(_uuid);
    }
    
}

void Session::_start_send_que_data()
{
    std::lock_guard<std::mutex> mutex(_mutex);
    auto data = _data_que.front();
    std::cout <<"send data:"<<data->get_msg()<<"\n";
    _socket.async_send(
        boost::asio::buffer(data->get_offset_data(),data->get_offset_length())
        ,
        std::bind(&Session::handle_write,this,std::placeholders::_1)
    );
    _data_que.pop();
}