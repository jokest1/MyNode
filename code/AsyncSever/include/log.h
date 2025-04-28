#include <iostream>
#include <boost/asio.hpp>
#include "Server.h"
#include "Session.h"
namespace test
{
void TestExe(int argc,const char* argv[])
{
    try
    {
        boost::asio::io_context ioc;
        Server s(ioc,10086);
        ioc.run();
    }
    catch(const boost::system::error_code& e)
    {
        std::cerr << e.what() << '\n';
    }
}
} // namespace test
