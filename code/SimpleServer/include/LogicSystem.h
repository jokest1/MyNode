
#pragma once
#include "Singleton.h"
#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <queue>
#include <condition_variable>
#include <map>

class Session;
class LogicNode;

using FunCallBack = 
std::function<
    void(
        std::shared_ptr<Session>,
        const short& msg_id,
        const std::string& msg_data
    )
>;

class LogicSystem:public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    ~LogicSystem();
    void post_msg_to_que(std::shared_ptr<LogicNode> msg);
private:
    LogicSystem();
    void _DealMsg();
    void _RegisterCallBacks();
    void _HelloWordCallBack(
        std::shared_ptr<Session> ,
        const short& msg_id,
        const std::string& msg_data
    );
    std::thread _worker_thread;
    std::mutex _mutex;
    std::queue<std::shared_ptr<LogicNode>> _msg_que;
    std::condition_variable _condition;
    bool _b_stop;
    std::map<short,FunCallBack> _func_callbacks;
};
