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
    void dettach(Node* node);
    void attach(Node* node, Node* position);
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



void ListLinkedDouble::dettach(Node* node) {
    node->prev->next = node->next; 
    node->next->prev = node->prev; 
}

void ListLinkedDouble::attach(Node* node, Node* position) {
    node->prev = position->prev; 
    node->prev->next = node; 
    node->next = position; 
    position->prev = node; 
}

void ListLinkedDouble::zip(ListLinkedDouble& other) { //O(n+m) con n el tamaño de la lista this, m el tamaño de other
    Node* current = head->next; 
    Node* current_other = other.head->next; 
    while (current != head && current_other != other.head) {
        Node* old_curr_other = current_other; 
        current_other = current_other->next; 
        other.dettach(old_curr_other);
        current = current->next; 
        attach(old_curr_other, current);
    }
    while (current_other != other.head) {
        Node* old_curr_other = current_other;
        current_other = current_other->next;
        other.dettach(old_curr_other);
        attach(old_curr_other, head);
    }
}

void resuelveCasos() {
    int n, m; 
    cin >> n; 
    ListLinkedDouble l1; 
    for (int i = 0; i < n; ++i) {
        int elem; 
        cin >> elem; 
        l1.push_back(elem); 
    }
    cin >> m;
    ListLinkedDouble l2;
    for (int i = 0; i < m; ++i) {
        int elem;
        cin >> elem;
        l2.push_back(elem);
    }
    l1.zip(l2); 
    cout << l1 << '\n';
}


int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) {
        resuelveCasos(); 
    }
    return 0; 
}

#endif


