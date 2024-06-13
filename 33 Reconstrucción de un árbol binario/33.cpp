/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no ser� corregida.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos:
  //@ </answer>

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
#include <list>

/*
  Implementaci�n de la clase BinTree para representar �rboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

/*

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


using namespace std;
// ----------------------------------------------------------------
// �No modificar nada importante por encima de esta l�nea!

// Implementa a continuaci�n la funci�n pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer>






template <typename T> 
BinTree<T> reconstruir(int& preOrdIni, int preOrdFin, int inOrdIni, int inOrdFin, vector<T> const& preorden, vector<T> const& inorden) {
    if (inOrdIni >= inOrdFin) return BinTree<T>(); 
    else {
        T root = preorden[preOrdIni]; 

        ++preOrdIni; 
        
        //busco la ra�z en el inorden 
        int inOrdIzqFin = inOrdIni;
        while (inorden[inOrdIzqFin] != root) ++inOrdIzqFin; 

        //en el inorden, el �rbol izquierdo est� entre [inOrdIzqIni, inOrdIzqFin)

        //En el inorden, el �rbol derecho est� entre [inOrdIzqFin+1, inOrdFin
  
        int inOrdDchoIni = inOrdIzqFin +1;

        BinTree<T> left = reconstruir(preOrdIni, preOrdFin, inOrdIni, inOrdIzqFin, preorden, inorden); 
        BinTree<T> right = reconstruir(preOrdIni, preOrdFin, inOrdDchoIni, inOrdFin, preorden, inorden); 

        return BinTree<T>(left,root,right); 
    }
}



template <typename T>
BinTree<T> reconstruir(vector<T> const& preorden, vector<T> const& inorden) {
    int ini = 0; 
    return reconstruir(ini, preorden.size(), 0, inorden.size(), preorden, inorden); 
}



bool resuelveCaso() {

    // leemos la entrada
    int N;
    cin >> N;
    if (!cin)
        return false;

    vector<int> preorden(N);
    for (int& c : preorden) {
        cin >> c;
    }

    vector<int> inorden(N);
    for (int& c : inorden) {
        cin >> c;
    }

    auto arbol = reconstruir(preorden, inorden);
    cout << arbol << '\n';
    return true;
}

/*@ </answer> */
/*
int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

*/