
#include <iostream>
#include <memory>	// for std::shared_ptr
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "HttpServer.h"

using std::cout;
using std::endl;
using boost::asio::ip::tcp;


HttpServer::HttpServer(std::size_t thread_pool_size)
: io_service_(),
endpoint_(boost::asio::ip::tcp::v4(), 8000),
acceptor_(io_service_, endpoint_),
peers_(),
thread_pool_size_(thread_pool_size)
{
	
}
	
void HttpServer::Start() {
	
	acceptor_.listen();
	
	StartAccept();
	
	// Create pool of threads that all run the single io_service
	/*
	std::vector<boost::shared_ptr<boost::thread> > threads;
	for (std::size_t i = 0; i < thread_pool_size_; ++i)
	{
		boost::shared_ptr<boost::thread> thread(new boost::thread(
			boost::bind(&boost::asio::io_service::run, &io_service_)));
		
		threads.push_back(thread);
	}
	auto function_run = [this] () {
		cout << "Adr inside " << &io_service_ << endl;
		io_service_.run();
	};
	*/
	
	std::vector<std::shared_ptr<std::thread> > threads;
	for (std::size_t i = 0; i < thread_pool_size_; ++i)
	{
		std::shared_ptr<std::thread> thread(
			// http://stackoverflow.com/questions/7895879/using-member-variable-in-lambda-capture-list-inside-a-member-function
			new std::thread([this]() {
				// won't work. Also tried instead:
				// function_run();
				io_service_.run();
				}
			)
		);
		
		threads.push_back(thread);
	}

	// Wait for all threads in the pool to exit.
	for (std::size_t i = 0; i < threads.size(); ++i) {
		threads[i]->join();
	}
}

void HttpServer::HandleWrite(const boost::system::error_code &ec,
	std::size_t bytes_transferred) {
	cout << "Done writing" << endl;
}

/*
void HttpServer::HandleRequest(const tcp::socket *sock ) {
	const std::string kHttpStandardAnswer = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
	
	// TODO Handle http request (write something back!)
	boost::asio::async_write(sock,
		boost::asio::buffer(kHttpStandardAnswer),
		boost::bind(&HttpServer::HandleWrite,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
} */

void HttpServer::HandleAccept(const boost::system::error_code &ec,
	std::shared_ptr<tcp::socket> socket_pointer) {
	
	// accept next peers
	StartAccept();
	
	cout << "(thread " << std::this_thread::get_id << ") Client accepted. Peer count: " << peers_.size() << endl;
	
	if (!ec) {
		//HandleRequest(*socket_pointer);
	}
}

void HttpServer::StartAccept () {
	
	// new socket
	tcp::socket *peer_socket = new tcp::socket(io_service_);
	std::shared_ptr<tcp::socket> peer_pointer(peer_socket);
	
	peers_.push_back(peer_pointer);
	
	acceptor_.async_accept(*peer_socket,
		boost::bind(&HttpServer::HandleAccept,
			this,
			boost::asio::placeholders::error, peer_pointer));
}
