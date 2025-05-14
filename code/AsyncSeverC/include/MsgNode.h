/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-29 10:07:06
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-29 17:36:58
 * @FilePath: \code\AsyncSeverC\include\MsgNode.h
 * @Description: 
 * 
 */
#include <string>
#include <memory>
#include <algorithm>

class MsgNode
{

public:
    MsgNode(const char* msg,int lenght);
    MsgNode(int lenght);
    ~MsgNode();
    char* get_msg();
    int get_cur_index()const;
    int get_total()const;
    void append_offset_index(int index);
    char* get_unused_data()const;
    int get_unused_length()const;

    void clear();
    static void clear_memory(char* d,size_t length);
private:
    int _total_length;
    int _cur_length;
    char* _data;
};


