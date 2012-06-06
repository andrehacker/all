#include <iostream>
#include <boost/asio.hpp>

// compiles with g++ -L/usr/lib/ main.cpp -o webserver -lpthread -lboost_system

int main()
{
	// access to OS's io service
    boost::asio::io_service io_service;
    
    // Get tcp socket
    boost::asio::ip::tcp::socket socket(io_service);
    
    boost::system::error_code error_code;	// boost way for error checking
    
    std::cout << "test" << std::endl;
}
