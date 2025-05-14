/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-05-03 14:31:04
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-04 11:14:46
 * @FilePath: \code\DoubleSever\include\Session.h
 * @Description: 
 * 
 */
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <boost/uuid.hpp>
#include <queue>
#include <iostream>

#define MAX_READ_DATA_LENGTH 2048

class Server;
class MsgNode;

class Session:public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_context& ioc,Server* p);
    ~Session();
    void start();
    const std::string& get_uuid()const;
    boost::asio::ip::tcp::socket& Socket();
    void send(const std::string& data);
    void send(const char* data,std::size_t length);
private:
    void handle_read(const boost::system::error_code& ec,std::size_t bytes_transfered);
    void handle_write(const boost::system::error_code& ec);
    void _start_send_que_data();
    boost::asio::ip::tcp::socket _socket;
    std::string _uuid;
    Server* _parent;
    std::queue<std::shared_ptr<MsgNode>> _data_que;
    std::mutex _mutex;
    std::shared_ptr<MsgNode> _read_data;
};

/*
MsgNode* msg_head;
MsgNode* msg_data;
bool head_parse = false ;

*/
