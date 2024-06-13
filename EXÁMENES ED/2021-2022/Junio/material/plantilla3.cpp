//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la representación empleada. 




// Indicar el coste de cada método en un comentario al principio del método.





#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector> 

// añade las librerías de la STL que necesites



using artista = std::string;
using obra = std::string;

// Elige el tipo representante adecuado para el TAD GaleriaArte e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.

class galeriaArte {

    // escribe aquí los atributos privados
    
public:
    galeriaArte() {}
    
    void nueva_obra(obra const& c, artista const& a, int p) {



    }
    
    void venta_obra (obra const& c) {




    }
    
    std::vector<artista> mas_vendidos() const {



    }
    
    std::vector<obra> obras_por_antiguedad(int k) const {




    }
};





// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    std::string op;
    std::cin >> op;
    if (!std::cin) return false;
    
    galeriaArte galeria;
    while (op != "FIN") {
        try {
            if (op == "nueva_obra") {
                obra c; artista a; int p;
                std::cin >> c >> a >> p;
                galeria.nueva_obra(c,a,p);
            }
            else if (op == "venta_obra") {
                obra c; 
                std::cin >> c;
                galeria.venta_obra(c);
            }
            else if (op == "mas_vendidos") {
                std::vector<artista> sol = galeria.mas_vendidos();
                std::cout << "Los artistas que mas han vendido son:\n";
                for (auto n : sol) std::cout << n << '\n';
            }
            else if (op == "obras_por_antiguedad") {
                int k; 
                std::cin >> k;
                std::vector<obra> v = galeria.obras_por_antiguedad(k);
                std::cout << "Obras mas antiguas en la galeria:\n";
                for (obra o : v) std::cout  << o << '\n';
            }
        }
        catch(std::invalid_argument& e) {
            std::cout << "ERROR: " << e.what() << "\n";
        }
        std::cin >> op;
    } 
    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif 
    
    while (resuelveCaso()) ;
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
  
    return 0;
}

