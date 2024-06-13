// ED Junio 2023. Ejercicio 1

//***************************************************
// IMPORTANTE
//
// Nombre del alumno
// Usuario del juez que se está usando en la prueba
//
//**************************************************


#include <iostream>
#include <fstream>
#include <stdexcept>

#include "linked_list_ed.h" 

template <class T>
class linked_list_ed_plus : public linked_list_ed<T> {
    using Nodo = typename linked_list_ed<T>::Nodo;
public:
    void print(std::ostream & o = std::cout) const {
        if (!this->empty()) {// la lista no está vacía
            Nodo * aux = this->prim;
            o << aux->elem;
            aux = aux->sig;
            while (aux != nullptr) {
                o << ' ' << aux->elem;
                aux = aux->sig;
            }
        }
    }
    
    // ordenación con el método de la burbuja
    void ordenarBurbuja() {
        if (this->prim == nullptr || this->prim->sig == nullptr) return; // lista de 0 o 1 elementos
        
        // listas con 2 o mas elementos
        Nodo* fin = nullptr;
        while (fin != this->prim->sig) {
            fin = desplazar(fin);
        }
    }
    
private: 
    Nodo* desplazar(Nodo* fin) {


        // Aqui el codigo del alumno



    }
};

template <class T>
inline std::ostream& operator<<(std::ostream & o, linked_list_ed_plus<T> const& a) {
    a.print(o);
    return o;
}

bool resuelveCaso() {
    // lectura de los datos
    int numElem;
    std::cin >> numElem;
    if (numElem == 0) return false;
    
    linked_list_ed_plus<int> lista;
    for (size_t i = 0; i < numElem; ++i) {
        int n;
        std::cin >> n;
        lista.push_back(n);
    }
    
    // Ordenar la lista
    lista.ordenarBurbuja();
    
    
    // Escribir el resultado
    std::cout << lista << '\n';
    
    return true;
}


int main() {

 #ifndef DOMJUDGE
 std::ifstream in("sample1.txt");
auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
 #endif

    while (resuelveCaso()) {}


  #ifndef DOMJUDGE // para dejar todo como estaba al principio
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
  #endif

return 0;
}
