/**
 * Aufgabenblatt 1
 * Author: André Hacker
 */

#include <iostream>
#include <string>
#include "Tuple.hpp"
#include "fibo.hpp"
#include "tag1-aufgabe3.hpp"


template <typename T>
int length(T str) {
	int i = 0;
	while(str[i++] != '\0');
	return --i;
}

template <typename T>
char charAt(T str, int index) {
	return str[index];
}

template <typename T>
void printRev(T str) {
	for (int i = length(str); i>=0; i--) {
		std::cout << charAt(str, i);
	}
	std::cout << std::endl;
}


int main(){
	// Aufgabe 1
	std::cout << "** Aufgabe 1: length und charAt" << std::endl;
	char t1[] = "Hope";
	std::string t2("Hope2");
	std::cout << length(t1) << std::endl;
	std::cout << length(t2) << std::endl;
	std::cout << charAt(t1, 2) << std::endl;
	std::cout << charAt(t2, 2) << std::endl;
	printRev(t1);
	std::cout << std::endl;
	
	// Aufgabe 2
	std::cout << "** Aufgabe 2: Tuple" << std::endl;
	Tuple<int, 2> triple;
	triple.setItem(1, 0);
	triple.setItem(2, 1);
	std::cout << triple.getItem(0) << std::endl;
	std::cout << triple.getItem(1) << std::endl;
	std::cout << std::endl;
	
	// Aufgabe 3: Constructor Test. See also tag1-aufgabe3.hpp
	std::cout << "** Aufgabe 3: Constructor Test and static member" << std::endl;
	Test<int> test(3);
	std::cout << std::endl;
	
	// Aufgabe 4: 
	std::cout << "** Aufgabe 4: Fibo" << std::endl;
	std::cout << "FIB: " << Fib<7>::val << std::endl;
	
}
