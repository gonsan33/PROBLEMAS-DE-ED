#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std; 

class Hora {
private: 
	int h; 
	int m; 
	int s; 
public: 
	Hora(int h = 0, int m = 0, int s = 0) : h(h), m(m), s(s) {}
	int getHora()const { return h;  }
	int getMinute() const{ return m; }
	int getSecond() const { return s; }

	//Operador de comparación
	bool operator <(const Hora& b) const {
		return this->h < b.h || this->h == b.h && this->m < b.m || this->h == b.h && this->m == b.m && this->s < b.s; 
	}

	void read(istream& op) {
		op >> this->h; 
		op.ignore(1); 
		op >> this->m; 
		op.ignore(1); 
		op >> this->s; 
	}

	void print(ostream& op) const{
		op << setfill('0') << setw(2) << this->h << ':' << setw(2) << this->m << ':' << setw(2) << this->s; 
	}

	Hora operator + (const Hora& a) const {
		int m = this->m + a.m + (this->s + a.s) / 60; 
		int s = (this->s + a.s) % 60; 
		int h = this->h + a.h + m / 60; 
		m = m % 60; 
		h = h % 24; 
		return Hora(h, m, s); 
	}



};

istream& operator >> (std::istream& op, Hora& a) {
	a.read(op); 
	return op; 
}

ostream& operator << (std::ostream& op, const Hora& a) {
	a.print(op); 
	return op; 
}

class Pelicula {
private: 
	Hora ini; 
	Hora fin; 
	Hora dur; 
	string titulo; 
public: 
	Pelicula() : ini(), fin(), titulo() {}
	Pelicula(Hora in, Hora dur, string t) : ini(in), dur(dur), fin(in + dur), titulo(t) {

	}


	bool operator < (const Pelicula& b) const {
		return fin < b.fin || !(b.fin < fin) && titulo < b.titulo; 
	}

	void print(ostream& op) const {
		op << fin << ' ' << titulo <<'\n';
	}

	void read(istream& op) {
		op >> ini >> dur; 
		this->fin = ini + dur; 
		op.ignore(1); 
		getline(op, titulo); 
	}

	




};

istream& operator >> (istream& op, Pelicula& a) {
	a.read(op); 
	return op; 
}


ostream& operator << (ostream& op, const Pelicula& a) {
	a.print(op); 
	return op; 
}

ostream& operator << (ostream& op, const vector<Pelicula>& v) {
	
	for (int i = 0; i < v.size(); ++i) op << v[i]; 
	
	return op; 
}

bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (n == 0) return false; 
	vector<Pelicula> v(n); 
	for (auto& x : v) cin >> x; 
	std::sort(v.begin(), v.end()); 
	cout << v << "---\n";
	return true;
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}








