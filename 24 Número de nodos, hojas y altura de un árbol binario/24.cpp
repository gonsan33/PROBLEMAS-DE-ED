/*
 * Esta implementaci�n utiliza smart pointers para prevenir
 * fugas de memoria y problemas con la destrucci�n.
 */

/*

#include <cassert>
#include <iostream>
#include <memory>
using namespace std; 
template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definici�n de NodePointer,
    // que TreeNode va a ser definida m�s adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}
template <typename T>
std::istream& operator>>(std::istream& op,  BinTree<T>& tree) {
    tree = read_tree<T>(op);
    return op;
}
template <typename T>
int numero_nodos(const BinTree<T>& tree) {
    if (tree.empty()) return 0;
    else return numero_nodos(tree.left()) + numero_nodos(tree.right()) + 1;
}
template <typename T>
int altura(const BinTree<T>& tree) {
    if (tree.empty()) return 0;
    else return max(altura(tree.left()), altura(tree.right())) + 1;
}
template <typename T>
int numero_hojas(const BinTree<T>& tree) {
    if (tree.empty()) return 0; 
    if (tree.left().empty() && tree.right().empty()) return 1;
    else return (tree.left().empty() ? 0 : numero_hojas(tree.left())) + (tree.right().empty() ? 0 : numero_hojas(tree.right())); 
}

void resuelveCasos() {
    BinTree<char> t; 
    cin >> t; 
    cout << numero_nodos(t) << ' ' << numero_hojas(t) << ' ' << altura(t) << '\n';
}

int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) resuelveCasos(); 
    return 0; 
}


*/