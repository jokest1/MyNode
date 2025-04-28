#include "ReadWrite.h"
#include <iostream>

std::string test_tool::ReadDataForSocker(boost::asio::ip::tcp::socket& s)
{
    static char data_buf[1024];
    static size_t data_buf_length = 0;
    std::string ret;
    data_buf_length = 0;
    memset(data_buf,0,sizeof(char)*1024);
    data_buf_length = s.receive(boost::asio::buffer(data_buf,1024));
    std::cout<<"read length:"<< data_buf_length<<"\n";
    ret.append(data_buf,data_buf_length+1);
    return ret;
}

bool test_tool::WriteDataToSocket(const std::string &data, boost::asio::ip::tcp::socket& s)
{
    static size_t data_length = 0;
    data_length = boost::asio::write(s,boost::asio::buffer(data.c_str(),data.length()));
    if (data_length == data.length())
    {
        return true;
    }
    return false;
}
