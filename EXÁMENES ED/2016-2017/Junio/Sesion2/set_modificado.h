
/*
 Se ha añadido un método público lower_bound (línea 108), que llama a otro método
 privado recursivo lower_bound (línea 194) que recibe además un puntero a un nodo del
 árbol (inicialmente la raíz). El método recursivo compara el elemento buscado con
 el elemento en el nodo apuntado. Si el elemento en la raíz es menor, entonces
 se busca en el hijo derecho. Si no, ya sabemos que existe un elemento mayor o
 igual que el buscado. Se busca en el hijo izquierdo por si existiera una aproximación
 mejor. Si es que sí, se devuelve lo encontrado en el hijo izquierdo. Si no,
 se devuelve la raíz.
 El coste es lineal respecto a la altura del árbol. Si el árbol está equilibrado,
 el coste es logaritmico respecto al número de nodos (elementos en el conjunto).
 */

//
//  set_eda.h
//
//  Implementación de conjuntos utilizando árboles de búsqueda
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 15/03/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef set_eda_h
#define set_eda_h

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>

template <class T, class Comparador = std::less<T>>
class set {
    using set_t = set<T, Comparador>;
    
    /*
     Nodo que almacena internamente el elemento (de tipo T),
     y punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vacío.
     */
    struct TreeNode;
    using Link = TreeNode *;
    struct TreeNode {
        T elem;
        Link iz;
        Link dr;
        TreeNode(T const& e, Link i = nullptr, Link d = nullptr) : elem(e), iz(i), dr(d) {}
    };
    
    // puntero a la raíz de la estructura jerárquica de nodos
    Link raiz;
    
    // número de elementos (cardinal del conjunto)
    size_t nelems;
    
    // objeto función que compara elementos (orden total estricto)
    Comparador menor;
    
public:
    
    set(Comparador c = Comparador()) : raiz(nullptr), nelems(0), menor(c) {}
    
    set(set_t const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }
    
    set_t & operator=(set_t const& that) {
        if (this != &that) {
            libera(raiz);
            raiz = copia(that.raiz);
            nelems = that.nelems;
            menor = that.menor;
        }
        return *this;
    }
    
    ~set() {
        libera(raiz);
        raiz = nullptr;
    };
    
    void insert(T const& e) {
        inserta(e, raiz);
    }
    
    bool empty() const {
        return raiz == nullptr;
    }
    
    size_t size() const {
        return nelems;
    }
    
    bool contains(T const& e) const  {
        return pertenece(e, raiz);
    }
    
    void erase(T const& e) {
        borra(e, raiz);
    }
    
    std::pair<bool,T> lower_bound(T const& e) const {
        return lower_bound(e, raiz);
    }
    
protected:
    
    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr));
    }
    
    static void libera(Link a) {
        if (a != nullptr){
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }
    
    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) {
            return false;
        }
        else if (menor(e, a->elem)) {
            return pertenece(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            return pertenece(e, a->dr);
        }
        else { // e == a->elem
            return true;
        }
    }
    
    void inserta(T const& e, Link & a) {
        if (a == nullptr) {
            a = new TreeNode(e);
            ++nelems;
        }
        else if (menor(e, a->elem)) {
            inserta(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            inserta(e, a->dr);
        }
        // else
        //   el elemento e ya está en el árbol (el conjunto no se modifica)
    }
    
    void borra(T const& e, Link & a)  {
        if (a != nullptr) {
            if (menor(e, a->elem)) {
                borra(e, a->iz);
            }
            else if (menor(a->elem, e)) {
                borra(e, a->dr);
            }
            else // e == a->elem
                if (a->iz == nullptr || a->dr == nullptr) {
                    Link aux = a;
                    a = a->iz == nullptr ? a->dr : a->iz;
                    --nelems;
                    delete aux;
                }
                else { // tiene dos hijos
                    subirMenor(a, a->dr, nullptr);
                    --nelems;
                }
        }
    }
    
    static void subirMenor(Link & a, Link b, Link padre) {
        if (b->iz != nullptr){
            subirMenor(a, b->iz, b);
        }
        else {
            if (padre != nullptr) {
                padre->iz = b->dr;
                b->dr = a->dr;
            }
            b->iz = a->iz;
            delete a;
            a = b;
        }
    }
    
    std::pair<bool,T> lower_bound(T const& e, Link r) const {
        if (r == nullptr)  // no hay elementos mayores o iguales que e
            return { false, T() };
        else {
            if (menor(r->elem, e)) // si el elemento en la raíz es menor
                return lower_bound(e, r->dr);  // buscamos en el hijo derecho
            else { // sí hay elementos mayores o iguales que e
                auto iz = lower_bound(e, r->iz); // buscamos en el hijo izquierdo
                if (iz.first)  // si se ha encontrado algo
                    return iz; // es lo que devolvemos, será más ajustado que la raíz
                else // el hijo izquierdo no ha servido para mejorar
                    return {true, r->elem}; // devolvemos true y la raíz
            }
        }
    }
    
public:
    // iterador que recorre los elementos del conjunto de menor a mayor
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr)
                throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }
        
        T const* operator->() const {
            return &operator*();
        }
        
        const_iterator & operator++() {  // ++ prefijo
            next();
            return *this;
        }
        
        bool operator==(const_iterator const& that) const {
            return act == that.act;
        }
        
        bool operator!=(const_iterator const& that) const {
            return !(this->operator==(that));
        }
        
    protected:
        friend class set;
        Link act;
        std::stack<Link> ancestros;  // antecesores no visitados
        
        // construye el iterador al primero
        const_iterator(Link ptr) { act = first(ptr); }
        
        // construye el iterador al último
        const_iterator() : act(nullptr) {}
        
        Link first(Link ptr) {
            if (ptr == nullptr) {
                return nullptr;
            } else { // buscamos el nodo más a la izquierda
                while (ptr->iz != nullptr) {
                    ancestros.push(ptr);
                    ptr = ptr->iz;
                }
                return ptr;
            }
        }
        
        void next() {
            if (act == nullptr) {
                throw std::out_of_range("El iterador no puede avanzar");
            } else if (act->dr != nullptr) { // primero del hijo derecho
                act = first(act->dr);
            } else if (ancestros.empty()) { // hemos llegado al final
                act = nullptr;
            } else { // podemos retroceder
                act = ancestros.top();
                ancestros.pop();
            }
        }
    };
    
    const_iterator begin() const {
        return const_iterator(raiz);
    }
    
    const_iterator end() const {
        return const_iterator();
    }
        
};


#endif // set_eda_h
