/**
 * Lösung für Aufgabe 1 auf Basis von Templates mit globalen Funktionen
 * Author: André Hacker
 */

#include <iostream>
using std::cout;
using std::endl;

namespace T{
	
	enum Futter {FISCH, BANANEN};
	
	// Global templates and structs, just for definition
	template <typename T>
	struct Tier {};

	struct Hai;
	template <>
	struct Tier<Hai> {/*Here I could define specific stuff*/};
	
	struct Delphin;
	
	struct Affe;
	
	// Global functions
	// fuettern
	template <typename T>
	void fuettern (Tier<T> &tier, Futter futter) {
		cout << "Fuettern allgemein" << endl;
	}
	
	void fuettern (Tier<Hai> &hai, Futter futter) {
		cout << "Hai fuettern" << endl;
		if (futter != FISCH) {
			std::cout << "Hai mag aber nur Fisch!" << std::endl;
		}
	}
	
	void fuettern (Tier<Delphin> &hai, Futter futter) {
		cout << "Delphin fuettern" << endl;
		if (futter != FISCH) {
			std::cout << "Delphin mag aber nur Fisch!" << std::endl;
		}
	}
	
	void fuettern (Tier<Affe> &hai, Futter futter) {
		cout << "Affe fuettern" << endl;
		if (futter != BANANEN) {
			std::cout << "Affe mag aber nur Bananen!" << std::endl;
		}
	}
	
	// spielen
	template <typename T>
	void spielen (Tier<T> &tier) {
		cout << "Spielen mit irgendwas" << endl;
	}
	
	void spielen (Tier<Hai> &tier) {
		std::cout << "Spielen mit Hai. Schutzweste nicht vergessen!" << std::endl;
	}
	
	void spielen (Tier<Delphin> &tier) {
		std::cout << "Spielen mit Delphin." << std::endl;
	}
	
	void spielen (Tier<Affe> &tier) {
		std::cout << "Spielen mit Affe." << std::endl;
	}
	
	// tierpflege
	template <typename T>
	void tierpflege (Tier<T> &tier, Futter futter) {
		std::cout << "Tier pflegen" << std::endl;
		fuettern(tier, futter);
		spielen(tier);
	}
}
