/**
 * Lösung für Aufgabe 1 auf Basis von Objektorientierung mit Vererbung
 * Author: André Hacker
 */

namespace OO {
	enum Futter {FISCH, BANANEN};

	class Tier {
	public:
		virtual void spielen() {
			std::cout << "Spielen mit Tier" << std::endl;
		}
		
		virtual void fuettern(Futter futter) {
			std::cout << "Tier füttern" << std::endl;
		}
		
		void tierpflege(Futter futter) {
			std::cout << "Tier pflegen" << std::endl;
			fuettern(futter);
			spielen();
		}
	};


	class Affe: public Tier {
	public:	
		void spielen() {
			std::cout << "Spielen mit Affe" << std::endl;
		}
		
		void fuettern(Futter futter) {
			std::cout << "Affen füttern" << std::endl;
			if (futter != BANANEN) {
				std::cout << "Affe mag aber nur Bananen!" << std::endl;
			}
		};
		
	};

	class Delphin: public Tier {
	public:
		void spielen() {
			std::cout << "Spielen mit Delphin" << std::endl;
		}
		
		void fuettern(Futter futter) {
			std::cout << "Delphin füttern" << std::endl;
			if (futter != FISCH) {
				std::cout << "Delphin mag aber nur Fisch!" << std::endl;
			}
		}
	};

	class Hai: public Tier {
	public:
		void spielen() {
			std::cout << "Spielen mit Hai. Schutzweste nicht vergessen!" << std::endl;
		}
		
		
		void fuettern(Futter futter) {
			std::cout << "Hai füttern" << std::endl;
			if (futter != FISCH) {
				std::cout << "Hai mag aber nur Fisch!" << std::endl;
			}
		}
	};

}
