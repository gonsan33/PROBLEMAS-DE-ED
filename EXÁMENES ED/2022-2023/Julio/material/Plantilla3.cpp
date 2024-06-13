// ED Junio 2023
// Ejercicio 3

//**************************************************
//
// IMPORTANTE
//
// Nombre y Apellidos del alumno
// Usuario del juez en la prueba de hoy
//
//***************************************************


#include <iostream> 
#include <fstream> 
#include <stdexcept>





class SistemaBatallas {
private: 



    // Codigo del alumno



    
public:
    void aparece_villano(std::string const& villano, int vida, int ataque) {


        // Codigo del alumno

    }
    
    void aparece_heroe(std::string const& heroe, int vida) {


        // Codigo del alumno

        
    }
    
    void aprende_ataque(std::string const& heroe, std::string ataque, int valor) {


        // Codigo del alumno
        

    }
    
    std::vector<std::pair<std::string, int>> mostrar_ataques(std::string const& heroe) {


        // Codigo del alumno


    }
    
    std::vector<std::pair<std::string, int>>  mostrar_turnos() {


        // Codigo del alumno



    }
    
    bool villano_ataca(std::string const& villano, std::string const& heroe) {




        // Codigo del alumno





    }
    
    bool heroe_ataca(std::string const& heroe, std::string const& ataque, std::string const& villano) {



        // Codigo del alumno




    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    
    std::string op;
    std::cin >> op;
    if (!std::cin)
        return false;
    
    SistemaBatallas sistema;
    
    while (op != "FIN") {
        
        try {
            
            if (op == "aparece_villano") {
                
                std::string villano; int vida, ataque;
                std::cin >> villano >> vida >> ataque;
                
                sistema.aparece_villano(villano, vida, ataque);
                
            }
            
            else if (op == "aparece_heroe") {
                
                std::string heroe; int vida;
                std::cin >> heroe >> vida;
                
                sistema.aparece_heroe(heroe, vida);
                
            }
            
            else if (op == "aprende_ataque") {
                std::string heroe; std::string ataque;
                int valor;
                std::cin >> heroe >> ataque >> valor;
                
                sistema.aprende_ataque(heroe, ataque, valor);
            }
            
            else if (op == "mostrar_ataques") {
                std::string heroe;
                std::cin >> heroe;
                std::vector<std::pair<std::string, int>> sol = sistema.mostrar_ataques(heroe);
                std::cout << "Ataques de " << heroe << '\n';
                for (int i = 0; i < sol.size(); ++i) {
                    std::cout << sol[i].first << ' ' << sol[i].second << '\n';
                }
            }
            
            else if (op == "mostrar_turnos") {
                std::vector<std::pair<std::string, int>> sol = sistema.mostrar_turnos();
                std::cout << "Turno:\n";
                for (int i = 0; i < sol.size(); ++i) {
                    std::cout << sol[i].first << ' ' << sol[i].second << '\n';
                }
            }
            
            else if (op == "villano_ataca") {
                std::string villano, heroe;
                std::cin >> villano >> heroe;
                bool sol = sistema.villano_ataca(villano, heroe);
                std::cout << villano << " ataca a " << heroe << '\n';
                if (sol) std::cout << heroe << " derrotado\n";
            }
            
            else if (op == "heroe_ataca") {
                std::string villano, ataque, heroe;
                std::cin >> heroe >> ataque >> villano;
                bool sol = sistema.heroe_ataca(heroe, ataque, villano);
                std::cout << heroe << " ataca a " << villano << '\n';
                if (sol) std::cout << villano << " derrotado\n";
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
    std::ifstream in("sample3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to sample3.txt
#endif

    while (resuelveCaso()) {}
        

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

