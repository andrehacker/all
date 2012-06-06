    #include <iostream>
    #include <thread>
    #include <boost/asio.hpp>
    #include <boost/thread.hpp>
    using std::cout;
    using std::endl;
    using boost::asio::ip::tcp;
	
    class HttpServer
    {
    public:
        HttpServer(std::size_t thread_pool_size)
        : io_service_(),
        endpoint_(boost::asio::ip::tcp::v4(), 8000),
        acceptor_(io_service_, endpoint_)
        { }
        
        void Start() {
            acceptor_.listen();
            cout << "Adr before " << &io_service_ << endl;
            std::thread io_thread([this](){
				cout << "Adr inside " << &io_service_ << endl;
				/*cout << "Line 1" << endl;
				cout << "Line 2" << endl;
				cout << "Line 3" << endl;
				cout << "Line 4" << endl;
				cout << "Line 5" << endl;
				cout << "Line 6" << endl;*/
				io_service_.run();
			});
            io_thread.join();
        }
        
    private:
        boost::asio::io_service io_service_;
        tcp::endpoint endpoint_;
        tcp::acceptor acceptor_;
    };

    int main() {
        HttpServer server(2);
        server.Start();
    }
