/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
  Estudiante 1: Nombre y Apellidos
  Estudiante 2: Nombre y Apellidos
 
  Dad una explicación de la solución y justificad el coste del
  nuevo método.

 *@ </answer> */

/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */

#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedDouble {
private:
   struct Node {
      int value;
      Node *next;
      Node *prev;
   };
   
public:
   ListLinkedDouble() : num_elems(0) {
      head = new Node;
      head->next = head;
      head->prev = head;
   }
   
   ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
      copy_nodes_from(other);
      num_elems = other.num_elems;
   }
   
   ~ListLinkedDouble() { delete_nodes(); }
   
   void push_front(const int &elem) {
      Node *new_node = new Node{elem, head->next, head};
      head->next->prev = new_node;
      head->next = new_node;
      num_elems++;
   }
   
   void push_back(const int &elem) {
      Node *new_node = new Node{elem, head, head->prev};
      head->prev->next = new_node;
      head->prev = new_node;
      num_elems++;
   }
   
   void pop_front() {
      assert(num_elems > 0);
      Node *target = head->next;
      head->next = target->next;
      target->next->prev = head;
      delete target;
      num_elems--;
   }
   
   void pop_back() {
      assert(num_elems > 0);
      Node *target = head->prev;
      target->prev->next = head;
      head->prev = target->prev;
      delete target;
      num_elems--;
   }
   
   int size() const { return num_elems; }
   
   bool empty() const { return num_elems == 0; };
   
   const int &front() const {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   int &front() {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   const int &back() const {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   int &back() {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   const int &operator[](int index) const {
      assert(0 <= index && index < num_elems);
      Node *result_node = nth_node(index);
      return result_node->value;
   }
   
   int &operator[](int index) {
      assert(0 <= index && index < num_elems);
      Node *result_node = nth_node(index);
      return result_node->value;
   }
   
   ListLinkedDouble &operator=(const ListLinkedDouble &other) {
      if (this != &other) {
         delete_nodes();
         head = new Node;
         head->next = head->prev = head;
         copy_nodes_from(other);
         num_elems = other.num_elems;
      }
      return *this;
   }
   
   void display(std::ostream &out) const;
   
   void display() const {
      display(std::cout);
   }
   
   void display_reverse(std::ostream &out) const;
   
   void display_reverse() const {
      display_reverse(std::cout);
   }
   
   // Nuevo método. Debe implementarse abajo
   void unzip(ListLinkedDouble &other); //O(n), con n el número de elementos de la lista
   
private:
   Node *head;
   int num_elems;
   
   Node *nth_node(int n) const;
   void delete_nodes();
   void copy_nodes_from(const ListLinkedDouble &other);
   void dettach(Node* node);
   void attach(Node* node, Node* position);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
   int current_index = 0;
   Node *current = head->next;
   
   while (current_index < n && current != head) {
      current_index++;
      current = current->next;
   }
   
   return current;
}

void ListLinkedDouble::delete_nodes() {
   Node *current = head->next;
   while (current != head) {
      Node *target = current;
      current = current->next;
      delete target;
   }
   
   delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
   Node *current_other = other.head->next;
   Node *last = head;
   
   while (current_other != other.head) {
      Node *new_node = new Node{current_other->value, head, last};
      last->next = new_node;
      last = new_node;
      current_other = current_other->next;
   }
   head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
   out << "[";
   if (head->next != head) {
      out << head->next->value;
      Node *current = head->next->next;
      while (current != head) {
         out << ", " << current->value;
         current = current->next;
      }
   }
   out << "]";
}

void ListLinkedDouble::display_reverse(std::ostream &out) const {
   out << "[";
   if (head->prev != head) {
      out << head->prev->value;
      Node *current = head->prev->prev;
      while (current != head) {
         out << ", " << current->value;
         current = current->prev;
      }
   }
   out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
   l.display(out);
   return out;
}



// ----------------------------------------------------------------
// ¡No modificar nada por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

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

void ListLinkedDouble::unzip(ListLinkedDouble & other) {//O(n), con n el número de elementos de la lista
    Node* current = head->next; 
    int i = 0; 
    while (i < this->num_elems) {
        Node* siguiente = current->next; 
        if (i % 2 == 1) {
            this->dettach(current);
            other.attach(current, other.head); 
        }
        ++i; 
        current = siguiente; 
    }
    //Modificar el número de elementos
    other.num_elems += num_elems / 2; 
    this->num_elems = num_elems + num_elems % 2; 
}

using namespace std;

ListLinkedDouble leerLista() {
  ListLinkedDouble lista;
  int num;
  cin >> num;
  while (num != 0) {
    lista.push_back(num);
    cin >> num;
  }
  return lista;
}


void resuelveCaso() {
  auto lista1 = leerLista();
  auto lista2 = leerLista();
  
  lista1.unzip(lista2);
  
//  for (int i = 0; i < lista1.size(); ++i) {
//     auto elem = lista1.front(); lista1.pop_front();
//     lista1.push_back(elem);
//  }

  std::cout << lista1 << '\n';
  std::cout << lista2 << '\n';
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
  int casos;
  cin >> casos;
  while (casos--) {
     resuelveCaso();
  }

   
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   // Descomentar si se necesita
   // system("PAUSE");
#endif
   
   return 0;
}


