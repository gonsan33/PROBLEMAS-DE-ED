/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Gonzalo Sánchez Montesinos
 
 
 Dad una explicación de la solución y justificad su coste.
 
 @ </answer> */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

// Elige el tipo representante adecuado para el TAD e implementa
// sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>
using DNI = string;

class carnet_puntos {
  
 
public:
  carnet_puntos(): puntos(MAX_PUNTOS + 1) {}
  
  void nuevo(const DNI& conductor) {//O(1)
      auto [it, nuevo] = conductores.insert({ conductor, InfoConductor(conductor,MAX_PUNTOS) }); 
      if (!nuevo) throw domain_error("Conductor duplicado"); 
      it->second.iterador = puntos[MAX_PUNTOS].insert(puntos[MAX_PUNTOS].begin(), conductor );
  }
  
  void quitar(DNI conductor, int points) { //O(1)
      InfoConductor& infoConductor = buscar_conductor(conductor); 
      //calculo sus nuevos puntos 
      int puntos_viejos = infoConductor.puntos; 
      infoConductor.puntos = max(infoConductor.puntos - points, 0);

      //si ha cambiado de puntos, lo cambio en la lista de puntos 
      if (puntos_viejos != infoConductor.puntos) {
          this->actualizar_puntos(infoConductor, puntos_viejos, infoConductor.puntos); 
      }
  }
  
  void recuperar(const DNI& conductor, int puntos) { //O(1)
      InfoConductor& infoConductor = buscar_conductor(conductor);
      int viejos_puntos = infoConductor.puntos; 
      infoConductor.puntos = min(MAX_PUNTOS, infoConductor.puntos + puntos); ; 
      if(viejos_puntos != infoConductor.puntos) actualizar_puntos(infoConductor, viejos_puntos, infoConductor.puntos); 
  }
  
  int consultar(const DNI& conductor) const {
      return buscar_conductor(conductor).puntos; 
  }
  
  int cuantos_con_puntos(int puntos) const {
      return buscar_puntos(puntos).size(); 
  }
  
  list<DNI> const& lista_por_puntos(int puntos) const {
      return buscar_puntos(puntos); 
  }

private: 


    struct InfoConductor {
        string dni; 
        int puntos; 
        list<DNI>::iterator iterador; 
        InfoConductor(const string& dni, int puntos) : dni(dni), puntos(puntos) {}

        InfoConductor(const string& dni, int puntos, const  list<DNI>::iterator& it) : dni(dni), puntos(puntos), iterador(it) {}
    };

    const int MAX_PUNTOS = 15;
    unordered_map<DNI, InfoConductor> conductores;
    vector<list<DNI>> puntos;

    InfoConductor& buscar_conductor(const DNI& dni) {
        auto it = conductores.find(dni); 
        if (it == conductores.end()) throw domain_error("Conductor inexistente");
        else return it->second; 
    }

    const InfoConductor& buscar_conductor(const DNI& dni) const {
        auto it = conductores.find(dni);
        if (it == conductores.end()) throw domain_error("Conductor inexistente");
        else return it->second;
    }

    list<DNI>& buscar_puntos(int points) {
        if (points < 0 || points > MAX_PUNTOS) throw domain_error("Puntos no validos");
        else return puntos[points]; 
    }

    const list<DNI>& buscar_puntos(int points) const {
        if (points < 0 || points > MAX_PUNTOS) throw domain_error("Puntos no validos");
        else return puntos[points];
    }


    void actualizar_puntos( InfoConductor& infoConductor, int puntos_viejos, int nuevos_puntos) {
        //lo elimino de la lista vieja
        puntos[puntos_viejos].erase(infoConductor.iterador);

        //lo añado a la lista nueva: 
        infoConductor.iterador = puntos[infoConductor.puntos].insert(puntos[infoConductor.puntos].begin(), infoConductor.dni);
    }



};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;
    
    carnet_puntos dgt;
    
    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            } else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            } else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            } else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
            } else
                cout << "OPERACION DESCONOCIDA\n";
        } catch (std::domain_error & e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

/*
 nuevo 123A
 nuevo 456B
 nuevo 666
 cuantos_con_puntos 15
 cuantos_con_puntos 0
 lista_por_puntos 15
 quitar 666 15
 lista_por_puntos 0
 quitar 456B 9
 consultar 456B
 quitar 123A 10
 recuperar 123A 1
 lista_por_puntos 6
 recuperar 123A 1
 lista_por_puntos 6
 lista_por_puntos 7
 FIN
 nuevo 123A
 nuevo 123A
 cuantos_con_puntos 20
 quitar 456B 2
 FIN
 
 */
