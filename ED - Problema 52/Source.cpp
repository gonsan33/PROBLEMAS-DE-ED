
// ALBERTO VERDEJO

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include<fstream>
#include<algorithm>
using namespace std;



using libro = string;


class ventaLibros {

    struct infoLibro {
        int ejemplares;
        int vendidos;
        list<string>::iterator it;
    };

    unordered_map<string, infoLibro>libros;
    map<int,list<string>>vendidos;




public:
    void nuevoLibro(libro x, int n) {
        if (libros.count(x) != 0)//Ya estaba
            libros[x].ejemplares += n;
        else {
            libros[x].ejemplares = n;
            libros[x].it = vendidos[0].insert(vendidos[0].begin(), x);
            libros[x].vendidos = 0;
        }
    }

    void comprar(libro x) {
        if (libros.count(x) == 0)throw invalid_argument("Libro no existente");
        int e = libros[x].ejemplares;
        int n = libros[x].vendidos;
        if (e == 0)throw out_of_range("No hay ejemplares");
        auto it = libros[x].it;
        vendidos[n].erase(it);
        libros[x].it = vendidos[n + 1].insert(vendidos[n+1].begin(), x);
        --libros[x].ejemplares;
        ++libros[x].vendidos;
    }

    bool estaLibro(libro x) const {
        return libros.count(x) != 0;
    }

    void elimLibro(libro x) {
        if (libros.count(x) != 0) {
            int n = libros[x].vendidos;
            vendidos[n].erase(libros[x].it);
            libros.erase(x);
        }
    }

    int numEjemplares(libro x) const {
        if (libros.count(x) == 0)throw invalid_argument("Libro no existente");
        return libros.at(x).ejemplares;
    }

    list<libro> top10() const {
        if (vendidos.empty())return list<libro>();
        auto it = vendidos.end();
        --it;
        int i = 0;
        list<libro>lista;
        while (it != vendidos.begin() && i <10) {
            auto i2 = (*it).second.begin();
            while(i<10&&i2!=(*it).second.end()) {
                lista.push_back((*i2));
                ++i2;
                ++i;
            }
            --it;
        }
        return lista;
    }
};


// Muestra el contenido de una lista
template <class T>
void mostrar(list<T> const& l) {
    for (auto const& e : l) {
        cout << "    " << e << '\n';
    }
}

bool resuelveCaso() {
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
        }
        else if (operacion == "comprar") {
            getline(cin, titulo);
            try {
                amazon.comprar(titulo);
            }
            catch (out_of_range const& e) {
                cout << e.what() << '\n';
            }
            catch (invalid_argument const& e) {
                cout << e.what() << '\n';
            }
        }
        else if (operacion == "estaLibro") {
            getline(cin, titulo);
            if (amazon.estaLibro(titulo)) {
                cout << "El libro " << titulo << " esta en el sistema\n";
            }
            else {
                cout << "No existe el libro " << titulo << " en el sistema\n";
            }
        }
        else if (operacion == "elimLibro") {
            getline(cin, titulo);
            amazon.elimLibro(titulo);
        }
        else if (operacion == "numEjemplares") {
            getline(cin, titulo);
            if (amazon.estaLibro(titulo)) {
                cout << "Existen " << amazon.numEjemplares(titulo) << " ejemplares del libro " << titulo << '\n';
            }
            else {
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

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
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
