//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la solución y justificación del coste de tu algoritmo.













#include <iostream> 
#include <fstream> 
#include "double_linked_list_ed.h"

template <typename T>
class lista_ext : public double_linked_list_ed<T> {
    using Nodo = typename double_linked_list_ed<T>::Nodo;
public:
    void print(std::ostream& o = std::cout) const {
        if (!this->empty()) {// la lista no esta vacia
            Nodo * aux = this->fantasma->sig;
            o << aux->elem;
            aux = aux->sig;
            while (aux != this->fantasma) {
                o << ' ' << aux->elem;
                aux = aux->sig;
            }
        }
    }
    

    void desparizar(lista_ext<T> & aux) {
        Nodo* current = this->fantasma->sig; 
        while (current != this->fantasma) {
            Nodo* old_current = current; 
            current = current->sig; 
            if (old_current->elem % 2 == 0) {
                dettach(old_current); 
                aux.attach(old_current, aux.fantasma); 
            }
        }
        
    }
private: 
    void dettach(Nodo* nodo) {
        nodo->ant->sig = nodo->sig; 
        nodo->sig->ant = nodo->ant; 
        nodo->sig = nullptr; 
        nodo->ant = nullptr; 
    }
    void attach(Nodo* node, Nodo* position) {
        node->sig = position; 
        node->ant = position->ant; 
        position->ant->sig = node; 
        position->ant = node; 
    }
    
};


void resuelveCaso () {
    // Lectura de los datos de entrada
    lista_ext<int> l;
    lista_ext<int> aux;
    int n; std::cin >> n;
    while (n != 0) {
        l.push_back(n);
        std::cin >> n;
    }
    std::cin >> n; 
    while (n != 0) {
        aux.push_back(n);
        std::cin >> n;
    }
    // LLamada a la funcion que resuelve el problema
    l.desparizar(aux);
    // Escribir los resultados
    l.print();
    std::cout << '\n';
    aux.print();
    std::cout << '\n';
} 


int main() {
 
#ifndef DOMJUDGE
    std::ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif
    
    int numCasos = 1;   std::cin >> numCasos; std::cin.ignore();
 
    for (int i = 0; i < numCasos; ++i) resuelveCaso();
    
  
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
   
    return 0;
}

