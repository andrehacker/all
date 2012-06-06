/**
 * Aufgabenblatt 3
 * Author: André Hacker
 */

#include <iostream>
#include <memory>
#include "tier.hpp"
#include "tier-template.hpp"

using std::cout;
using std::endl;


// Code for pointer test
struct C {
	~C() {
		std::cout << "destructor" << std::endl;
	}
};

void ptr_test_sub(std::unique_ptr<C> &ptr) {
	std::cout << "exit sub()" << std::endl;
}

void ptr_test() {
	std::unique_ptr<C> ptr(new C);
	ptr_test_sub(ptr);
	std::cout << "exit test()" << std::endl;
}


int main () {
	
	// Aufgabe 1
	// Using classical OO style with inheritance
	cout << endl << "Aufgabe 1: Zoo" << endl;
	{
		using namespace OO;
		Hai hai;
		Delphin delphin;
		Affe affe;
		hai.fuettern(BANANEN);
		cout << endl;
		hai.spielen();
		cout << endl;
		hai.tierpflege(BANANEN);
		cout << endl;
		delphin.fuettern(BANANEN);
		cout << endl;
		delphin.spielen();
		cout << endl;
		delphin.tierpflege(BANANEN);
		cout << endl;
		affe.fuettern(BANANEN);
		cout << endl;
		affe.spielen();
		cout << endl;
		affe.tierpflege(BANANEN);
		cout << endl;
	}
	
	// Using Template Subclassing
	cout << endl << "Using Template subclassing now" << endl;
	{
		using namespace T;
		Tier<Hai> hai;
		Tier<Delphin> delphin;
		Tier<Affe> affe;
		fuettern(hai, Futter::BANANEN);
		cout << endl;
		fuettern(delphin, BANANEN);
		cout << endl;
		fuettern(affe, BANANEN);
		cout << endl;
		tierpflege(hai, BANANEN);
		cout << endl;
		tierpflege(delphin, BANANEN);
		cout << endl;
		tierpflege(affe, BANANEN);
		cout << endl;
	}
	
	// Test for unique-ptr. Found out that copy constructor is deleted!
	//ptr_test();
}
