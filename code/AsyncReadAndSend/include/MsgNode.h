/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-27 21:58:38
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-27 22:23:40
 * @FilePath: \code\AsyncReadAndSend\include\MsgNode.h
 * @Description: 
 *      用于记录数据的读写状态的节点
 */
#pragma once
#include <memory>
#include <string>

extern const int RECVSIZE = 1024;
class MsgNode
{
public:
    MsgNode(const char* msg,int total_len);
    MsgNode(int total_len);
    ~MsgNode();
    const char* get_msg()const;
    int get_cur_index()const;
    int get_total()const;
    void append_data_offset(int length);
private:
    char* _msg;
    int _total_length;
    int _cur_length;
};
