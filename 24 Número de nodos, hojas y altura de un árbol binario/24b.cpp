//Se implementan las operaciones dentro de la clase: 
/*
 * Esta implementación utiliza smart pointers para prevenir
 * fugas de memoria y problemas con la destrucción.
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

    int numero_nodos() const {
        return this->numero_nodos(root_node); 
    }

    int altura() const {
        return this->altura(root_node); 
    }
    int numero_hojas() const {
        return this->numero_hojas(root_node); 
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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

    int numero_nodos(NodePointer root) const {
        if (root == nullptr) return 0;
        else return 1 + numero_nodos(root->left) + numero_nodos(root->right); 
    }
    int altura(NodePointer root) const {
        if (root == nullptr) return 0;
        else return max(altura(root->left), altura(root->right)) + 1; 
    }
    int numero_hojas(NodePointer root) const {
        if (root == nullptr) return 0;
        else if (root->left == nullptr && root->right == nullptr) return 1; 
        else return (root->left == nullptr ? 0 : numero_hojas(root->left)) + (root->right == nullptr ? 0 : numero_hojas(root->right));
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
std::istream& operator>>(std::istream& op, BinTree<T>& tree) {
    tree = read_tree<T>(op);
    return op;
}


void resuelveCasos() {
    BinTree<char> t;
    cin >> t;
    cout << t.numero_nodos() << ' ' << t.numero_hojas() << ' ' << t.altura() << '\n';
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) resuelveCasos();
    return 0;
}
*/