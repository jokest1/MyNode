/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-29 10:07:10
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-29 17:37:09
 * @FilePath: \code\AsyncSeverC\src\MsgNode.cpp
 * @Description: 
 * 
 */
#include "MsgNode.h"

MsgNode::MsgNode(const char* msg,int lenght)
    :MsgNode(lenght)
{
    memcpy(_data,msg,sizeof(char)*_total_length);
}
MsgNode::MsgNode(int lenght)
    :_total_length(lenght)
    ,_cur_length(0)
{
    _data = new char[_total_length];
    clear();
}
MsgNode::~MsgNode()
{
    delete[] _data;
}
char* MsgNode::get_msg()
{
    return _data;
}
int MsgNode::get_cur_index()const
{
    return _cur_length;
}
int MsgNode::get_total()const
{
    return _total_length;
}
void MsgNode::append_offset_index(int index)
{
    _cur_length+=index;
}
char* MsgNode::get_unused_data()const
{
    return _data+_cur_length;
}
int MsgNode::get_unused_length()const
{
    return _total_length - _cur_length;

}
void MsgNode::clear()
{
    clear_memory(_data,_total_length);
    _cur_length = 0;
}

void MsgNode::clear_memory(char* d,size_t length)
{
    std::fill(d,d+length,0);
}