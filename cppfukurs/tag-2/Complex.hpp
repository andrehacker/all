/**
 * Klasse für Komplexe Zahl
 * Author: André Hacker
 */

#include <string>
#include <sstream>

template <typename T>
class Complex {
public:
	
	//template <typename X>
	//friend Complex operator + (const Complex &left, const X &right);
	
	//template <typename X>
	//friend Complex operator + (const X &left, const Complex &right);
	
	Complex() {
		this->real = 0;
		this->imag = 0;
	}
	
	Complex(T real, T imag) {
		this->real = real;
		this->imag = imag;
	}
	
	// complex + complex
	Complex operator+(const Complex & other){
		return Complex<T>(other.real + real, other.imag + imag);
	}
	
	// Assignment operator for Anything -> Complex
	template <typename X>
	Complex & operator = (X other) {
		real = other;
		imag = 0;
		return *this;
	}
	
	// Conversion function for Complex -> Anything.
	// E. g.: int i; i = c;
	template <typename X>
	operator X() {
		return real;
	}
	
	T getReal() {
		return real;
	}
	
	T getImag() {
		return imag;
	}
	
	std::string toString() {
		std::stringstream ss;
		ss << real << " + " << imag << "i";
		return ss.str();
	}
	
private:
	T real;
	T imag;
};


//template <typename T>
//Complex<T> operator+ (Complex<T> &left, T right);

//template <typename T>
//Complex<T> operator+ (T left, Complex<T> &right);


