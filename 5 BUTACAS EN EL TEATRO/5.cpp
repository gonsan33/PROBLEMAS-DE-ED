#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std; 



const int MAX_RESERVAS = 50000;
class Teatro {
public:
	Teatro(): reservas(0) {}
	bool nueva_reserva(int inicio, int fin, const string& nombre); 
	string nombre_reserva(int num_butaca) const ;
	int lower(int ini, int fin, int num_butaca) const;



private:
	struct Reserva {
		int inicio;
		int fin;
		string nombre;
		Reserva(int ini = 0, int fin= 0, const string & nombre = "") : inicio(ini), fin(fin), nombre(nombre) {}
		bool operator <(const Reserva& a) const {
			return this->fin < a.inicio; 
		}
		bool operator < (int butaca) const {
			return this->fin < butaca; 
		}
		bool operator <= (int butaca) const {
			return this->fin < butaca || (this->inicio <= butaca && this->fin >= butaca);
		}
		bool includes(int butaca) const{return(this->inicio <= butaca && this->fin >= butaca);}
		
	};
	vector<Reserva> reservas;
	bool freeInterval(int ini, int fin, int& pos_ini) const; 
};

bool Teatro::nueva_reserva(int inicio, int fin, const string& nombre) {
	int pos; 
	if (this->reservas.size() == 0) {
		reservas.push_back(Reserva(inicio, fin, nombre));
		return true;
	}
	else if (this->freeInterval(inicio, fin, pos)) {
		Reserva nueva(inicio, fin, nombre);
		reservas.push_back(nueva); 
		if (reservas[pos] < inicio) ++pos; 
		for (int i = reservas.size() - 1; i > pos; --i) {
			reservas[i] = reservas[i - 1]; 
		}
		reservas[pos] = nueva; 
		return true; 
	}
	else return false; 


}
string Teatro::nombre_reserva(int num_butaca) const {
	int pos = this->lower(0, this->reservas.size(), num_butaca); 
	if (reservas.size() > 0 && this->reservas[pos].includes(num_butaca)) return this->reservas[pos].nombre;
	else return ""; 
}

int Teatro::lower(int ini, int fin, int num_butaca) const {
	if (ini + 1 >= fin) return ini;
	else {
		int mitad = (ini + fin - 1) / 2;
		if (this->reservas[mitad] < num_butaca) return  lower(mitad + 1, fin, num_butaca);
		else return lower(ini, mitad + 1, num_butaca);
	}
}

bool Teatro::freeInterval(int ini, int fin, int& pos_ini) const {
	if (reservas.size() > 0) {
		pos_ini = lower(0, reservas.size(), ini);
		if (this->reservas[pos_ini].fin < ini || this->reservas[pos_ini].inicio > fin) return true;
		else return false;
	}
	else return true; 
	 

}

 bool resuelveCasos() {
	int n, q; 
	cin >> n >> q; 
	if (n == 0 && q == 0) return false; 
	else {
		Teatro a; 
		for (int i = 0; i < n; ++i) {
			int ini, fin;
			string nombre; 
			cin >> ini >> fin >> nombre; 
			if (a.nueva_reserva(ini, fin, nombre)) cout << '.';
			else cout << 'X'; 
		}
		cout << '\n'; 
		for (int j = 0; j < q; ++j) {
			int cons; 
			cin >> cons; 
			string str = a.nombre_reserva(cons); 
			if (str != "") cout << str << '\n';
			else cout << "LIBRE\n"; 
		}
		cout << "---\n"; 
		return true; 
	}
}

int main() {
#ifndef DOMJUDGE
	std::ofstream out("salida.txt");
	auto coutbuf = std::cout.rdbuf(out.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 
	while (resuelveCasos()); 
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0; 
}



