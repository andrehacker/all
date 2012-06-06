#include <iostream>
#include <thread>		// for thread object
#include <vector>

void doSomething(int id)
{
	std::cout << "I am " << id << std::endl;
}

void controlThreads()
{
	std::cout << "START" << std::endl;

	// store Threads in vector
	std::vector<std::thread> threads;
	
	for (int id=0; id<10;id++)
	{
		// Create and start thread;
		threads.push_back(std::thread(doSomething, id));
	}
	
	for (auto t = threads.begin(); t != threads.end(); ++t)
	{
		t->join();	// why dereferencing here?
	}
	
	std::cout << "DONE" << std::endl;
}

int main () 
{
	
	controlThreads();
}
