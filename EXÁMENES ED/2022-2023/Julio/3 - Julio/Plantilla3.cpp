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
#include <unordered_map>
#include <map>
using namespace std; 





class SistemaBatallas {
private: 



    // Codigo del alumno



    
public:
    void aparece_villano(std::string const& villano, int vida, int ataque) {
        auto it = villanos.find(villano); 
        if (it != villanos.end()) throw invalid_argument("Personaje ya existente");
        else villanos[villano] = Villain{ vida, ataque, turnos.insert(turnos.end(), {villano,vida}) };
    }
    
    void aparece_heroe(std::string const& heroe, int vida) {
        auto it = heroes.find(heroe);
        if (it != heroes.end()) throw invalid_argument("Personaje ya existente");
        else {
            Hero hero; 
            hero.vida = vida;  
            hero.it = turnos.insert(turnos.end(), { heroe, vida });
            heroes[heroe] = hero; 
        }
    }
    
    void aprende_ataque(std::string const& heroe, std::string ataque, int valor) {        
        Hero& hero = getHero(heroe); 
        if (hero.ataques.count(ataque)) throw invalid_argument("Ataque repetido");
        else hero.ataques.insert({ ataque,valor }); 
    }
    
    std::vector<std::pair<std::string, int>> mostrar_ataques(std::string const& heroe) const{
        const Hero& hero = getHero(heroe); 
        vector<pair<string, int>> rta; 
        for (auto [nombre, daño] : hero.ataques) {
            rta.push_back({ nombre, daño }); 
        }
        return rta; 

    }
    
    std::vector<std::pair<std::string, int>>  mostrar_turnos() const {
        std::vector<std::pair<std::string, int>> rta; 
        for (const auto& par : turnos) {
            rta.push_back(par); 
        }
        return rta; 
    }
    
    bool villano_ataca(std::string const& villano, std::string const& heroe) {
        // Codigo del alumno
        
        //Cojo héroe y villano
        Hero& hero = getHero(heroe); 
        Villain& vill = getVillain(villano); 
        //Miro que sea el turno del villano 
        if (turnos.front().first != villano) throw invalid_argument("No es su turno"); 

        //Ataco al héroe: 
        hero.vida -= vill.ataque; 

        bool muerto = hero.vida <= 0; 

        //Pongo al villano a  esperar turno 
        turnos.pop_front(); 
        vill.it = turnos.insert(turnos.end(), { villano, vill.vida }); 

        //Actualizo el héroe: 
        if (muerto) {
            turnos.erase(hero.it); 
            heroes.erase(heroe); 
        }
        else {
            hero.it->second = hero.vida; 
        }


        return muerto; 
    }
    
    bool heroe_ataca(std::string const& heroe, std::string const& ataque, std::string const& villano) {
        // Codigo del alumno

        //Cojo héroe y villano
        Hero& hero = getHero(heroe);
        Villain& vill = getVillain(villano);
        //Miro que sea el turno del héroe 
        if (turnos.front().first != heroe) throw invalid_argument("No es su turno");

        //Miro que exista el ataque: 
        auto it_ataque = hero.ataques.find(ataque); 
        if (it_ataque == hero.ataques.end()) throw invalid_argument("Ataque no aprendido"); 
        int daño = it_ataque->second; 

        //Ataco al villano
        vill.vida -= daño; 

        bool muerto = vill.vida <= 0; 

        //Pongo al héroe a esperar turno: 
        turnos.pop_front();
        hero.it = turnos.insert(turnos.end(), { heroe, hero.vida });

        //Actualizo al villano
        if (muerto) {
            turnos.erase(vill.it);
            villanos.erase(villano);
        }
        else vill.it->second = vill.vida; 
        

        return muerto; 
    }

private: 
    struct Hero {
        int vida; 
        map<string, int> ataques; 
        list<pair<string, int>>::iterator it;
    };
    struct Villain {
        int vida; 
        int ataque; 
        list<pair<string, int>>::iterator it;
    };
    unordered_map<string, Hero> heroes; 
    unordered_map<string, Villain> villanos; 
    list<pair<string,int>> turnos; 

    Hero& getHero(const string& str) {
        auto it = heroes.find(str); 
        if (it == heroes.end()) throw invalid_argument("Heroe inexistente");
        else return it->second; 
    }

    const Hero& getHero(const string& str) const{
        auto it = heroes.find(str);
        if (it == heroes.end()) throw invalid_argument("Heroe inexistente");
        else return it->second;
    }

    Villain& getVillain(const string& str) {
        auto it = villanos.find(str);
        if (it == villanos.end()) throw invalid_argument("Villano inexistente");
        else return it->second;
    }
    const Villain& getVillain(const string& str) const {
        auto it = villanos.find(str);
        if (it == villanos.end()) throw invalid_argument("Villano inexistente");
        else return it->second;
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

