#pragma once
/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-03 14:09:28
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 11:54:25
 * @FilePath: \code\DoubleSever\include\MsgNode.h
 * @Description: 
 * 
 */

class MsgNode
{

public:
    MsgNode(int size);
    MsgNode(const char* data,int size);
    ~MsgNode();
    const char* get_offset_data()const;
    char* get_msg()const;
    int get_offset_length()const;
    int get_total_length()const;
    void clear();
private:
    int _cur_index;
    int _total;
    char* _data;
};
