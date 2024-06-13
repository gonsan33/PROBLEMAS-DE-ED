// ****  IMPORTANTE  ******

// Nombre y apellidos del estudiante

// Usuario del juez de examen

//*************************************



#include <iostream>
#include <iomanip>
#include <stdexcept>


using entrenador = std::string;
using pokemon = std::string;
using nivel = int;

class CentroPokemon {


        // Aqui el código del alumno

public:
    
    void capturar_pokemon(entrenador const& e, pokemon const& p, nivel n) {
        
        
    }
    
    std::pair<pokemon,nivel> vencer_pokemon (entrenador const& e, nivel n) {
        
        
    }
    
    int dia_de_liberacion(pokemon const& p) {
        
        
    }
    
    pokemon gimnasio (entrenador const& e) {
        
        
    }
};



// A PARTIR DE AQUI NO SE PUEDE MODIFICAR EL CODIGO

bool resuelveCaso() {
    // leer los datos de la entrada
    
    std::string op;
    std::cin >> op;
    if (!std::cin)
        return false;
    
    CentroPokemon centro;
    
    while (op != "FIN") {
        
        try {
            
            if (op == "capturar_pokemon") {
                
                entrenador e; pokemon p; nivel n;
                std::cin >> e >> p >> n;
                
                centro.capturar_pokemon(e, p, n);
                
            }
            
            else if (op == "vencer_pokemon") {
                
                entrenador e; int n; 
                std::cin >> e >> n;
                
                std::pair<pokemon,nivel> p = centro.vencer_pokemon(e,n);
                std::cout << e << " utiliza el pokemon " << p.first << " con nivel " << p.second << " para vencer a un nivel " << n << '\n';
            }
            
            else if (op == "dia_de_liberacion") {
                pokemon p;
                std::cin >> p;
                int n = centro.dia_de_liberacion(p);
                std::cout << "Liberados "<< n << " pokemon " << p << '\n';
            }
            
            if (op == "gimnasio") {
                entrenador e; 
                std::cin >> e;
                pokemon p = centro.gimnasio(e);
                std::cout << e << " deja el pokemon " << p << " en un gimnasio\n";
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
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
   
    
    while (resuelveCaso()) ;//Resolvemos todos los casos
    
    
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}

