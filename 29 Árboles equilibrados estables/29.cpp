/*
 * Esta implementación utiliza smart pointers para prevenir
 * fugas de memoria y problemas con la destrucción.
 */



#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
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

    bool complete() const {
        return completo(root_node).first;
    }

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

    pair<bool, int> completo(NodePointer root) const {
        if (root == nullptr) return { true,0 };
        else {
            bool condition = (root->left != nullptr && root->right != nullptr) || (root->left == nullptr && root->right == nullptr);
            pair<bool, int> primero = { false,0 };
            if (condition)primero = completo(root->left);
            pair<bool, int> segundo = { false,0 };
            if (condition && primero.first) segundo = completo(root->right);

            return { primero.first && segundo.first && condition && primero.second == segundo.second, primero.second + 1 };
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

// {rta, hmin, hmax, }
template<typename T>
tuple<bool, int, int> estable(const BinTree<T>& tree) {
    if (tree.empty()) return make_tuple(true, 0, 0);
    else if (tree.left().empty() && tree.right().empty()) return make_tuple(true, 0, 1);
    else {
        auto left = estable(tree.left());
        auto right = estable(tree.right());
        bool estable = get<0>(left) && get<0>(right) && abs(get<1>(left) - get<2>(right)) <= 1 && abs(get<1>(right) - get<2>(left)) <= 1;
        int hmin = min(max(get<1>(left), get<2>(right)) , max(get<1>(right), get<2>(left))) + 1;
        int hmax = max(get<2>(left), get<2>(right)) + 1;
        return make_tuple(estable, hmin, hmax);

    }
}




void resuelveCaso() {
    BinTree<int> t;
    cin >> t;
    auto rta = estable(t);
    if (get<0>(rta)) cout << "SI\n";
    else cout << "NO\n"; 
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) resuelveCaso();
    return 0;
}