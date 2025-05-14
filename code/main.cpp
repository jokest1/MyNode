/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-15 15:57:30
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-05-08 19:39:10
 * @FilePath: \code\main.cpp
 * @Description: 
 * 
 */

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include "log.h"

/// 函数模板偏特化demo
template <typename A, typename B>
void f(A a, B b) {
    std::cout << "Normal version." << std::endl;
}

template <typename A>
void f<A, int>(A a, int b) {
    std::cout << "Partial version." << std::endl;
}

int main(int argc,const char* argv[])
{
    //test::TestExe(argc,argv);
    f<double,int>(1,1);
    return 0;
}