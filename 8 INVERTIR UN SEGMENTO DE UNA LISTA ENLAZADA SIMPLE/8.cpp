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
	void duplicateIter();
	Node* duplicate(Node* node);
	Node* invertir(Node*& act, Node*& ant);


public:
	ListLinkedList() : head(nullptr) {}
	~ListLinkedList() {

	}
	void push_front(int elem);
	void push_back(int elem);
	void pop_front(int elem);
	void pop_back(int elem);
	void invertirIter();


	Node* last_node() const;

	const int& front() const;
	int& front();

	const int& at(int index) const;
	int& at(int index);

	int size() const;

	bool empty() const;

	void display(std::ostream& out = cout) const;

	void duplicate();

	void invertir();

	void reverse_segment(int index, int lenght) {
		Node* pred_ini; 
		if (index > 0) {
			pred_ini = nth_node(index - 1);
			Node* ini = pred_ini->next;


			Node* ulti = nth_node(ini, lenght);

			Node* siguiente_de_ulti = ulti->next;
			ulti->next = nullptr;
			pred_ini->next = invertir(ini->next, ini);
			ini->next = siguiente_de_ulti;

		}

		else {
			Node* ini = head;

			Node* ulti = nth_node(lenght);
			Node* siguiente_de_ulti = ulti->next;
			ulti->next = nullptr;
			head = invertir(ini->next, ini);
			ini->next = siguiente_de_ulti;


		}
			
		
		



	}
	Node* nth_node(Node* ini, int n) const {
		assert(0 <= n);
		int current_index = 0;
		Node* current = ini; 
		while (current_index < n && current != nullptr) {
			++current_index;
			current = current->next;
		}
		return current;
	}

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

ListLinkedList::Node* ListLinkedList::duplicate(ListLinkedList::Node* node) { //Coste lineal en el tama�o de la lista. 
	if (node == nullptr) return nullptr;
	else {
		node->next = new Node{ node->value,duplicate(node->next) };
		return node;
	}
}

void ListLinkedList::duplicateIter() { //Coste lineal en el tama�o de la lista. 
	Node* actual = head;
	while (actual != nullptr) {
		head->next = new Node{ actual->value, head->next };
		actual = actual->next->next;
	}

}

ListLinkedList::Node* ListLinkedList::invertir(ListLinkedList::Node*& act, ListLinkedList::Node*& ant) {
	if (act->next == nullptr) {
		act->next = ant;
		return act;
	}
	else {
		Node* resultado = invertir(act, act->next);
		act->next = ant;
		return resultado;
	}
}
void ListLinkedList::invertirIter() {
	//head apunta al �ltimo elemento invertido
	Node* actual = head;
	Node* inicial = this->head; 
	while (actual != nullptr) {
		Node* mueve = actual;
		actual = actual->next;
		mueve->next = head;
		head = mueve;
	}
	inicial->next = nullptr; 
}


void ListLinkedList::invertir() {//Coste lineal en el tama�o de la lista
	if (head != nullptr) {
		Node* new_head = invertir(head, head->next);
		head->next = nullptr;
		head = new_head;
	}
}


bool  resuelveCasos() {
	ListLinkedList list;
	int num;
	cin >> num;
	if (!cin) return false; 
	int index = 0 , length = 0;
	cin >> index >> length; 
	for (int i = 0; i < num; ++i) {
		int elem; 
		cin >> elem; 
		list.push_back(elem); 
	}
	list.invertirIter(); 
	list.display();
	cout << '\n';
	return true; 
}



int main() {
	while(resuelveCasos());
	return 0;
}

*/


