
#pragma once
#include <memory>
#include <mutex>
#include <iostream>

template<typename T>
class Singleton
{
protected:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&& )= delete;
    static std::shared_ptr<T> _instance;
public:
    ~Singleton()
    {
        std::cout <<"this is singleton destruct \n";
    }

    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag,[&]()
        {
            _instance = std::make_shared<T>(new T);
        }
        );
        return _instance;
    }
    void PrintAddress()
    {
        std::cout<<_instance.get()<<"\n";
    }
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
