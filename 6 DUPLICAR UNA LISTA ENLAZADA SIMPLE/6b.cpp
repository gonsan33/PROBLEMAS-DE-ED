#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { } //Constructora O(1)
    ~ListLinkedSingle() { //Destructora O(n) 
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) { //O(1)
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem); //O(n)

    void pop_front() { //O(1)
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back(); //O(n)

    int size() const; //O(n)

    bool empty() const { //O(1)
        return head == nullptr;
    };

    const int& front() const { //O(1)
        assert(head != nullptr);
        return head->value;
    }

    int& front() {//O(1)
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {//O(1)
        return last_node()->value;
    }

    int& back() {//O(1)
        return last_node()->value;
    }

    const int& at(int index) const { //O(n)
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) { //O(n)
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const; //O(n)
    void display() const { //O(n)
        display(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void reverse_segment(int index, int length); //O(n)

    void duplicate(); //O(n)

private:
    Node* head;

    void delete_list(Node* start_node); //O(n)
    Node* last_node() const; //O(n)
    Node* nth_node(int n) const; //O(n)
    Node* copy_nodes(Node* start_node) const; //O(n)

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const { //O(n)
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {//O(n)
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {//O(n)
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() { //O(n)
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

int ListLinkedSingle::size() const { //O(n)
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const { //O(n)
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const { //O(n)
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const { //O(n)
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

void ListLinkedSingle::reverse_segment(int index, int length) { //O(n)

    Node*& next_del_elem_previo = index == 0 ? head : this->nth_node(index - 1)->next;

    Node* actual = next_del_elem_previo;
    Node* ini = actual;

    int num = 0;

    while (actual != nullptr && num < length) {
        Node* mueve = actual;
        actual = actual->next;
        mueve->next = next_del_elem_previo;
        next_del_elem_previo = mueve;
        ++num;
    }

    ini->next = actual;

}


void ListLinkedSingle::duplicate() { //O(n)
    Node* current = head; 
    while (current != nullptr) {
        Node* old_curr = current; 
        current = current->next; 
        old_curr->next = new Node{ old_curr->value, current }; 
    }
}

void resuelveCasos() {
    ListLinkedSingle l; 
    int elem; 
    cin >> elem; 
    while (elem != 0) {
        l.push_back(elem); 
        cin >> elem; 
    }
    l.duplicate(); 
    l.display(); 
    cout << '\n'; 

   
}

int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) {
        resuelveCasos(); 
    }
    return 0; 
}



