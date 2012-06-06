/**
 * Aufgabenblatt 1
 * Author: André Hacker
 */

template <int I>
struct Fib {
	static int val;
};

template <int I>
int Fib<I>::val = Fib<I-1>::val + Fib<I-2>::val;

// Recursion anchor by Template Spezialization
template < >
struct Fib <0> {
	static int val;
};

template < >
struct Fib <1> {
	static int val;
};


