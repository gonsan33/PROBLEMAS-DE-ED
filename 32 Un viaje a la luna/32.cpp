#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;
public:
    Persona() : nombre(""), edad(0) {}
    Persona(const string& nombre, int edad) : nombre(nombre), edad(edad) {}
    const string& getNombre() const {
        return nombre;
    }
    int getEdad() const { return edad; }
    void read(istream& in) {
        in >> edad;
        in.ignore(1); 
        getline(in, nombre);
    }
    void display(ostream& op = cout) {
        op  << nombre;
    }



};



#include <cassert>
#include <iostream>

template <typename Elem>
class ListLinkedDouble {
private:
    struct Node {
        Elem value;
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

    void push_front(const Elem& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const Elem& elem) {
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

    template <typename Predicate>
    void remove_if(Predicate pred) {
        Node* current = head->next;
        while (current != head) {
            Node* aux = current;
            current = current->next;
            if (pred(aux->value)) {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                aux->next = nullptr;
                aux->prev = nullptr;
                delete aux;
                --num_elems;
            }

        }
    }


    const Elem& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    Elem& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const Elem& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    Elem& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const Elem& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    Elem& operator[](int index) {
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


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

template <typename Elem>
typename ListLinkedDouble<Elem>::Node*
ListLinkedDouble<Elem>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename Elem> void ListLinkedDouble<Elem>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename Elem>
void ListLinkedDouble<Elem>::copy_nodes_from(const ListLinkedDouble& other) {
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

template <typename Elem>
void ListLinkedDouble<Elem>::display(std::ostream& out) const {
    if (head->next != head) {
        out << head->next->value <<'\n';
        Node* current = head->next->next;
        while (current != head) {
            out << current->value << '\n';
            current = current->next;
        }
    }
}

template <typename Elem>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<Elem>& l) {
    l.display(out);
    return out;
}

std::istream& operator >> (std::istream& in, Persona& p) {
    p.read(in);
    return in;
}

std::ostream& operator << (std::ostream& op, Persona& p) {
    p.display(op);
    return op;
}


bool resuelveCasos() {
    int n, min, max;
    cin >> n >> min >> max;
    if (n == 0 && min == 0 && max == 0) return false;
    ListLinkedDouble<Persona> lista;

    Persona aux;
    for (int i = 0; i < n; ++i) {
        cin >> aux;
        lista.push_back(aux);
    }
    lista.remove_if([min, max](const Persona& p) {return (p.getEdad() < min || p.getEdad() > max);  });
    cout << lista;
    cout << "---\n";
    return true;
}

int main() {
    while (resuelveCasos());
    return 0;
}

