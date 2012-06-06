/**
 * Aufgabenblatt 1
 * Author: André Hacker
 */

#include <iostream>

template <typename T>
class Test {
public:
	
	// Here we have the constructor as a template
	template <typename X>
	Test(X val) {
		X testvar = val;
		std::cout << "Template constructor works well;)" << std::endl;
	}
	
	T getVal() {
		return mVal;
	}
	
private:
	// Static elements may only be initialized with definition. This is only the declaration
	static int mVal;
};
