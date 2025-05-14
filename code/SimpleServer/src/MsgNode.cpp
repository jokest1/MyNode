#include "MsgNode.h"
#include <algorithm>
#include <string>
#include <cstring>

MsgNode::MsgNode(int length)
    :_total_length(length)
    ,_cur_length(0)
{
    _data = new char[_total_length+1]{0};
}

MsgNode::~MsgNode()
{
    delete[] _data;
}

void MsgNode::clear()
{
    std::fill(_data,_data+_total_length,0);
    _cur_length = 0;
}

int MsgNode::get_unused_length()const
{
    return _total_length-_cur_length;
}

const char* MsgNode::get_unused_data()const
{
    return _data+get_unused_length();
}

char* MsgNode::get_msg()
{
    return _data;
}

int MsgNode::get_total_length()const
{
    return _total_length;
}


WriteNode::WriteNode(const char *msg, int msg_length, short msg_id)
    :MsgNode(msg_length+HEAD_TOTAL_LEN)
    ,_msg_id(msg_id)
{
    short net_msg_id=boost::asio::detail::socket_ops::host_to_network_short(msg_id);
    std::memcpy(this->_data,&net_msg_id,2);
    short net_msg_length=boost::asio::detail::socket_ops::host_to_network_short(msg_id);
    std::memcpy(this->_data+2,&net_msg_length,2);
    std::memcpy(this->_data+4,msg,msg_length);
}

ReadNode::ReadNode(int max_len, short msg_id)
    :MsgNode(max_len)
    ,_msg_id(msg_id)
{
    
}