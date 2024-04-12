/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1:
 Estudiante 2:
 
 
 Dad una explicación de la solución y justificad su coste.
 
 @ </answer> */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <map>
#include <iomanip>
using namespace std; 
/*
  Implementación de la clase BinTree para representar árboles binarios.
 */

template<class T>
class BinTree {
public:

  BinTree(): root_node(nullptr) { }
  
  BinTree(const T &elem): root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }
  
  BinTree(const BinTree &left, const T &elem, const BinTree &right)
    :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }
  

  bool empty() const {
    return root_node == nullptr;
  }

  const T & root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const {
    display_node(root_node, out);
  }
  
private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right): elem(elem), left(left), right(right) { }

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }

};

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert (c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert (c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

/*
 * Analizador léxico del lenguaje
 */

class Lexer {
public:
  Lexer(std::istream &in): in(in) { }

  std::string peek() {
    if (next != "") {
      return next;
    } else {
      next = read_next();
      return next;
    }
  }

  std::string get() {
    std::string result = peek();
    next = "";
    return result;
  }

private:
  std::istream &in;

  std::string read_next() {
    std::ostringstream result;
    char current;
    in >> current;
    while (iswspace(current)) {
      in >> current;
    }

    if (isdigit(current)) {
      result << current;
      while (isdigit(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (isalpha(current)) {
      result << current;
      while (isalnum(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
      result << current;
    } else if (current == ':') {
      result << current;
      in >> current;
      if (current != '=') throw std::domain_error("invalid token: :" + current);
      result << current;
    } else {
      throw std::domain_error("invalid_token: " + current);
    }

    return result.str();
  }

private:
  std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
  Parser(std::istream &in): l(in) { }

  BinTree<std::string> parse() {
    return S();
  }

private:
  Lexer l;

  bool is_identifier(const std::string &token) {
    return (!token.empty() && isalpha(token[0]));
  }

  bool is_identifier_or_number(const std::string &token) {
    return (!token.empty() && isalnum(token[0]));
  }

  BinTree<std::string> S() {
    std::string identifier = l.get();
    if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

    std::string equal = l.get();
    if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

    BinTree<std::string> rhs = E();

    std::string semicolon = l.get();
    if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

    return { { identifier }, ":=", rhs };
  }

  BinTree<std::string> E() {
    BinTree<std::string> term = T();
    return Ep(term);
  }

  BinTree<std::string> Ep(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "+" || op == "-") {
      l.get();
      BinTree<std::string> term = T();
      return Ep({ left, op, term });
    } else {
      return left;
    }
  }

  BinTree<std::string> T() {
    BinTree<std::string> factor = F();
    return Tp(factor);
  }

  BinTree<std::string> Tp(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "*") {
      l.get();
      BinTree<std::string> factor = F();
      return Tp({left, "*", factor});
    } else {
      return left;
    }
  }

  BinTree<std::string> F() {
    std::string next = l.get();
    if (is_identifier_or_number(next)) {
      return { next };
    } else if (next == "(") {
      BinTree<std::string> inner = E();
      std::string closing = l.get();
      if (closing != ")") throw std::domain_error(") expected, found " + closing);
      return inner;
    } else {
      throw std::domain_error("number or identifier expected, found " + next);
    }
  }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream &in) {
  return Parser(in).parse();
}

using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 *
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
/*@ <answer> */

int pasarAInt(const std::string& str) {
    int res = 0; 
    int pot = 1; 
    for (int i = str.size() - 1; i >= 0; --i) {
        res += (str[i] - '0') * pot; 
        pot *= 10; 
    }
    return res; 
}

int eval(const BinTree<std::string>& t, const map<string,int>& map) {
    int res; 
    switch (t.root().at(0))
    {
    case '*': 
        res = eval(t.left(),map) * eval(t.right(),map); 
        break; 
    case '+':res = eval(t.left(), map) + eval(t.right(), map);
        break;
    case '-': res = eval(t.left(), map) - eval(t.right(), map);
        break;
    case '0': 
    case '1': 
    case '2': 
    case '3': 
    case '4': 
    case '5': 
    case '6': 
    case '7': 
    case '8': 
    case '9': 
        //es un número 
        res = pasarAInt(t.root()); 
        break; 
    default: 
        //lo que tengo es una variable, tomo como precondición que esté inicializada
        res = map.at(t.root()); 
        break;
    }

    return res; 
}

void asignar(const BinTree<std::string>& t, map<string, int>& map) {

    map[t.left().root()] = eval(t.right(), map);
}



bool resuelveCaso() {
  int N;
  cin >> N;
  if (N == 0)
    return false;
  
  map<string, int> map; 
  for (int i = 0; i < N; ++i) {
      BinTree<string> sintax = parse(cin); 
      asignar(sintax, map); 
  }

  for (auto& [clave, valor] : map) {
      cout << clave << " = " << valor << '\n';
  }
  
  cout << "---\n";
    
  return true;
}



/*@ </answer> */

int main() {
//#ifndef DOMJUDGE
 // std::ifstream in("sample.in");
  //auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
  
  while (resuelveCaso()) {}

//#ifndef DOMJUDGE
  //std::cin.rdbuf(cinbuf);
 // // Descomentar si se trabaja en Windows
//system("PAUSE");
//#endif
  return 0;
}

/*
 
 3
 x := 3;
 y := 5;
 z := x + y;
 2
 b := 5 + 6 * 3;
 a := b - 1;
 3
 x := 1;
 x := x * 2;
 x := x * 2;
 0
 */
