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
#include <exception>
#include <unordered_map>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <tuple>
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
  
  void eliminar_torre(const string &nombre) { //O(1) 
      InfoTorre& info = buscar_torre(nombre); 
      
      //como info guarda los iteradores, eliminar tiene coste constante
      posicionesI.at(info.pos.second).erase(info.iteradorI); 
      posicionesJ.at(info.pos.first).erase(info.iteradorJ); 

      //se elimina del mapa de torres
      torres.erase(nombre); 

  }
  
  pair<bool, string> torre_en_posicion(int x, int y) const { //O(log NX + log NY) donde NX, NY son el máximo número de torres con una misma coordenada X/Y

      auto itI = posicionesI.find(y); 
      auto itD = posicionesJ.find(x); 
      if (itI == posicionesI.end() || itD == posicionesJ.end()) return {false, ""};

      //ahora se obtienen iteradores que apunten al par componente torre
      auto nuevoItI = itI->second.find(x); 
      auto nuevoItD = itD->second.find(y); 

      //los dos deben ser distintos del final
      if (nuevoItI == itI->second.end() || nuevoItD == itD->second.end())  return { false, "" };

      return { true,nuevoItI->second }; 

  }

  pair<int, int> posicion(const string &nombre) const {
      return this->buscar_torre(nombre).pos; 
  }
  
  string torre_mas_cercana(const string &nombre, const Direccion &dir) const { //Coste O(1) 
      const InfoTorre& info = this->buscar_torre(nombre); 
      map<int, Nombre>::iterator it; 
      switch (dir) {
      case Direccion::Norte:
          if (info.iteradorJ == posicionesJ.at(info.pos.first).end()  || posicionesJ.at(info.pos.first).size() <= 1) throw domain_error("No hay torres en esa direccion");
          it = info.iteradorJ; 

          return (++it)->second;
      case Direccion::Sur: 
          if (info.iteradorJ == posicionesJ.at(info.pos.first).begin()|| posicionesJ.at(info.pos.first).size() <= 1) throw domain_error("No hay torres en esa direccion");
         it = info.iteradorJ;

          return (--it)->second;
      case Direccion::Este: 
          if (info.iteradorI == posicionesI.at(info.pos.second).end() || posicionesI.at(info.pos.second).size() <= 1) throw domain_error("No hay torres en esa direccion");
         it = info.iteradorI;
          return (++it)->second;      
      case Direccion::Oeste:
          if (info.iteradorI == posicionesI.at(info.pos.second).begin() || posicionesI.at(info.pos.second).size() <= 1) throw domain_error("No hay torres en esa direccion");
          it = info.iteradorI;
          return (--it)->second;
      }
      return ""; 
  }

private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados
   

    struct InfoTorre {
        string nombre;
        Position pos; 

        map<int, Nombre>::iterator iteradorI; 
        map<int, Nombre>::iterator iteradorJ;

        InfoTorre(const Nombre& nombre, const Position& pos, const map<int,Nombre>::iterator& itI, const map<int,Nombre>::iterator& itJ): nombre(nombre), pos(pos), iteradorI(itI), iteradorJ(itJ) {}

    };
    

    unordered_map<Nombre, InfoTorre> torres; 

    unordered_map<int, map<int,Nombre>> posicionesJ; //Clave:  x, valor: (clave:  y , valor: nombre)
    unordered_map<int, map<int, Nombre>> posicionesI; //Clave:  y, valor: (clave:  x , valor: nombre)


    
    InfoTorre& buscar_torre(const Nombre& nombre) { //O(1)
        auto it = torres.find(nombre); 
        if (it == torres.end()) throw domain_error("Torre no existente"); 
        return it->second; 
    }

    const InfoTorre& buscar_torre(const Nombre& nombre) const { //O(1)
        auto it = torres.find(nombre);
        if (it == torres.end()) throw domain_error("Torre no existente");
        return it->second;
    }

    void insertar_torre(const Nombre& nombre, int x, int y) { //O(log NX + log NY) donde NX, NY son el máximo número de torres con una misma coordenada X/Y

        //se mira si había una torre con el mismo nombre
        if(torres.count(nombre)) throw domain_error("Torre ya existente");

        //como la torre no está, se tendrá que añadir. 

        auto [iteradorI, insertadoI] = this->posicionesI[y].insert({ x,nombre }); 
        auto [iteradorD, insertadoD] = this->posicionesJ[x].insert({ y,nombre }); 
        if (!insertadoI || !insertadoD) throw domain_error("Posicion ocupada"); 

        torres.insert({ nombre, InfoTorre(nombre, {x,y}, iteradorI, iteradorD)});

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

  while (resuelveCaso()) { }

  return 0;
}
