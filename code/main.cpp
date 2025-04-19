/*
 * @Author: EST 363023987@qq.com
 * @Date: 2025-04-15 15:57:30
 * @LastEditors: EST 363023987@qq.com
 * @LastEditTime: 2025-04-19 21:03:46
 * @FilePath: \code\main.cpp
 * @Description: 
 * 
 */
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include "log.h"



int main(int argc,const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    /*
    using namespace std;
    cout<<"Enter your weight: ";
    float weight;
    cin>>weight;
    string gain = "A 10% increase raises ";
    string wt = boost::lexical_cast<string> (weight);
    gain = gain+wt+"to";
    weight = 1.1*weight;
    gain = gain + boost::lexical_cast<string>(weight)+".";
    cout<<gain<<endl;
    */
   test::TestExe(argc,argv);
    return 0;
}