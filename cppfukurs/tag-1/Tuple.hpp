/**
 * Aufgabenblatt 1
 * Author: André Hacker
 */

template <typename T, unsigned int SIZE>
class Tuple {
public:
	
	T getItem(int position) {
		return items[position];
	}
	
	void setItem(T item, int position) {
		items[position] = item;
	}
	
private:
	T items [SIZE];
};
