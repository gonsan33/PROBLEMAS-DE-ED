/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementaci�n del TAD Lista mediante listas enlazadas dobles.
  *
  * Esta versi�n incluye la sobrecarga de operadores <<, [] y asignaci�n.
  */

/*
#ifndef __LIST_LINKED_DOUBLE_H
#define __LIST_LINKED_DOUBLE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(int elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(int elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void swap2by2();//O(n)

    void zip(ListLinkedDouble& other); //O(n+m) con n el tamaño de la lista this, m el tamaño de other


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
    void ListLinkedDouble::dettach(Node* node); 
    void ListLinkedDouble::attach(Node* node, Node* position); 
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}
void  ListLinkedDouble::swap2by2() {
    int n = this->num_elems / 2;
    Node* current = head->next;
    for (int i = 0; i < n; ++i) {
        //Voy a intercambiar current y current->next
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current->next = current->next->next;
        current->next->prev = current;
        current->prev->next->next = current;
        current->prev = current->prev->next;

        //Avanzar: 
        current = current->next;
    }
}
/*
void ListLinkedDouble::zip(ListLinkedDouble& other) { //O(n+m) con n el tamaño de la lista this, m el tamaño de other
    int i = 0, j = 0; 
    Node* current = this->head->next;  
    Node* current_other = other.head->next; 
    while (i < this->size() && j < other.size()) {
        current_other->prev = current; 
        current->next->prev = current_other; 

        //Avanzo en current_other
        current_other = current_other->next; 
        //Avanzo en current
        current = current->next; 
        //Termino de conectar las listas: 
        current->prev->prev->next = current->prev; 
        current->prev->next = current; 


        ++i; 
        ++j; 
    }

    while (j < other.size()) {
        head->prev->next = current_other; 
        current_other->prev = head->prev; 

        //Avanzo en current_other
        current_other = current_other->next;

        //Termino de conectar las listas
        head->prev->next->next = head; 
        head->prev = head->prev->next; 
        ++j; 
    }

    other.head->next = other.head; 
    other.head->prev = other.head; 

    this->num_elems += other.num_elems; 
    other.num_elems = 0; 


}
*/
/*

void ListLinkedDouble::dettach(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void ListLinkedDouble::attach(Node* node, Node* position) {
    node->prev = position->prev;
    node->next = position;
    position->prev->next = node;
    position->prev = node;
}

void ListLinkedDouble::zip(ListLinkedDouble& other) { //O(n+m) con n el tamaño de la lista this, m el tamaño de other
    Node *current = this->head->next->next; 
    Node* current_other = other.head->next; 
    while(current != head && current_other != head) {
        Node*siguiente = current->next; 
        Node*siguiente_other = current_other->next; 
        attach(current_other, current); 
        current = siguiente; 
        current_other = siguiente_other;         
    }
    other.head->next = other.head; 
    other.head->prev = other.head; 

    this->num_elems += other.num_elems; 
    other.num_elems = 0; 
}

void resuelveCasos() {
    int n,m;
    cin >> n;
  
    ListLinkedDouble l1, l2;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        l1.push_back(a);
    }
    cin >> m; 
    for (int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        l2.push_back(a);
    }
    l1.zip(l2); 
    l1.display();
    cout << '\n';
}

int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) resuelveCasos(); 
    return 0;
}


#endif

*/

