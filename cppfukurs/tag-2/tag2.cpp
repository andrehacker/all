/**
 * Aufgabenblatt 2
 * Author: André Hacker
 */

#include <iostream>
#include <string>
#include <vector>
#include "Complex.hpp"

using std::cout;
using std::endl;

// complex + int or int + complex
template <typename T>
Complex<T> operator+ (Complex<T> &left, T right) {
	return Complex<T>(right + left.getReal(), left.getImag());
}

template <typename T>
Complex<T> operator+ (T left, Complex<T> &right) {
	return Complex<T>(right.getReal() + left, right.getImag());
}


// Aufgabe 2: Namespaces
//int i = 0;	// This will always cause a conflict if we redefine i in a sub namespace
namespace B {
	void f() {cout << "B" << endl;};
	int x = 100;
}

namespace A {
	using namespace B;
	void f() {cout << "A" << endl;};
	int i = 1;
	namespace ASub {
		int i = 2;
	}
}

namespace A {
	int j = 10;
}

// Aufgabe 3: stringType(str)

// Generic struct template
template <typename T>
struct TypeName {
	static std::string name;
};

template <typename T>
std::string TypeName<T>::name = "other";

// Complete specialization
template <>
std::string TypeName<std::string>::name = "string";

// Partial specialization. Does not work yet for unknown reasons
/*
template <typename T>
std::string TypeName<std::vector<T>>::name = "vector";

template <typename T>
std::string TypeName<std::vector<std::vector<T>>>::name = "vector of vector";

template <typename TChar, typename TTraits, typename TAlloc>
std::string TypeName<std::basic_string<TChar, TTraits, TAlloc>>::name = "basic_string";
*/

// Generic template method
template <typename T>
std::string stringType(T obj) {
	return TypeName<T>::name;
}

int main(){
	// Aufgabe 1: Complex numbers
	cout << endl << "** Aufgabe 1: Complex" << endl;
	Complex<int> a(1, 2);
	Complex<int> b(3, 4);
	Complex<int> c = a + b;
	cout << "Result: " << c.toString() << endl;
	
	int i;
	i = c;
	cout << "Complex to int (conversion function): " << i << endl;
	
	Complex<float> d;
	d = 14.3;
	cout << "int to complex (assignment operator): " << d.toString() << endl;
	
	Complex<float> e(1.1, 2.2), f, g;
	f = e + 2.0f;
	g = 2.0f + e;
	cout << "complex + int: " << f.toString() << endl;
	cout << "int + complex: " << g.toString() << endl;
	cout << endl;
	
	cout << "** Aufgabe 2: Namespaces" << endl;
	{
		using namespace A;
		//f();	// does not work, because A uses B and so B is also used/visible here!
		cout << x << endl;	// works - crazy!!!
		cout << i << endl;
		//cout << ::i << endl;
		cout << A::i << endl;
		cout << A::ASub::i << endl;
	}
	{
		using namespace A::ASub;
		cout << i;
	}
	cout << endl;
	
	cout << "** Aufgabe 3: stringType" << endl;
	std::string test("Hoho");
	cout << stringType(test) << endl;
	cout << stringType("Hoho") << endl;
	cout << stringType(1) << endl;
}
