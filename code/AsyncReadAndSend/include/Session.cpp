/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 22:17:13
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-28 15:24:22
 * @FilePath: \code\AsyncReadAndSend\include\Session.cpp
 * @Description: 
 * 
 */
#include "Session.h"
#include "MsgNode.h"

Session::Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    :_socket(socket)
    ,_send_panding(false)
    ,_read_panding(false)
{
}

Session::~Session()
{

}


void Session::Connect(const boost::asio::ip::tcp::endpoint &ep)
{
    _socket->connect(ep);
}

void Session::WriteCallBackErr(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<MsgNode> data)
{
    _node->append_data_offset(bytes_transferred);
    if (_node->get_cur_index()!=_node->get_total())
    {
        this->_socket->async_write_some(
            boost::asio::buffer(
                _node->get_msg()+_node->get_cur_index()
                ,_node->get_total()-_node->get_cur_index()
            )
            ,std::bind(
                &Session::WriteCallBackErr
                ,this
                ,std::placeholders::_1
                ,std::placeholders::_2
                ,this->_node
            )
        );
    }
    
}

void Session::WriteToSocketErr(const std::string &buf)
{
    this->_node = std::make_shared<MsgNode>(buf.c_str(),buf.length());
    this->_socket->async_write_some(
        boost::asio::buffer(
            _node->get_msg()
            ,_node->get_total()
        )
        ,std::bind(
            &Session::WriteCallBackErr
            ,this
            ,std::placeholders::_1
            ,std::placeholders::_2
            ,this->_node
        )
        );

}

void Session::WriteCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<MsgNode> data)
{
    if (ec.value()!=0)
    {
        std::cout<<"error code:"<<ec.value()<<"\n";
        return;
    }
    auto& send_data = _send_queue.front();
    send_data->append_data_offset(bytes_transferred);
    if (send_data->get_cur_index()!=send_data->get_total())
    {
        this->_socket->async_write_some(
            boost::asio::buffer(send_data->get_msg()+send_data->get_cur_index(),send_data->get_total()-send_data->get_cur_index())
            ,std::bind(&Session::WriteCallBack,this,std::placeholders::_1,std::placeholders::_2
            )
        );
        return;
    }
    _send_queue.pop();
    if (_send_queue.empty())
    {
        this->_send_panding = false;
    }else
    {
        auto& send_data = _send_queue.front();
        this->_socket->async_write_some(
            boost::asio::buffer(send_data->get_msg(),send_data->get_total())
            ,std::bind(&Session::WriteCallBack,this,std::placeholders::_1,std::placeholders::_2)
        );
    }
    
}

void Session::WriteToSocket(const std::string &buf)
{
    _send_queue.emplace(std::make_shared<MsgNode>(boost::asio::buffer(buf.c_str(),buf.length())));
    if (this->_send_panding)
    {
        return;
    }
    this->_socket->async_write_some(
        boost::asio::buffer(
            buf.c_str(),buf.length()
        )
        ,std::bind(
                &Session::WriteCallBack
                ,this
                ,std::placeholders::_1
                ,std::placeholders::_2
        )
    );
    this->_send_panding = true;
}

void Session::WriteAllCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<MsgNode> data)
{
    if (ec.value()!=0)
    {
        std::cout<<"error code:"<<ec.value()<<"\n";
        return;
    }
    _send_queue.pop();
    if (_send_queue.empty())
    {
        this->_send_panding = false;
    }else
    {
        auto& send_data = _send_queue.front();
        this->_socket->async_send(boost::asio::buffer(send_data->get_msg(),send_data->get_total())
            ,std::bind(&Session::WriteAllCallBack,this,std::placeholders::_1,std::placeholders::_2)
    );
    }
    
}

void Session::WriteAllToSocked(const std::string &buf)
{
    this->_send_queue.emplace(std::make_shared<MsgNode>(buf.c_str(),buf.length()));
    if (this->_send_panding)
    {
        return;
    }
    this->_socket->async_send(boost::asio::buffer(buf.c_str(),buf.size()),std::bind(&Session::WriteAllCallBack,this,std::placeholders::_1,std::placeholders::_2));
    this->_send_panding = true;
}

void Session::ReadCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (ec.value()!=0)
    {
        std::cout<<"error code:"<<ec.value()<<"\n";
        return;
    }
    _read_node->append_data_offset(bytes_transferred);
    if (_read_node->get_cur_index()!=_read_node->get_total())
    {
        _socket->async_read_some(
            boost::asio::buffer(_read_node->get_msg()+_read_node->get_cur_index(),_read_node->get_total()-_read_node->get_cur_index())
            ,std::bind(&Session::ReadCallBack,this,std::placeholders::_1,std::placeholders::_2)
        );
        return;
    }
    _read_panding = false;
    //TODO:处理接收到的数据
    _read_node = nullptr;
}

void Session::ReadToSocket()
{
    if(_read_panding)
    {
        return;
    }
    _read_node = std::make_shared<MsgNode>(RECVSIZE);
    this->_socket->async_read_some(
        boost::asio::buffer(_read_node->get_msg(),_read_node->get_total())
        ,std::bind(&Session::ReadCallBack,this,std::placeholders::_1,std::placeholders::_2)
    );
    _read_panding = false;
    //TODO:处理接收到的数据
    _read_node = nullptr;
}

void Session::ReadAllCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (ec.value()!=0)
    {
        std::cout<<"error code:"<<ec.value();
        return;
    }
    _read_node->append_data_offset(bytes_transferred);

    _read_panding = false;
    //TODO:处理接收到的数据
    _read_node = nullptr;
}

void Session::ReadAllToSocket()
{
    if (_read_panding)
    {
        return;
    }
    _read_node = std::make_shared<MsgNode>(RECVSIZE);
    this->_socket->async_receive(boost::asio::buffer(_read_node->get_msg(),_read_node->get_total())
        ,std::bind(&Session::ReadAllCallBack,this,std::placeholders::_1,std::placeholders::_2)
    );
    _read_panding = true;
}
