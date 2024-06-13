/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>.
 *
 * Tampoco está permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

//@ <answer>
// Nombre y Apellidos: ALBERTO VERDEJO
//@ </answer>

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
using namespace std;

// Elige el tipo representante adecuado para el TAD OficinaEmpleo
// e implementa sus operaciones.
// Puedes añadir métodos o funciones privadas si lo consideras conveniente.
// Justifica la elección de los tipos y el coste de las operaciones.
//@ <answer>

//E empleos totales  P personas totales 
using nombre = string;
using empleo = string;

class OficinaEmpleo {

public:
   
   void altaOficina(nombre const& nom, empleo const& emp) { //O(logE) 

       InfoEmpleo info;
       info.emp = emp;
       auto it = personas[nom].find(info); 
       if (it == personas[nom].end()) {
           info.it = empleos[emp].insert(empleos[emp].end(), nom);
           personas[nom].insert(info); 
       }
   }
   
   nombre ofertaEmpleo(empleo emp) {
       if (!empleos.count(emp)) throw domain_error("No existen personas apuntadas a este empleo"); 
       else {
           nombre nom = empleos[emp].front(); 

           for (const InfoEmpleo& info : personas[nom]) {
               empleos[info.emp].erase(info.it);
               if (empleos[info.emp].empty()) empleos.erase(info.emp); 
           }

           personas.erase(nom); 
           return nom; 

       }
   }
   
   vector<empleo> listadoEmpleos(nombre nom) const {
       if (!personas.count(nom)) throw domain_error("Persona inexistente"); 
       vector<empleo> rta; 
       for (const InfoEmpleo& info : personas.at(nom)) {
           rta.push_back(info.emp); 
       }
       return rta; 
   }
private: 
    struct InfoEmpleo {
        empleo emp; 
        list<nombre>::iterator it; 
        bool operator <(const InfoEmpleo& other) const {
            return emp < other.emp; 
        }
    };
    unordered_map<nombre, set<InfoEmpleo>> personas;
    unordered_map<empleo, list<nombre>> empleos; 
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
   string orden, nom, emp;
   cin >> orden;
   if (!cin)
      return false;
   
   OficinaEmpleo paro;
   
   while (orden != "FIN") {
      try {
         if (orden == "altaOficina") {
            cin >> nom >> emp;
            paro.altaOficina(nom, emp);
         } else if (orden == "ofertaEmpleo") {
            cin >> emp;
            auto afortunado = paro.ofertaEmpleo(emp);
            cout << emp << ": " << afortunado << '\n';
         } else if (orden == "listadoEmpleos") {
            cin >> nom;
            auto caps = paro.listadoEmpleos(nom);
            cout << nom << ":";
            for (auto c : caps) {
               cout << ' ' << c;
            }
            cout << '\n';
         }
      } catch (domain_error & e) {
         cout << "ERROR: " << e.what() << '\n';
      }
      cin >> orden;
   }
   cout << "---\n";
   return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.in");
    std::ofstream out("output.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    auto coutbuf = cout.rdbuf(out.rdbuf());
#endif
   while (resuelveCaso());
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   cout.rdbuf(coutbuf);
#endif
   return 0;
}

/*
 altaOficina Carlota administracion
 altaOficina Carlota secretariado
 altaOficina Carlota recursosHumanos
 altaOficina Juan administracion
 altaOficina Juan riesgosLaborales
 ofertaEmpleo administracion
 altaOficina Beatriz administracion
 altaOficina Beatriz jardineria
 altaOficina Beatriz biblioteca
 ofertaEmpleo administracion
 listadoEmpleos Carlota
 altaOficina Carlota informatica
 altaOficina Beatriz informatica
 listadoEmpleos Beatriz
 ofertaEmpleo informatica
 ofertaEmpleo informatica
 ofertaEmpleo informatica
 ofertaEmpleo biblioteca
 FIN
 ofertaEmpleo informatica
 altaOficina Ivan informatica
 altaOficina Ivan administracion
 listadoEmpleos Ivan
 ofertaEmpleo informatica
 ofertaEmpleo administracion
 listadoEmpleos Ivan
 FIN

 
 */
