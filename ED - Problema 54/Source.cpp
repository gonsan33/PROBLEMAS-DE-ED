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
#include<set>
using namespace std;

// Elige el tipo representante adecuado para el TAD OficinaEmpleo
// e implementa sus operaciones.
// Puedes añadir métodos o funciones privadas si lo consideras conveniente.
// Justifica la elección de los tipos y el coste de las operaciones.
//@ <answer>

using paciente = string;

class Urgencias {

    struct infoPaciente {
        int gravedad;
        list<string>::iterator iter;
    };

    unordered_map<paciente, infoPaciente>pacientes;
    vector<list<string>>sala_espera;
    set<string>curados;

public:

    Urgencias() :sala_espera(vector<list<string>>(3)) {};

    void nuevo_paciente(paciente const& nom, int gravedad) {
        if (pacientes.count(nom) != 0)throw domain_error("Paciente repetido");
        if (gravedad < 1 || gravedad>3)throw domain_error("Gravedad incorrecta");
        infoPaciente ip;
        ip.gravedad = gravedad;
        ip.iter = sala_espera[gravedad - 1].insert(sala_espera[gravedad - 1].end(), nom);
        pacientes[nom] = ip;
    }

    int gravedad_actual(paciente const& nom) const {
        if (pacientes.count(nom) == 0)throw domain_error("Paciente inexistente");
        return pacientes.at(nom).gravedad;
    }

    paciente siguiente() {
        string str = "";
        int i = 2;
        bool enc = false;
        while (i >= 0 && !enc) {
            int ii = 0;
            while (ii < sala_espera[i].size()&&!enc) {
                enc = true;
                str = sala_espera[i].front();
                ++ii;//Esto sobraria pero bueno lo dejo
            }
            --i;
        }
        if (!enc)throw domain_error("No hay pacientes");
        auto it = pacientes[str].iter;
        sala_espera[pacientes[str].gravedad-1].erase(it);
        pacientes.erase(str);
        return str;
    }

    void mejora(paciente nom)  {
        if (pacientes.count(nom) == 0)throw domain_error("Paciente inexistente");
        int gravedad = pacientes[nom].gravedad;
        auto it = pacientes[nom].iter;
        sala_espera[gravedad - 1].erase(it);
        --gravedad;
        if (gravedad == 0) {//Se larga del hospital
            pacientes.erase(nom);
            curados.insert(nom);//Coste logaritmico
        }
        else {//Se queda pero con menos gravedad
            --pacientes[nom].gravedad;
            pacientes[nom].iter = sala_espera[gravedad - 1].insert(sala_espera[gravedad - 1].begin(), nom);
        }
    }

    list<string>recuperados() const {
        list<string>l;
        for (string s : curados) {
            l.push_back(s);
        }
        return l;
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden, nom;
    int gravedad;
    cin >> orden;
    if (!cin)
        return false;

    Urgencias hospital;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> nom >> gravedad;
                hospital.nuevo_paciente(nom, gravedad);
            }
            else if (orden == "gravedad_actual") {
                cin >> nom;
                int g = hospital.gravedad_actual(nom);
                cout<<"La gravedad de " << nom << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string paciente = hospital.siguiente();
                cout <<  "Siguiente paciente: "<<paciente<<'\n';
            }
            else if (orden == "mejora") {
                cin >> nom;
                hospital.mejora(nom);
            }
            else if (orden == "recuperados") {
                auto lista = hospital.recuperados();
                cout << "Lista de recuperados:";
                for (auto a : lista)cout << " " << a;
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


