/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Gonzalo Sánchez Montesinos
 
 Dad una explicación de la solución y justificad su coste.
 Todas las operaciones tienen coste constante 
 @ </answer> */


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream & operator>>(istream &is, Direccion &dir) {
  string palabra; is >> palabra;
  if (palabra == "Norte") dir = Direccion::Norte;
  else if (palabra == "Sur") dir = Direccion::Sur;
  else if (palabra == "Este") dir = Direccion::Este;
  else if (palabra == "Oeste") dir = Direccion::Oeste;
  else throw std::domain_error("Lectura de direccion incorrecta");
  return is;
}

// Implementa a continuación la clase Desierto.
//@ <answer>

using Position = pair<int, int>; 
using Nombre = string; 

class Desierto {
public:
  
  Desierto() { }
  
  void anyadir_torre(const string &nombre, int x, int y) {
      this->insertar_torre(nombre, x, y); 
  }
  
  void eliminar_torre(const string &nombre) {
      auto [x, y] = buscar_torre(nombre); 
      //se quita del eje X
      posicionesI.erase()
  }
  
  pair<bool, string> torre_en_posicion(int x, int y) const {

  }

  pair<int, int> posicion(const string &nombre) const {

  }
  
  string torre_mas_cercana(const string &nombre, const Direccion &dir) const {

  }

private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados
   



    unordered_map<Nombre, Position> torres; 

    unordered_map<int, map<int,Nombre>> posicionesJ; //Clave:  x, valor: (clave:  y , valor: nombre)
    unordered_map<int, map<int, Nombre>> posicionesI; //Clave:  y, valor: (clave:  x , valor: nombre)



    Position& buscar_torre(const Nombre& nombre) {
        auto it = torres.find(nombre); 
        if (it == torres.end()) throw domain_error("Torre no existente"); 
        return it->second; 
    }

    const Position& buscar_torre(const Nombre& nombre) const {
        auto it = torres.find(nombre);
        if (it == torres.end()) throw domain_error("Torre no existente");
        return it->second;
    }

    void insertar_torre(const Nombre& nombre, int x, int y) { 
        
        //se mira si había una torre con el mismo nombre
        auto it = torres.find(nombre); 
        if (it != torres.end()) throw domain_error("Torre ya existente"); 
        torres.insert({ nombre, {x,y} }); 
        
        
        
        //se busca la posición 


        auto itI = posicionesI.find(y); 

        auto itJ = posicionesJ.find(x); 

        if (itI == posicionesI.end()) { //se inserta
            map<int, Nombre> nuevo; 
            nuevo.insert({ x,nombre }); 
            posicionesI.insert({y, nuevo });
        }
        else { //se mira si en la fila hay algún otro elemento con la misma clave x
            auto itNuevo = itI->second.find(x); 
            if (itNuevo == itI->second.end()) { //se inserta
                itI->second.insert({ x,nombre });
            }
            else throw domain_error("Posicion ocupada"); 

        }

        if (itJ == posicionesJ.end()) { //se inserta
            map<int, Nombre> nuevo;
            nuevo.insert({ y,nombre });
            posicionesI.insert({ x, nuevo });
        }
        else { //se mira si en la fila hay algún otro elemento con la misma clave x
            auto itNuevo = itJ->second.find(x);
            if (itNuevo == itJ->second.end()) { //se inserta
                itJ->second.insert({ y,nombre });
            }
            else throw domain_error("Posicion ocupada");

        }

    }
  

};



//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
  string inst, nombre; int x,y; Direccion dir;
  cin >> inst;
  if (!cin) return false;
  Desierto desierto;
  while (inst != "FIN") {
    try {
      if (inst == "anyadir_torre") {
        cin >> nombre >> x >> y;
        desierto.anyadir_torre(nombre, x, y);
      } else if (inst == "eliminar_torre") {
        cin >> nombre;
        desierto.eliminar_torre(nombre);
      } else if (inst == "posicion") {
        cin >> nombre;
        auto [x,y] = desierto.posicion(nombre);
        cout << x << ' ' << y << '\n';
      } else if (inst == "torre_en_posicion") {
        cin >> x >> y;
        auto [hay, nombre] = desierto.torre_en_posicion(x, y);
        if (hay) cout << "SI " << nombre << '\n';
        else cout << "NO\n";
      } else {
        cin >> nombre >> dir;
        nombre = desierto.torre_mas_cercana(nombre, dir);
        cout << nombre << '\n';
      }
    } catch (domain_error & e) {
      cout << e.what() << '\n';
    }
    cin >> inst;
  }
  cout << "---\n";
  return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (resuelveCaso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
