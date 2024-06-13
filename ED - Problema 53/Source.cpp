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
using namespace std;

// Elige el tipo representante adecuado para el TAD OficinaEmpleo
// e implementa sus operaciones.
// Puedes añadir métodos o funciones privadas si lo consideras conveniente.
// Justifica la elección de los tipos y el coste de las operaciones.
//@ <answer>

using nombre = string;
using empleo = string;

class OficinaEmpleo {


    unordered_map<nombre,map< empleo,list<string>::iterator>>tios;//Aquí guardo los iteradores de las listas de los empleos
    unordered_map<empleo, list<string>>empleos;

public:

    void altaOficina(nombre const& nom, empleo const& emp) {
        if (tios.count(nom) == 0) {//No está apuntada
           list<string>::iterator it= empleos[emp].insert(empleos[emp].end(),nom);
           tios[nom][emp] = it;
        }
        else {
            auto it = tios[nom].find(emp);
            if (it == tios[nom].end()) {
                list<string>::iterator iter = empleos[emp].insert(empleos[emp].end(), nom);
                tios[nom][emp]=iter;
            }
        }
        
    }

    nombre ofertaEmpleo(empleo emp) {
        if (empleos.count(emp) == 0)throw domain_error("No existen personas apuntadas a este empleo");
        string a = empleos[emp].front();
        //Ahora le borramos del sistema
        for (auto [k, v] : tios[a]) {
            empleos[k].erase(v);
            if (empleos[k].empty()) {
                empleos.erase(k);
            }
        }
        tios.erase(a);
        return a;
    }

    vector<empleo> listadoEmpleos(nombre nom) const {
        if (tios.count(nom) == 0)throw domain_error("Persona inexistente");
        vector<string>vec;
        for (auto [k, v] : tios.at(nom)) {
            vec.push_back(k);
        }
        return vec;
    }
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
            }
            else if (orden == "ofertaEmpleo") {
                cin >> emp;
                auto afortunado = paro.ofertaEmpleo(emp);
                cout << emp << ": " << afortunado << '\n';
            }
            else if (orden == "listadoEmpleos") {
                cin >> nom;
                auto caps = paro.listadoEmpleos(nom);
                cout << nom << ":";
                for (auto c : caps) {
                    cout << ' ' << c;
                }
                cout << '\n';
            }
        }
        catch (domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
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
