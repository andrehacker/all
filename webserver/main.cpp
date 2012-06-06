#include <iostream>
#include "HttpServer.h"

int main() {
	
	cout << "Server started" << endl;
		
	HttpServer server(2);
	server.Start();
}

