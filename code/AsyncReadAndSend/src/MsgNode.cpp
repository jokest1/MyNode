#include "MsgNode.h"
#include <string.h>


MsgNode::MsgNode(const char* msg,int total_len)
    :MsgNode(total_len)
{
    memcpy(_msg,msg,sizeof(char)*total_len);
}
MsgNode::MsgNode(int total_len)
    :_total_length(total_len)
    ,_cur_length(0)
{
    _msg = new char[total_len];
    memset(_msg,0,sizeof(char)*total_len);
}

MsgNode::~MsgNode()
{
    delete[] this->_msg;
}

const char *MsgNode::get_msg() const
{
    return _msg;
}

int MsgNode::get_cur_index() const
{
    return _cur_length;
}

int MsgNode::get_total() const
{
    return _total_length;
}

void MsgNode::append_data_offset(int length)
{
    this->_cur_length+=length;
}
