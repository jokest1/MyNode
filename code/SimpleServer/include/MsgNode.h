/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-05 09:42:02
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-05 10:00:01
 * @FilePath: \code\SimpleServer\include\MsgNode.h
 * @Description: 
 * 
 */
#pragma once
#include <boost/asio.hpp>

#define HEAD_TOTAL_LEN 4

class MsgNode
{
public:
    MsgNode(int length);
    ~MsgNode();
    void clear();
    int get_unused_length()const;
    const char* get_unused_data()const;
    char* get_msg();
    int get_total_length()const;
protected:
    int _total_length;
    int _cur_length;
    char* _data;
};

class WriteNode:public MsgNode
{
public:
    WriteNode(const char* msg,int msg_length,short msg_id);
private:
    short _msg_id;
};

class ReadNode:public MsgNode
{
public:
    ReadNode(int max_len,short msg_id);
private:
    short _msg_id;
};
