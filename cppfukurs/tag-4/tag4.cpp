/**
 * Aufgabenblatt 3
 * Author: André Hacker
 */

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ostream;


class Person {
public:
	
	Person(string _name, string _vorname,
		int _geburtstag, int _geburtsmonat, int _geburtsjahr):
		name(_name), vorname(_vorname), geburtstag(_geburtstag),
		geburtsmonat(_geburtsmonat), geburtsjahr(_geburtsjahr) {};
	
	string name;
	string vorname;
	int geburtstag;
	int geburtsmonat;
	int geburtsjahr;
};

ostream& operator<< (ostream& out, const Person& person) {
	out << person.vorname << " " << person.name << "\t" << person.geburtstag << "." << person.geburtsmonat << "." << person.geburtsjahr;
}

// C++11 style using Lambda and auto. Could be done inline below as well.
auto smallerdate = [] (const Person p1, const Person p2) {
	if (p1.geburtsjahr < p2.geburtsjahr
			|| (p1.geburtsjahr == p2.geburtsjahr && p1.geburtsmonat < p2.geburtsmonat)
			|| (p1.geburtsjahr == p2.geburtsjahr && p1.geburtsmonat == p2.geburtsmonat && p1.geburtstag < p2.geburtstag)) {
		return true;
	}
	return false;
};

template <typename T>
void printAsLine(T& obj) {
	cout << obj << endl;
}

template <typename T>
void printVector(std::vector<T>& obj) {
	std::for_each(obj.begin(), obj.end(), printAsLine<T>);
	cout << endl;
}

int main () {
	
	std::vector<Person> p1;
	p1.push_back(Person("Hacker", "Andre", 22, 4, 1983));
	p1.push_back(Person("Hacker", "Katharina", 8, 5, 1984));
	p1.push_back(Person("Meier", "Hans", 21, 4, 1984));
	p1.push_back(Person("Heiner", "Dieter", 10, 4, 1930));
	p1.push_back(Person("Müller", "Olaf", 28, 2, 1968));
	p1.push_back(Person("Holzheim", "Sigi", 11, 9, 1987));
	p1.push_back(Person("Sonderbar", "Martin", 25, 6, 1993));
	p1.push_back(Person("Klein", "Manfred", 12, 4, 1993));
	p1.push_back(Person("Lustig", "Peter", 5, 1, 1962));
	p1.push_back(Person("Müller", "Hans", 14, 7, 2003));
	cout << "Ursprüngliche Liste von Personen" << endl;
	printVector(p1);
	
	cout << "Personen nach Name sortieren" << endl;
	std::vector<Person> p2(p1);	// make copy
	std::sort(p2.begin(), p2.end(), [] (const Person& p1, const Person& p2) {return p1.name.compare(p2.name) < 0;});
	printVector(p2);
	
	cout << "Personen nach Geburtsalter sortieren" << endl;
	std::vector<Person> p3(p1);
	std::sort(p3.begin(), p3.end(), smallerdate);
	printVector(p3);
	
	cout << "Vertauschen von Vorname und Nachname jeder Person" << endl;
	std::vector<Person> p4(p1);
	for_each(p4.begin(), p4.end(), [] (Person& p) {std::swap(p.name, p.vorname);});
	printVector(p4);
	
	cout << "Entferne alle Personen die nach 1985 geboren wurden" << endl;
	// Use erase-remove idiom
	std::vector<Person> p5(p1);
	p5.erase( std::remove_if(p5.begin(), p5.end(), [] (Person& p) {return p.geburtsjahr>=1985;}), p5.end() );
	printVector(p5);
	
	cout << "Wie viele Personen haben Nachname Müller" << endl;
	std::vector<Person> p6(p1);
	unsigned int count = static_cast<unsigned int>( std::count_if(p6.begin(), p6.end(), [] (Person& p) {return p.name == "Müller";}) );
	cout << "Personen mit Name Müller: " << count << endl;
}
