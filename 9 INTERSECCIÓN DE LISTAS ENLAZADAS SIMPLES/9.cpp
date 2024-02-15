#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

/*
class ListLinkedList {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;
	Node* nth_node(int n) const;
	void delete_list(Node* start_node);
	Node* duplicate(Node* node);

public:
	ListLinkedList() : head(nullptr) {}
	~ListLinkedList() {

	}
	void push_front(int elem);
	void push_back(int elem);
	void pop_front(int elem);
	void pop_back(int elem);


	Node* last_node() const;

	const int& front() const;
	int& front();

	const int& at(int index) const;
	int& at(int index);

	int size() const;

	bool empty() const;

	void display(std::ostream& out = cout) const;

	void duplicate();

	void intersect(const ListLinkedList& other);

};

void ListLinkedList::delete_list(ListLinkedList::Node* start_node) {
	if (start_node != nullptr) {
		delete_list(start_node->next);
		delete start_node;
	}
}
ListLinkedList::Node* ListLinkedList::nth_node(int n) const {
	assert(0 <= n);
	int current_index = 0;
	Node* current = head;
	while (current_index < n && current != nullptr) {
		++current_index;
		current = current->next;
	}
	return current;
}

void ListLinkedList::push_front(int elem) {
	head = new Node{ elem, head };
}
void ListLinkedList::push_back(int elem) {
	if (head == nullptr) head = new Node{ elem, nullptr };
	else {
		this->last_node()->next = new Node{ elem, nullptr };
	}
}
void ListLinkedList::pop_front(int elem) {
	assert(head != nullptr);
	Node* old_head = head;
	head = head->next;
	delete old_head;
}
void ListLinkedList::pop_back(int elem) {
	assert(head != nullptr);
	if (head->next == nullptr) {//1 elem
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
		current = nullptr;
		previous->next = nullptr;
	}
}

ListLinkedList::Node* ListLinkedList::last_node() const {
	assert(head != nullptr);
	Node* current = head;
	while (current->next != nullptr) current = current->next;
	return current;
}

const int& ListLinkedList::front() const {
	assert(head != nullptr);
	return head->value;
}
int& ListLinkedList::front() {
	assert(head != nullptr);
	return head->value;
}

const int& ListLinkedList::at(int index) const {
	Node* result_node = nth_node(index);
	assert(result_node != nullptr);
	return result_node->value;
}
int& ListLinkedList::at(int index) {
	Node* result_node = nth_node(index);
	assert(result_node != nullptr);
	return result_node->value;
}

int ListLinkedList::size() const {
	int num_nodes = 0;
	Node* current = head;
	while (current != nullptr) {
		++num_nodes;
		current = current->next;
	}
	return num_nodes;
}

bool ListLinkedList::empty() const {
	return head == nullptr;
}

void ListLinkedList::display(std::ostream& out) const {
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

void ListLinkedList::duplicate() {
	head = duplicate(head);
}

ListLinkedList::Node* ListLinkedList::duplicate(ListLinkedList::Node* node) { //Coste lineal en el tamaño de la lista. 
	if (node == nullptr) return nullptr;
	else {
		node->next = new Node{ node->value,duplicate(node->next) };
		return node;
	}
}

void resuelveCasos() {
	ListLinkedList list1;
	ListLinkedList list2;
	int n,m;
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

	list1.intersect(list2); 
	list1.display();
	cout << '\n';
}




void ListLinkedList::intersect(const ListLinkedList& other) { //Coste lineal en la suma del número de elementos de ambas listas. O(n+m) n = this.size(), m = other.size()
	Node* current = head; 
	Node* curr_other = other.head;
	Node* previous = nullptr; 
	//Invariante: todos los elementos de la lista this, hasta el elemento que estoy mirando, están también en la lista other. 
	//previous lleva el antecesor de current
	while (current != nullptr && curr_other != nullptr) {
		if (current->value < curr_other->value) {
			//Hay que eliminar el elemento current: 
			Node* aux = current->next; 
			delete current;
			if (previous == nullptr) head = aux;
			else previous->next = aux; 
			current = aux;
		}
		else if (current->value == curr_other->value) {
			previous = current; 
			current = current->next;
			curr_other = curr_other->next; 
		}
		else {
			if (curr_other->next == nullptr) {
				Node* aux = current->next;
				delete current;
				if (previous == nullptr) head = aux;
				else previous->next = aux;
				current = aux;
			}
			curr_other = curr_other->next;
		}

	}

	//Se eliminan los demás elementos: 
	if(previous!= nullptr) previous->next = nullptr; 
	delete_list(current); 
		



	
	
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) resuelveCasos();
	return 0;
}
*/
