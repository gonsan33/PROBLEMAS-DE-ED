/*
 * Implementación inicial del TAD de los árboles binarios.
 *
 * Cuidado: ˇEsta implementación no libera la memoria que reserva!
 */

/*

#include <cassert>
#include <iostream>
using namespace std; 
template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}
    BinTree(const T& elem) : root_node(new TreeNode(nullptr, elem, nullptr)) {}
    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(new TreeNode(left.root_node, elem, right.root_node)) {}

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
    struct TreeNode {
        T elem;
        TreeNode* left, * right;

        TreeNode(TreeNode* left, const T& elem, TreeNode* right)
            : elem(elem), left(left), right(right) {}
    };

    TreeNode* root_node;

    static void display_node(const TreeNode* root, std::ostream& out) {
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
std::istream& operator>>(std::istream& op, BinTree<T>& tree) {
    tree = read_tree<T>(op);
    return op;
}


template <typename T> 
//first lleva la altura, second el diámetro del árbol
pair<int, int> diametro(const BinTree<T>& tree) {
    if (tree.empty()) return { 0,0 }; 
    else {
        auto izq = diametro(tree.left()); 
        auto dcha = diametro(tree.right()); 
        return { max(izq.first, dcha.first) + 1, max(izq.first + dcha.first +1, max(izq.second, dcha.second))};
    }
}

void resuelveCasos() {
    BinTree<char> t;
    cin >> t; 
    cout << diametro(t).second << '\n'; 
    
}


int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) resuelveCasos(); 
    return 0; 
}
*/