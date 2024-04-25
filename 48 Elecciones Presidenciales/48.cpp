/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
 * Introduce el nombre y apellidos de los/as componentes del grupo:
 *
 * Estudiante: Gonzalo Sánchez Montesinos
 *
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {
  
public:

  ConteoVotos() {}
  void nuevo_estado(const string &nombre, int num_compromisarios) { //O(1)
      //busco si está el estado
      auto [it, nuevo] = estados.insert({ nombre, InfoEstado(nombre, num_compromisarios) }); 
      //nuevo == false si y solo si el estado ya estaba, en cuyo caso insert no hace nada
      if (!nuevo) throw domain_error("Estado ya existente"); 
  }

  void sumar_votos(const string &estado, const string &partido, int num_votos) { //O(logP) donde P es el número de partidos
      //cojo el estado
      InfoEstado& infoEstado = this->buscar_estado(estado); 
      //cojo el partido
      infoEstado.votos[partido] += num_votos; 
      //se comprueba si es el partido que más votos tiene 
      if (infoEstado.ganador == "" || infoEstado.votos[infoEstado.ganador] < infoEstado.votos[partido]) {
          //actualizo la información de los compromisarios que obtiene cada partido a nivel nacional 
          partidos[infoEstado.ganador] -= infoEstado.compromisarios; 
          //cambio el ganador 
          infoEstado.ganador = partido; 
          //sumo sus compromisarios a nivel nacional 
          partidos[infoEstado.ganador] += infoEstado.compromisarios;
      }
  }

  string ganador_en(const string &estado) const { //O(1)
      return this->buscar_estado(estado).ganador; 
  }

  vector<pair<string,int>> resultados() const { 
      vector<pair<string, int>> v; 
      for (const auto& [partido, compr] : partidos) {
          if (compr > 0) v.push_back({ partido, compr }); 
      }
      return v; 
  }

private: 

    using Partido = string; 
    using Estado = string; 

    struct InfoEstado {
        string nombre; 
        int compromisarios; 
        unordered_map<Partido, int> votos; 
        Partido ganador; 
        InfoEstado(string n, int c): nombre(n), compromisarios(c),ganador("") {}
    };

    unordered_map<Estado, InfoEstado> estados; 
    map<Partido, int> partidos; 

    /*
    dos soluciones posibles: 
    que partidos sea un map, en cuyo caso la operación sumar votos tiene coste O(logP), donde P es el número de partidos. Esto es en el caso peor, cuando se cambia de ganador. 
    Si no se cambia de ganador, el coste es constante. 
    que partidos sea un unordered_map, en cuyo caso la operación sumar_votos tiene coste O(1), pero la operación resultados tiene coste PlogP. 
    Asumo que se cambia de ganador muchas menos veces que veces se llama a resultado, luego se opta por que partidos sea un map
    */

    //Operaciones de búsqueda
    InfoEstado& buscar_estado(const Estado& estado) {
        auto it = estados.find(estado); 
        if (it == estados.end()) throw domain_error("Estado no encontrado");
        else return it->second; 
    }

    const InfoEstado& buscar_estado(const Estado& estado) const {
        auto it = estados.find(estado);
        if (it == estados.end()) throw domain_error("Estado no encontrado");
        else return it->second;
    }


};


bool resuelveCaso() {
  string operacion, estado, partido;
  int compromisarios, votos;
  cin >> operacion;
  if (!cin)
    return false;
  
  ConteoVotos CV;
  
  while (operacion != "FIN") {
    try {
      if (operacion == "nuevo_estado") {
        cin >> estado >> compromisarios;
        CV.nuevo_estado(estado, compromisarios);
      } else if (operacion == "sumar_votos") {
        cin >> estado >> partido >> votos;
        CV.sumar_votos(estado, partido, votos);
      } else if (operacion == "ganador_en") {
        cin >> estado;
        auto ganador = CV.ganador_en(estado);
        cout << "Ganador en " << estado << ": " << ganador << '\n';
      } else if (operacion == "resultados") {
        for (auto [estado, compromisarios] : CV.resultados()) {
          cout << estado << ' ' << compromisarios << '\n';
        }
      }
    } catch (domain_error & e) {
      cout << e.what() << '\n';
    }
    cin >> operacion;
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
