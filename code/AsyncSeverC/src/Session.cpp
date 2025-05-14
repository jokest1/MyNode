#include "Session.h"
#include "MsgNode.h"
#include "Server.h"

Session::Session(boost::asio::io_context& ioc,Server* p)
    :_socket(ioc)
    ,_parent(p)
    ,_read_node(std::make_shared<MsgNode>(1024))
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    _uuid = boost::uuids::to_string(uuid);
}
Session::~Session()
{
    
}
boost::asio::ip::tcp::socket& Session::Socket()
{
    return _socket;
}
void Session::start()
{
    /*
    开始进行通讯：
        1.清理存储数据的空间
        2.将读时间假如asio的事件队列
        3.绑定触发读事件的回调函数
    */
    _read_node->clear();
    _socket.async_read_some(
        boost::asio::buffer(
            _read_node->get_unused_data()
            ,
            _read_node->get_unused_length()
        )
        ,
        std::bind(
            &Session::handle_read
            ,
            shared_from_this()
            ,
            std::placeholders::_1
            ,
            std::placeholders::_2
        )
    );
}
void Session::send(const std::string& buf)
{
    /*
    手动调用send函数将发送的数据给对端
        1.首先构建要发送的数据
        2.判断当前是否已经有了发送数据
            有就加入到队列中
            没有就开启发送队列
    */
   std::lock_guard<std::mutex> lock(this->_send_lock);
   auto data = std::make_shared<MsgNode>(buf.c_str(),buf.size());
   std::cout<<"send data:"<<buf<<"\n";
   bool speeding =false;
   if (!_send_node.empty())
   {
    speeding=true;
   }
   _send_node.emplace(data);
   if (speeding)
   {
    return;
   }
   _socket.async_send(
    boost::asio::buffer(data->get_unused_data(),data->get_unused_length())
    ,
    std::bind(&Session::handle_write,shared_from_this(),std::placeholders::_1)
   );
   
}
const std::string& Session::uuid()const
{
    return _uuid;
}
void Session::handle_read(const boost::system::error_code& ec,std::size_t bytes_transfered)
{
    /*
    触发读事件的回调函数（代表系统缓冲区已经有了数据通知asio来取）
        1.判断是否有错误
        2.将数据读取出来进行处理
        3.将读取数据发送回去
    */
   if (!ec.value())
   {
        std::cout<<_read_node->get_msg()<<"\n";
        this->send(_read_node->get_msg());
   }
   else
   {
        _parent->clear_session(_uuid);
   }
   
}
void Session::handle_write(const boost::system::error_code& ec)
{
    /*
    触发写事件的回调函数代表系统缓冲区已经把用户要发送的数据移动到缓冲区了
        1.判断是否出现了错误
        2.删除掉当前正在排队的数据
        3.判断队列是否有数据有就继续发送没有就进入等待读取状态
    */
   if (!ec.value())
   {
    _send_node.pop();
    if (!_send_node.empty())
    {
        auto& data = _send_node.front();
        _send_node.pop();
        this->send(data->get_msg());
    }else
    {
        start();
    }
   }else
   {
    _parent->clear_session(_uuid);
   }
   
}