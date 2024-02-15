#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std; 


class Complejo {
private: 
	double x; 
	double y; 
public: 
	Complejo(double x = 0, double y = 0) : x(x), y(y) {}

	Complejo operator + (const Complejo& a) const {
		return Complejo(this->x + a.x, this->y + a.y); 
	}

	Complejo operator * (const Complejo& a) const {
		return Complejo(this->x * a.x - this->y * a.y, this->x * a.y + this->y * a.x); 
	}

	double module() const {
		return sqrt(x * x + y * y); 
	}

	void read(istream& op) {
		op >> x >> y; 
	}
};


Complejo recurrencia(const Complejo& z, const Complejo& c) {
	return z * z + c; 
}

istream& operator >> (istream& op, Complejo& c) {
	c.read(op); 
	return op; 
}


void resuelveCasos()  {
	Complejo c; 
	cin >> c; 
	int n; 
	cin >> n; 
	Complejo z(0,0); 
	int i = 0; 
	while (z.module() <= 2 && i < n) {
		z = recurrencia(z, c); 
		++i; 
	}
	if (z.module() <= 2) cout << "SI\n";
	else cout << "NO\n"; 


}

int main() {
	int n; 
	cin >> n; 
	for (int i = 0; i < n; ++i) resuelveCasos(); 
	return 0; 
}