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
const T & minimum(const BinTree<T>& tree) {
    if (tree.left().empty() && tree.right().empty()) return tree.root();
    else if (tree.left().empty()) return min(minimum(tree.right()), tree.root()); 
    else if(tree.right().empty()) return min(minimum(tree.left()), tree.root());
    else return min(minimum(tree.left()), min(tree.root(), minimum(tree.right())));
}

template <typename T>
void resolver() {
    BinTree<T> t; 
    cin >> t; 
    cout << minimum(t) << '\n'; 
}

bool resuelveCaso() {
    char letra; 
    cin >> letra; 
    if (!cin) return false; 
    else {
        if (letra == 'N') resolver<int>();
        else resolver<string>(); 

        return true; 
    }
}

int main() {
    while (resuelveCaso()); 
    return 0; 
}