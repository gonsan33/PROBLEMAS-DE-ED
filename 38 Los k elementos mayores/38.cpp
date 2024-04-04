/*
 * Implementaci�n del TAD Conjunto mediante �rboles binarios de b�squeda
 *
 * Versi�n inicial
 */


#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std; 
template <typename T> class SetTree {
public:
    SetTree() : root_node(nullptr), num_elems(0) {}
    SetTree(const SetTree& other)
        : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
    ~SetTree() { delete_nodes(root_node); }

    void insert(const T& elem) {
        auto [new_root, inserted] = insert(root_node, elem);
        root_node = new_root;
        if (inserted) {
            num_elems++;
        }
    }

    bool contains(const T& elem) const { return search(root_node, elem); }

    void erase(const T& elem) {
        auto [new_root, removed] = erase(root_node, elem);
        root_node = new_root;
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

    T min() const {
        return this->min(this->root_node); 
    }
    void erase_min() {
        auto [parent, current] = minNode(root_node); 
        if (parent == nullptr) { //es la ra�z
            root_node = current->right;
        }
        
        else { //tiene hijos
            parent->left = current->right; 
        }
        delete current; 
        --num_elems; 
    }

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right)
            : left(left), elem(elem), right(right) {}
    };

    Node* root_node;
    int num_elems;

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

    static std::pair<Node*, bool> insert(Node* root, const T& elem) {
        if (root == nullptr) {
            return { new Node(nullptr, elem, nullptr), true };
        }
        else if (elem < root->elem) {
            auto [new_root_left, inserted] = insert(root->left, elem);
            root->left = new_root_left;
            return { root, inserted };
        }
        else if (root->elem < elem) {
            auto [new_root_right, inserted] = insert(root->right, elem);
            root->right = new_root_right;
            return { root, inserted };
        }
        else {
            return { root, false };
        }
    }

    static bool search(const Node* root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (elem == root->elem) {
            return true;
        }
        else if (elem < root->elem) {
            return search(root->left, elem);
        }
        else {
            return search(root->right, elem);
        }
    }

    static std::pair<Node*, bool> erase(Node* root, const T& elem) {
        if (root == nullptr) {
            return { root, false };
        }
        else if (elem < root->elem) {
            auto [new_root_left, erased] = erase(root->left, elem);
            root->left = new_root_left;
            return { root, erased };
        }
        else if (root->elem < elem) {
            auto [new_root_right, erased] = erase(root->right, elem);
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

    const T& min(Node* root) const { //devuelve un puntero al nodo con el menor elemento del conjunto. Precondici�n: el �rbol no es vac�o
        if (root->left == nullptr) return root->elem;
        else return min(root->left); 
    }

    pair<Node*, Node*> minNode(Node* root) { //el primer elemento lleva el predecesor del nodo, el segundo el nodo. Precondici�n: el �rbol no es vac�o
        if (root->left == nullptr) return { nullptr, root }; 
        else {
            pair<Node*, Node*> res = minNode(root->left); 
            return { root->left == res.second ? root : res.first, res.second }; 
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}
template <typename T>
void resolver(const T& fin) {
    int k; 
    cin >> k; 
    vector<T> sol;
    SetTree<T> t; 
    T aux; 
    cin >> aux; 
    while (aux != fin) {
        t.insert(aux); 
        cin >> aux; 
        if (t.size() > k) t.erase_min(); 
    }

    
    //tengo los k elementos mayores, los saco por pantalla
    while (!t.empty()) {
        sol.push_back(t.min()); 
        t.erase_min(); 
    }
    
    cout << '{' << sol[0];
    for (int i = 1; i < k; ++i) {
        cout <<',' << ' ' << sol[i];
    }

    cout <<'}' << '\n';
}


bool resuelveCasos() {
    char c; 
    cin >> c;
    if (!cin) return false; 
    if (c == 'N') resolver<int>(-1);
    else if (c == 'P')resolver<string>("FIN");
    return true; 
}

int main() {
    while (resuelveCasos()); 
    return 0; 
}
