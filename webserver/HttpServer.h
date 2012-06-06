#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include <iostream>
#include <memory>	// for std::shared_ptr
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using std::cout;
using std::endl;
using boost::asio::ip::tcp;


class HttpServer
{

public:
	
	HttpServer(std::size_t thread_pool_size);
	
	void Start();
	
private:
	
	boost::asio::io_service io_service_;
	tcp::endpoint endpoint_;
	tcp::acceptor acceptor_;
	std::size_t thread_pool_size_;

	std::vector<std::shared_ptr<tcp::socket>> peers_;

	void HandleWrite(const boost::system::error_code &ec,
		std::size_t bytes_transferred);

	void HandleRequest(const tcp::socket *sock );

	void HandleAccept(const boost::system::error_code &ec,
		std::shared_ptr<tcp::socket> socket_pointer);
	
	void StartAccept ();
	
};

#endif
