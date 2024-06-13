
// ALBERTO VERDEJO

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <fstream>
using namespace std;



using libro = string;

class ventaLibros {
    
    
public:
    void nuevoLibro(libro x, int n) {
        if (stock.count(x)) {
            stock.at(x).uds += n;
        }
        else {
            
            stock.insert({ x,Info{ n,0,lista.insert(lista.end(), x) } });
        }
        
    }
    
    void comprar(libro x) {
        auto it = stock.find(x); 
        if (it == stock.end()) throw invalid_argument("Libro no existente"); 
           if (it->second.uds == 0) throw out_of_range("No hay ejemplares"); 

        it->second.uds -= 1; 
        it->second.vendidas += 1; 
        
        //Ajusto la posición en la lista
        if (it->second.it != lista.begin()) {
            auto current = it->second.it;
            auto prev = it->second.it;
            --prev;

            while (current != lista.begin() && stock[*prev].vendidas <= it->second.vendidas) {
                --current;
                if(current != lista.begin()) --prev;
            }

            //elimino de donde estaba en la lista: 
            lista.erase(it->second.it); 
            //inserto
            it->second.it = lista.insert(current, x);
        }
       
    }
    
    bool estaLibro(libro x) const {
        return stock.count(x); 
    }
    
    void elimLibro(libro x) {
        if (stock.count(x)) {
            lista.erase(stock[x].it); 
            stock.erase(x); 
        }
    }
    
    int numEjemplares(libro x) const {
        auto it = stock.find(x);
        if (it == stock.end()) throw invalid_argument("Libro no existente");
        return it->second.uds; 
    }
    
    list<libro> top10() const {
        list<libro> res; 
        int i = 0; 
        auto it = lista.begin(); 
        while (it != lista.end() && i < 10 &&  stock.at(*it).vendidas > 0) {
            res.push_back(*it); 
            ++it; 
            ++i; 
        }
        return res; 

    }

private: 

    list<libro> lista;
    struct Info {
        int uds; 
        int vendidas; 
        list<libro>::iterator it; 
    };
    unordered_map<libro, Info> stock;



    
};


// Muestra el contenido de una lista
template <class T>
void mostrar(list<T> const& l) {
    for (auto const& e : l) {
        cout << "    " << e << '\n';
    }
}

bool resuelveCaso(){
    int numOp;
    
    cin >> numOp;
    if (!cin) return false;
    
    ventaLibros amazon;

    string operacion, titulo;

    for (int i = 0; i < numOp; ++i) {
        cin >> operacion;
        cin.ignore(1); // saltar blanco
        if (operacion == "nuevoLibro") {
            int unidades;
            cin >> unidades;
            cin.ignore(1);
            getline(cin, titulo);
            amazon.nuevoLibro(titulo, unidades);
        } else if (operacion == "comprar") {
            getline(cin, titulo);
            try {
                amazon.comprar(titulo);
            } catch (out_of_range const& e) {
                cout << e.what() << '\n';
            } catch (invalid_argument const& e) {
                cout << e.what() << '\n';
            }
        } else if (operacion == "estaLibro") {
            getline(cin, titulo);
            if (amazon.estaLibro(titulo)) {
                cout << "El libro " << titulo << " esta en el sistema\n";
            }
            else {
                cout << "No existe el libro " << titulo << " en el sistema\n";
            }
        } else if (operacion == "elimLibro") {
            getline(cin, titulo);
            amazon.elimLibro(titulo);
        } else if (operacion == "numEjemplares") {
            getline(cin, titulo);
            if (amazon.estaLibro(titulo)) {
                cout << "Existen " << amazon.numEjemplares(titulo) << " ejemplares del libro " << titulo << '\n';
            } else {
                cout << "No existe el libro " << titulo << " en el sistema\n";
            }
        }
        else if (operacion == "top10") {
           cout << "TOP10\n";
            mostrar(amazon.top10());
        }
    }
    // fin del caso
    cout << "---\n";
    return true;
    
}

int main(){
    /*
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
*/
  while (resuelveCaso()) { }
  /*
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
*/
    return 0;
}

/*
 5
 nuevoLibro 20 Heidi
 nuevoLibro 30 Caperucita roja
 comprar Heidi
 numEjemplares Caperucita roja
 top10
 8
 nuevoLibro 1 La vuelta al mundo en 80 dias
 comprar La vuelta al mundo en 80 dias
 estaLibro La vuelta al mundo en 80 dias
 nuevoLibro 5 Viaje al centro de la tierra
 comprar Viaje al centro de la tierra
 comprar Viaje al centro de la tierra
 top10
 comprar La isla misteriosa

 */
