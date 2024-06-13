// ****  IMPORTANTE  ******

// Nombre y apellidos del estudiante

// Usuario del juez de examen

//*************************************



#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std; 

using entrenador = std::string;
using pokemon = std::string;
using nivel = int;

class CentroPokemon {


        // Aqui el código del alumno

public:
    
    void capturar_pokemon(entrenador const& e, pokemon const& p, nivel n) { //O(log P) donde P es el número de pokemons (un entrenador podría tenerlos todos)
        //miro si el entrenador había capturado ya ese pokemon
        auto iterador_pokemons = pokemons.find(p); 
        
        if (iterador_pokemons != pokemons.end()) {
            auto iterador_mapa_iteradores = iterador_pokemons->second.mapa_iteradores.find(e);
            if (iterador_mapa_iteradores != iterador_pokemons->second.mapa_iteradores.end()) throw invalid_argument("Pokemon repetido");
            else if (entrenadores[e].mapa_pokemons.count(n)) throw invalid_argument("Nivel repetido");
            else registrar_pokemon(e, p, n);
        }
        else if(entrenadores[e].mapa_pokemons.count(n)) throw invalid_argument("Nivel repetido");
        else registrar_pokemon(e, p, n); 
        
    }
    
    std::pair<pokemon,nivel> vencer_pokemon (entrenador const& e, nivel n) const {
        const InfoEntrenador& info = getEntrenador(e); 
        if (info.mapa_pokemons.size() == 0)  throw invalid_argument("No tiene pokemons"); 
        else {
            auto [niv, pok] = *(--info.mapa_pokemons.cend()); 
            if (niv < n) throw invalid_argument("El pokemon no puede ser vencido");
            else return { pok,niv }; 
        }
        
    }
    
    int dia_de_liberacion(pokemon const& p) {
        int total = pokemons[p].mapa_iteradores.size(); 
        for (auto [e, iteradores] : pokemons[p].mapa_iteradores) {
            borrarPokemon(e, iteradores); 
        }
        return total; 
        
    }
    
    pokemon gimnasio (entrenador const& e) {
        InfoEntrenador& info = getEntrenador(e); 
        if(info.lista_pokemons.empty()) throw invalid_argument("No tiene pokemons");
        else {
            pokemon p = info.lista_pokemons.front(); 
            info.lista_pokemons.pop_front(); 
            Iteradores& iteradores = pokemons[p].mapa_iteradores[e]; 
            info.mapa_pokemons.erase(iteradores.it_mapa_pokemons); 
            return p; 
        }
    }

private: 
    struct InfoEntrenador {
        map<nivel, pokemon> mapa_pokemons; //inserción logn, acceso y eliminación con iterador: constante
        list<pokemon> lista_pokemons; //inserción/eliminación/acceso con iterador constante
        //unordered_set<pokemon> conjunto_pokemons; //acceso, inserción, eliminación constante

    };
    struct Iteradores {
        list<pokemon>::iterator it_lista_pokemons; 
        map<nivel, pokemon>::iterator it_mapa_pokemons; 
    };

    struct InfoPokemon {
        unordered_map<entrenador, Iteradores> mapa_iteradores; 
    };

    unordered_map<entrenador, InfoEntrenador> entrenadores; 
    unordered_map<pokemon, InfoPokemon> pokemons; 

    void borrarPokemon(const entrenador& entr,const Iteradores& iteradores) {
        InfoEntrenador& info = getEntrenador(entr); 
        info.lista_pokemons.erase(iteradores.it_lista_pokemons); 
        info.mapa_pokemons.erase(iteradores.it_mapa_pokemons); 
    }

    InfoEntrenador& getEntrenador(const entrenador& entr) {
        auto it = entrenadores.find(entr); 
        if (it == entrenadores.end()) throw invalid_argument("Entrenador no existente");
        else return it->second; 
    }    

    const InfoEntrenador& getEntrenador(const entrenador& entr) const {
        auto it = entrenadores.find(entr);
        if (it == entrenadores.end()) throw invalid_argument("Entrenador no existente");
        else return it->second;
    }

    void registrar_pokemon(entrenador const& e, pokemon const& p, nivel n) {
        Iteradores& iteradores = pokemons[p].mapa_iteradores[e];
        InfoEntrenador& info = entrenadores[e]; 
        iteradores.it_lista_pokemons = info.lista_pokemons.insert(info.lista_pokemons.end(), p); 
        iteradores.it_mapa_pokemons = info.mapa_pokemons.insert({ n,p }).first; 
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

