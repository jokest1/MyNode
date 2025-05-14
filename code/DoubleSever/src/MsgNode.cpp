/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-03 14:09:49
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 11:54:09
 * @FilePath: \code\DoubleSever\src\MsgNode.cpp
 * @Description: 
 * 
 */
#include "MsgNode.h"
#include <string>
#include <algorithm>
#include <cstring>

MsgNode::MsgNode(int size)
    :_total(size)
    ,_cur_index(0)
{
    this->_data = new char[_total];
    std::fill(this->_data,this->_data+_total,0);
}
MsgNode::MsgNode(const char* data,int size)
    :MsgNode(size)
{
    std::memcpy(_data,data,sizeof(char)*size);
}
MsgNode::~MsgNode()
{
    delete[] _data;
}
const char* MsgNode::get_offset_data()const
{
    return _data+_cur_index;
}
char* MsgNode::get_msg()const
{
    return _data;
}
int MsgNode::get_offset_length()const
{
    return _total-_cur_index;
}
int MsgNode::get_total_length()const
{
    return _total;
}
void MsgNode::clear()
{
    std::fill(this->_data,this->_data+_total,0);
    _cur_index = 0;
}