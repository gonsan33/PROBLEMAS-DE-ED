// ****  IMPORTANTE  ******

// Nombre y apellidos del estudiante

// Usuario del juez de examen

//*************************************


#include <iostream>

#include "double_linked_list_ed.h"



template <class T>
class Particion : public double_linked_list_ed<T> {
    using Nodo = typename double_linked_list_ed<T>::Nodo;
public:
    void printIz(std::ostream & o = std::cout) const {
        if (!this->empty()) {// la lista no está vacía
            Nodo * aux = this->fantasma->sig;
            o << aux->elem;
            aux = aux->sig;
            while (aux != this->fantasma) {
                o << ' ' << aux->elem;
                aux = aux->sig;
            }
        }
        std::cout << '\n';
    }
    
    void printDr(std::ostream & o = std::cout) const {
        if (!this->empty()) {// la lista no está vacía
            Nodo * aux = this->fantasma->ant;
            o << aux->elem;
            aux = aux->ant;
            while (aux != this->fantasma) {
                o << ' ' << aux->elem;
                aux = aux->ant;
            }
        }
        std::cout << '\n';
    }
    
    // Partir una lista en menores, iguales y mayores que el pivote
    // Se debe comentar el código indicando lo que representa cada puntero que se emplea
    void particion() {
 
        
        

        // Aqui el código que resuelve el problema
        

        
        

    }
    
    void rotar() {
        if (!this->empty() && this->fantasma->sig->sig != nullptr) {
            // Dos o mas elementos
            Nodo* a_mover = this->fantasma->sig; 
            Nodo* ult = this->fantasma->ant;
            // Desengancha el primer nodo
            this->fantasma->sig= a_mover->sig;
            this->fantasma->sig->ant = this->fantasma;
            // Lo engancha al final de la lista
            a_mover->sig = this->fantasma;
            a_mover->ant = this->fantasma->ant;
            this->fantasma->ant->sig = a_mover;
            this->fantasma->ant = a_mover;
            // repite el proceso para todos los demás nodos de la lista
            Nodo* act = a_mover;
            while (ult->sig != this->fantasma) {
                a_mover = this->fantasma->sig; 
                // Desengancha el primer nodo
                this->fantasma->sig= a_mover->sig;
                this->fantasma->sig->ant = this->fantasma;
                // Lo engancha al final de la lista
                a_mover->sig = this->fantasma;
                a_mover->ant = act;
                act->sig = a_mover;
                this->fantasma->ant = a_mover;
                act = act->sig;
            }
        }
    }
    
    
};

template <class T>
inline std::ostream& operator<<(std::ostream & o, Particion<T> const& a) {
    a.printIz(o);
    return o;
}

bool resuelveCaso() {
    // Lectura de los datos
    int n;
    std::cin >> n;
    if (n == 0) return false;
    Particion<int> lista;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        lista.push_back(k);
    }
    // LLamada a la función que resuelve el problema
    lista.particion();
    
    // Se rota la lista para detectar posibles errores en la asignación de los punteros
    lista.rotar();
    
    // Se escribe el resultado
    std::cout << lista;
    return true;
}


int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("casos1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
    while (resuelveCaso()) {}
    
    
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}

