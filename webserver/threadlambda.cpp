#include <iostream>
#include <thread>
#include <boost/asio.hpp>
using std::cout;
using std::endl;
using boost::asio::ip::tcp;

void test() {
	std::cout << "Line 1" << endl;
	std::cout << "Line 2" << endl;
	std::cout << "Line 3" << endl;
	std::cout << "Line 4" << endl;
	std::cout << "Line 5" << endl;
	std::cout << "Line 6" << endl;
}

int main() {
	
	boost::asio::io_service io_service;
	tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 8000);
	tcp::acceptor acceptor(io_service, endpoint);
	
	acceptor.listen();
	io_service.run();
	
	//return 0;
	/*std::thread io_thread([](){
		cout << "Line 1" << endl;
		cout << "Line 2" << endl;
		cout << "Line 3" << endl;
		cout << "Line 4" << endl;
		cout << "Line 5" << endl;
		cout << "Line 6" << endl;
	});*/
	std::thread io_thread(test);
	io_thread.join();
}
