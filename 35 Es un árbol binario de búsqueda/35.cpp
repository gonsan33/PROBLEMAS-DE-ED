/*
 * Aquí se introducen los recorridos parametrizados con respecto
 * al tipo de acción que se desea realizar en cada visita.
 */

#ifndef __BINTREE_H
#define __BINTREE_H

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <climits>
#include <tuple>
using namespace std; 

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const { inorder(root_node, func); }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
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

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void inorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

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
tuple<bool,T,T> esDeBusquedaPrivi(const BinTree<T>& tree) { //es_abb,min,max
    if (tree.empty()) return {true, T(), T()};
    else {
        auto [es_abbL, minL, maxL] = esDeBusquedaPrivi(tree.left()); 
        auto [es_abbR, minR, maxR] = esDeBusquedaPrivi(tree.right());

        T min = tree.left().empty() ? tree.root() : minL; 
        T max = tree.right().empty() ? tree.root() : maxR; 

        return { es_abbL && es_abbR && (tree.left().empty() ||  maxL < tree.root()) && (tree.right().empty() ||  tree.root() < minR), min, max };
    }
}



template <typename T>
bool esDeBusqueda(const BinTree<T>& tree) {
    auto [esABB, min, max] = esDeBusquedaPrivi(tree);
    return esABB;
}

template <typename T>
void resolver() {
    BinTree<T> tree;
    cin >> tree;
    if (esDeBusqueda<T>(tree)) cout << "SI\n";
    else cout << "NO\n";
}

bool resuelveCasos() {
    char ini; 
    cin >> ini; 
    if (!cin) return false; 
    if (ini == 'N') {
        resolver<int>();         
    }
    else {
        resolver<string>();
    }
    return true; 
}

int main() {
    while (resuelveCasos()); 
    return 0; 
}

//Otra opción es ver si está ordenado el inorden
//Intentar esto con una expresión lambda
#endif