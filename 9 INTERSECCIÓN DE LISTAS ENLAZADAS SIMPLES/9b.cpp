/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
  */

  /*@ <answer>
   *  Estudiante 1: Nombre y Apellidos
   *  Estudiante 2: Nombre y Apellidos
   *@ </answer> */

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Nuevo m�todo. Debe implementarse abajo
    void merge(ListLinkedSingle& l2);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;

    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

// ----------------------------------------------------------------
// �No modificar nada por encima de esta l�nea!

// Implementa a continuaci�n el m�todo pedido.
//@ <answer>

void ListLinkedSingle::merge(ListLinkedSingle& l2) {
    Node* prev1 = nullptr; 
    Node* current1 = head; 
    Node* current2 = l2.head; 

    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value > current2->value) {
            current2 = current2->next; 
        }
        else if (current1->value == current2->value) {
            prev1 = current1;
            current1 = current1->next;
            current2 = current2->next; 
        }
        else { //elimino de la lista this
            if (prev1 == nullptr) {
                //tengo que mover head
                head = current1->next; 
                delete current1; 
                current1 = head; 
            }
            else {
                current1 = current1->next; 
                delete prev1->next; 
                prev1->next = current1; 
            }
        }

    }

    if (current1 != nullptr ) {
        if (prev1 != nullptr) prev1->next = nullptr;
        else head = nullptr; 
        this->delete_list(current1);
    }

}

// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

using namespace std;

ListLinkedSingle leerLista() {
    ListLinkedSingle lista;
    int n;
    std::cin >> n;
    while (n != 0) {
        lista.push_back(n);
        std::cin >> n;
    }
    return lista;
}

void resuelveCaso() {
    ListLinkedSingle list1;
    ListLinkedSingle list2;
    int n, m;
    cin >> n;
    int aux;
    for (int i = 0; i < n; ++i) {
        cin >> aux;
        list1.push_back(aux);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> aux;
        list2.push_back(aux);
    }

    list1.merge(list2);
    list1.display();
    cout << '\n';
}

int main() {


    // Leemos el n�mero de casos de prueba que vendr�n a continuaci�n
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }


    return 0;
}
