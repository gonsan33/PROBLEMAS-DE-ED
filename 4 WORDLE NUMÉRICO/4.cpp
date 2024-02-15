#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std; 


const int MAX_ELEMS = 2000;

class Multiconjunto {
private:
	struct Elem {
		int valor;
		int multiplicidad;
		bool operator <(const Elem& b) const {
			return valor < b.valor;
		}
		Elem(int v = 0, int m = 1) : valor(v), multiplicidad(m) {}
	};
	Elem elems[MAX_ELEMS];
	int num_elems;

public:
	Multiconjunto() : num_elems(0) {} //Coste constante O(1)

	void anyadir(int elem); // añade un elemento al multiconjunto

	int lower(const Elem elems[MAX_ELEMS], int ini, int fin, int valor) const;
	void eliminar(int elem);
	bool pertenece(int elem) const; // comprueba si un elemento está en el multiconjunto

	pair<bool, int> perteneceConMultiplicidad(int elem) const; // comprueba si un elemento está en el multiconjunto; y, si lo está, devuelve su multiplicidad
	int add(int elem); 

};

int Multiconjunto::lower(const Elem elems[MAX_ELEMS], int ini, int fin, int valor) const {
	if (ini + 1 >= fin) return ini;
	else {
		int mitad = (ini + fin - 1) / 2;
		if (elems[mitad].valor < valor) return lower(elems, mitad + 1, fin, valor);
		else return lower(elems, ini, mitad + 1, valor);
	}

}
void Multiconjunto::anyadir(int elem) {
	int pos = lower(elems, 0, num_elems, elem);
	if (elems[pos].valor == elem) ++elems[pos].multiplicidad;
	else {
		if (elems[pos].valor < elem && num_elems > 0) ++pos;
		for (int i = num_elems; i > pos; --i) elems[i] = elems[i - 1];
		elems[pos] = Elem(elem, 1);
		++num_elems;
	}
}

void Multiconjunto::eliminar(int elem) {
	int pos = lower(elems, 0, num_elems, elem);
	if (elems[pos].valor == elem) --elems[pos].multiplicidad;
	else {
		for (int i = pos; i < num_elems - 1; ++i) elems[i] = elems[i + 1];
		--num_elems;
	}
}

bool Multiconjunto::pertenece(int elem) const {
	return elems[lower(this->elems, 0, num_elems, elem)].valor == elem;
}

ostream& operator << (ostream& op, const vector<char>& v) {
	for (auto& x : v) cout << x;
	return op;
}

pair<bool, int> Multiconjunto::perteneceConMultiplicidad(int elem) const { // comprueba si un elemento está en el multiconjunto; y, si lo está, devuelve su multiplicidad
	int pos = lower(this->elems, 0, num_elems, elem);
	int multiplicidad = elems[pos].multiplicidad;
	return { elems[pos].valor == elem, multiplicidad };
}

int Multiconjunto::add(int elem) {
	int pos = lower(elems, 0, num_elems, elem);
	if (elems[pos].valor == elem) ++elems[pos].multiplicidad;
	else {
		if (elems[pos].valor < elem && num_elems > 0) ++pos;
		for (int i = num_elems; i > pos; --i) elems[i] = elems[i - 1];
		elems[pos] = Elem(elem, 1);
		++num_elems;
	}
	return elems[pos].multiplicidad;
}

bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (n == 0) return false; 
	else {

		//Se obtiene la clave correcta, como conjunto y como multiconjunto
		vector<int> key(n); 
		Multiconjunto llave; 
		for (int& x : key) {
			cin >> x; 
			llave.anyadir(x); 
		}

		vector<int> solution(n); 
		Multiconjunto sol; 
		
		vector<char> salida(n); 
		//Se lee
		for (int i = 0; i < n; ++i) {
			cin >> solution[i]; 
			//Si el número en la posición i en la llave y en la solución coinciden, está bien colocado. Luego se guarda que está bien colocado, y se mete en el Multiconjunto sol
			//para que, después, no haya problemas.
			if (solution[i] == key[i]) {
				sol.anyadir(solution[i]); 
				salida[i] = '#'; 
			}
		}

		//Ahora se vuelve a recorrer el vector para pintar las posiciones en las que no hay un número correcto
		for (int i = 0; i < n; ++i) {
			if (solution[i] != key[i]) {
				//Se añade al multiconjunto solución y se obtiene la multiplicidad del elemento
				int multiplicidad = sol.add(solution[i]); 
				//Se mira si el elemento está en la llave 
				auto aux = llave.perteneceConMultiplicidad(solution[i]); 
				if (aux.first && multiplicidad <= aux.second) salida[i] = 'O';
				else salida[i] = '.'; 
			}
		}

		cout << salida << '\n'; 




		return true; 
	}
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}

