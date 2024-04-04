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

    bool empty() const { 
        return root_node == nullptr; 
    }

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

struct tSol {
    int altura; 
    int mellas; 
    bool mella_izq; 
    bool mella_dcha; 
    tSol(int altura,int mellas, bool mella_izq, bool mella_dcha ) : altura(altura), mellas(mellas), mella_izq(mella_izq), mella_dcha(mella_dcha) {}
};



template <typename T>
tSol calc_mellas(const BinTree<T>& t) {
    if (t.left().empty() && t.right().empty()) return tSol(1, 0, false, false);
    else if (t.left().empty()) return tSol(2, 1, true, false);
    else if (t.right().empty()) return tSol(2, 1, false, true); 
    else {
        tSol left = calc_mellas(t.left()); 
        tSol right = calc_mellas(t.right()); 

        int altura = 0, mellas = 0; 
        bool mella_izq = false, mella_dcha = false; 

        if (left.altura == right.altura) {
            altura = left.altura + 1; 
            mellas = left.mellas + right.mellas - (left.mella_dcha && right.mella_izq ? 1 : 0); 
            mella_izq = left.mella_izq; 
            mella_dcha = right.mella_dcha; 
        }
        else if (left.altura < right.altura) {
            //en este caso, a left le faltan 2^left.altura nodos, pero solo una mella, porque left ha de ser completo
            altura = right.altura + 1; 
            mellas = right.mellas + (right.mella_izq ? 0 : 1); 
            mella_izq = true; 
            mella_dcha = right.mella_dcha; 
        }
        else if (left.altura > right.altura) {
            altura = left.altura + 1;
            mellas = left.mellas + (left.mella_dcha ? 0 : 1);
            mella_dcha = true;
            mella_izq = left.mella_izq;
        }

        return tSol(altura, mellas, mella_izq, mella_dcha); 
        
    }
}

template <typename T>
int num_mellas(const BinTree<T>& t) {
    return calc_mellas(t).mellas; 
}
/*
template <typename T> 
int num_mellas(const BinTree<T>& t) {
    
    queue <pair<BinTree<T>,int>> q; 
    
    q.push({ t,1 });
   
    while (!q.front().first.left().empty() && !q.front().first.right().empty()) {
        auto [current,level] = q.front(); 
        q.pop(); 
        q.push({ current.left(),level + 1 });
        q.push({ current.right(),level + 1 });
    }

    //En la cola están los nodos del penúltimo nivel a partir del primero que no tiene hijos: 
    int n = 0; 
    bool anterior = false; 
    bool completo = true; 
    int lastlevel = q.front().second; 

    while (!q.empty()) {
        
        auto [current, level] = q.front();
        q.pop(); 
        if (level == lastlevel) {
            if (current.left().empty() && !anterior) ++n;
            if (current.right().empty() && !current.left().empty()) ++n;

            anterior = current.right().empty();

            completo &= current.left().empty() && current.right().empty();
        }
        else {
            n = 0; 
            anterior = false; 

            if (current.left().empty() && !anterior) ++n;
            if (current.right().empty() && !current.left().empty()) ++n;

            anterior = current.right().empty();

            completo &= current.left().empty() && current.right().empty();
        }
    }
    if (completo) n = 0; 
    return n; 


}
*/
void resuelveCasos() {
    BinTree<char> t; 
    cin >> t; 
    cout << num_mellas(t) << '\n'; 
}

int main() {
    int n; 
    cin >> n; 
    for (int i = 0; i < n; ++i) resuelveCasos(); 
    return 0; 
}

#endif