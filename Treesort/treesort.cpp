#include <iostream>
#include <iomanip>
using namespace std; 
/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Conjunto mediante árboles binarios de búsqueda.
  *
  * Esta versión añade iteradores.
  */

#ifndef __SET_TREE_H
#define __SET_TREE_H

#include <cassert>
#include <iostream>
#include <stack>

template <typename T, typename ComparatorFunction = std::less<T>>
class SetTree {

private:
    struct Node;

public:
    SetTree(ComparatorFunction less_than)
        : root_node(nullptr), num_elems(0), less_than(less_than) {}
    SetTree() : root_node(nullptr), num_elems(0) {}
    SetTree(const SetTree& other)
        : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
    ~SetTree() { delete_nodes(root_node); }

    void insert(const T& elem) {
        bool inserted = insert(root_node, elem);
        if (inserted) {
            num_elems++;
        }
    }

    bool contains(const T& elem) const { return search(root_node, elem); }

    void erase(const T& elem) {
        bool removed = erase(root_node, elem);
        if (removed) {
            num_elems--;
        }
    }

    int size() const { return num_elems; }
    bool empty() const { return num_elems == 0; }

    SetTree& operator=(const SetTree& other) {
        if (this != &other) {
            num_elems = other.num_elems;
            delete_nodes(root_node);
            root_node = copy_nodes(other.root_node);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        display(root_node, out);
        out << "}";
    }

    class iterator {
    public:
        const T& operator*() const {
            assert(!st.empty());
            return st.top()->elem;
        }

        const T* operator->() const { return &operator*(); }

        iterator& operator++() {
            assert(!st.empty());
            Node* top = st.top();
            st.pop();
            descend_and_push(top->right, st);
            return *this;
        }

        iterator operator++(int) {
            iterator previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const iterator& other) { return st == other.st; }

        bool operator!=(const iterator& other) { return !this->operator==(other); }

    private:
        friend class SetTree;

        iterator() {}

        iterator(Node* root) { descend_and_push(root, st); }

        std::stack<Node*> st;
        static void descend_and_push(Node* node, std::stack<Node*>& st) {
            Node* current = node;
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
        }
    };

    iterator begin() const { return iterator(root_node); }

    iterator end() const { return iterator(); }

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right)
            : left(left), elem(elem), right(right) {}
    };

    Node* root_node;
    int num_elems;

    ComparatorFunction less_than;

    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->elem,
                copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    bool insert(Node*& root, const T& elem) {
        if (root == nullptr) {
            root = new Node(nullptr, elem, nullptr);
            return true;
        }
        else if (less_than(elem, root->elem)) {
            return insert(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return insert(root->right, elem);
        }
        else {
            return false;
        }
    }

    bool search(const Node* root, const T& elem) const {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return search(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return search(root->right, elem);
        }
        else {
            return true;
        }
    }

    bool erase(Node*& root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return erase(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return erase(root->right, elem);
        }
        else {
            remove_root(root);
            return true;
        }
    }

    static void remove_root(Node*& root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            root = nullptr;
        }
        else if (left_child == nullptr) {
            root = right_child;
        }
        else if (right_child == nullptr) {
            root = left_child;
        }
        else {
            Node* lowest = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = right_child;
            root = lowest;
        }
    }

    static Node* remove_lowest(Node*& root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            Node* result = root;
            root = root->right;
            return result;
        }
        else {
            return remove_lowest(root->left);
        }
    }

    static void display(Node* root, std::ostream& out) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                display(root->left, out);
                out << ", ";
            }
            out << root->elem;
            if (root->right != nullptr) {
                out << ", ";
                display(root->right, out);
            }
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}

/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Diccionario mediante árboles binarios
  * de búsqueda.
  *
  * Esta versión incorpora iteradores.
  */

#ifndef __MAP_TREE_H
#define __MAP_TREE_H

#include <cassert>
#include <iostream>
#include <stack>
#include <tuple>
#include <utility>

template <typename K, typename V, typename ComparatorFunction = std::less<K>>
class MapTree {
private:
    template <typename S> class iterator_gen;

public:
    struct MapEntry {
        const K key;
        V value;

        MapEntry(K key, V value) : key(key), value(value) {}
        MapEntry(K key) : key(key), value() {}
    };

    using const_iterator = iterator_gen<const MapEntry>;
    using iterator = iterator_gen<MapEntry>;

    MapTree() : root_node(nullptr), num_elems(0) {}
    MapTree(ComparatorFunction less_than)
        : root_node(nullptr), num_elems(0), less_than(less_than) {}
    MapTree(const MapTree& other)
        : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
    ~MapTree() { delete_nodes(root_node); }

    void insert(const MapEntry& entry) {
        auto [new_root, inserted] = insert(root_node, entry);
        this->root_node = new_root;
        if (inserted) {
            num_elems++;
        }
    }

    bool contains(const K& key) const {
        return search(root_node, key) != nullptr;
    }

    const V& at(const K& key) const {
        Node* result = search(root_node, key);
        assert(result != nullptr);
        return result->entry.value;
    }

    V& at(const K& key) {
        Node* result = search(root_node, key);
        assert(result != nullptr);
        return result->entry.value;
    }

    V& operator[](const K& key) {
        auto [inserted, new_root, found_node] = search_or_insert(root_node, key);
        this->root_node = new_root;
        if (inserted)
            num_elems++;
        return found_node->entry.value;
    }

    void erase(const K& key) {
        auto [new_root, erased] = erase(root_node, key);
        this->root_node = new_root;
        if (erased) {
            num_elems--;
        }
    }

    int size() const { return num_elems; }
    bool empty() const { return num_elems == 0; }

    MapTree& operator=(const MapTree& other) {
        if (this != &other) {
            num_elems = other.num_elems;
            delete_nodes(root_node);
            root_node = copy_nodes(other.root_node);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        display(root_node, out);
        out << "}";
    }

    iterator begin() { return iterator(root_node); }

    iterator end() { return iterator(); }

    const_iterator begin() const { return const_iterator(root_node); }

    const_iterator end() const { return const_iterator(); }

    const_iterator cbegin() { return const_iterator(root_node); }

    const_iterator cend() { return const_iterator(); }

private:
    struct Node {
        MapEntry entry;
        Node* left, * right;

        Node(Node* left, const MapEntry& entry, Node* right)
            : left(left), entry(entry), right(right) {}
    };

    Node* root_node;
    int num_elems;
    ComparatorFunction less_than;

    template <typename S> class iterator_gen {
    public:
        S& operator*() const {
            assert(!st.empty());
            return st.top()->entry;
        }

        S* operator->() const { return &operator*(); }

        iterator_gen& operator++() {
            assert(!st.empty());
            Node* top = st.top();
            st.pop();
            descend_and_push(top->right, st);
            return *this;
        }

        iterator_gen operator++(int) {
            iterator_gen previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const iterator_gen& other) { return st == other.st; }

        bool operator!=(const iterator_gen& other) {
            return !this->operator==(other);
        }

    private:
        friend class MapTree;

        iterator_gen() {}

        iterator_gen(Node* root) { descend_and_push(root, st); }

        std::stack<Node*> st;

        static void descend_and_push(Node* node, std::stack<Node*>& st) {
            Node* current = node;
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
        }
    };

    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->entry,
                copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    std::pair<Node*, bool> insert(Node* root, const MapEntry& elem) {
        if (root == nullptr) {
            return { new Node(nullptr, elem, nullptr), true };
        }
        else if (less_than(elem.key, root->entry.key)) {
            auto [new_root_left, inserted] = insert(root->left, elem);
            root->left = new_root_left;
            return { root, inserted };
        }
        else if (less_than(root->entry.key, elem.key)) {
            auto [new_root_right, inserted] = insert(root->right, elem);
            root->right = new_root_right;
            return { root, inserted };
        }
        else {
            return { root, false };
        }
    }

    std::tuple<bool, Node*, Node*> search_or_insert(Node* root, const K& key) {
        if (root == nullptr) {
            Node* new_node = new Node(nullptr, { key }, nullptr);
            return { true, new_node, new_node };
        }
        else if (less_than(key, root->entry.key)) {
            auto [inserted, new_root, found_node] = search_or_insert(root->left, key);
            root->left = new_root;
            return { inserted, root, found_node };
        }
        else if (less_than(root->entry.key, key)) {
            auto [inserted, new_root, found_node] =
                search_or_insert(root->right, key);
            root->right = new_root;
            return { inserted, root, found_node };
        }
        else {
            return { false, root, root };
        }
    }

    std::pair<Node*, bool> erase(Node* root, const K& key) {
        if (root == nullptr) {
            return { root, false };
        }
        else if (less_than(key, root->entry.key)) {
            auto [new_root_left, erased] = erase(root->left, key);
            root->left = new_root_left;
            return { root, erased };
        }
        else if (less_than(root->entry.key, key)) {
            auto [new_root_right, erased] = erase(root->right, key);
            root->right = new_root_right;
            return { root, erased };
        }
        else {
            return { remove_root(root), true };
        }
    }

    static Node* remove_root(Node* root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            return nullptr;
        }
        else if (left_child == nullptr) {
            return right_child;
        }
        else if (right_child == nullptr) {
            return left_child;
        }
        else {
            auto [lowest, new_right_root] = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = new_right_root;
            return lowest;
        }
    }

    static std::pair<Node*, Node*> remove_lowest(Node* root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            return { root, root->right };
        }
        else {
            auto [removed_node, new_root_left] = remove_lowest(root->left);
            root->left = new_root_left;
            return { removed_node, root };
        }
    }

    Node* search(Node* root, const K& key) const {
        if (root == nullptr) {
            return nullptr;
        }
        else if (less_than(key, root->entry.key)) {
            return search(root->left, key);
        }
        else if (less_than(root->entry.key, key)) {
            return search(root->right, key);
        }
        else {
            return root;
        }
    }

    static void display(Node* root, std::ostream& out) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                display(root->left, out);
                out << ", ";
            }
            out << root->entry.key << " -> " << root->entry.value;
            if (root->right != nullptr) {
                out << ", ";
                display(root->right, out);
            }
        }
    }
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const MapTree<K, V>& map) {
    map.display(out);
    return out;
}

#endif

template <typename T> 
void tree_sort(vector<T>& elems) { //coste O(nlogn) si el árbol está equilibrado, O(n^2) si es degenerado
    SetTree<T> set; 
    for (T e : elems) set.insert(e); 

    int i = 0 ; 
    for (T e : set) {
        elems[i] = e; 
        ++i; 
    }
}

template <typename T>
void tree_sort(vector<T>& elems) { //si el vector tiene repetidos 
    //coste O(nlogn) si el árbol está equilibrado, O(n^2) si es degenerado
    MapTree<T, int> mult; 
    for (T e : elems) ++mult[e]; 
    int i = 0; 
    for (auto& [elem, m] : mult) {
        for (int j = 0; j < m; ++j) {
            elems[i++] = e; 
        }
    }
}

#endif
