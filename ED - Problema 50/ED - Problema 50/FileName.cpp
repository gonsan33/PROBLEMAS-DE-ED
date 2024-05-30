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

  Estudiante 1:Víctor Gómez Torres
  Estudiante 2: - - -

  Dad una explicación de la solución y justificad su coste.

  @ </answer> */


  // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include<unordered_map>
#include <map>

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
istream& operator>>(istream& is, Direccion& dir) {
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


struct Pos {
    int x;
    int y;

    bool operator ==(Pos p2) {
        return x == p2.x && y == p2.y;
    }

    bool operator<(Pos p2) {
        return x < p2.x || x == p2.x && y < p2.y;
    }

};

class Desierto {
public:

    Desierto() { };

    void anyadir_torre(const string& nombre, int x, int y) {
        if (torres.count(nombre) != 0)throw domain_error("Torre ya existente");
        if (mov_x.count(y)!=0&&mov_x.at(y).count(x) != 0)throw domain_error("Posicion ocupada");
        torres[nombre] = { x,y };
        mov_x[y][x] = nombre;
        mov_y[x][y] = nombre;
    }

    void eliminar_torre(const string& nombre) {
        if (torres.count(nombre) == 0)throw domain_error("Torre no existente");
        Pos p = torres[nombre];
        torres.erase(nombre);
        auto it = mov_x.at(p.y).find(p.x);
        mov_x[p.y].erase(it);
        auto it2 = mov_y.at(p.x).find(p.y);
        mov_y[p.x].erase(it2);
    }

    pair<bool, string> torre_en_posicion(int x, int y) const {
        bool a = mov_x.count(y) == 0 || mov_x.at(y).count(x) == 0;
        return { !a,   !a ? mov_x.at(y).at(x) : " "};
    }

    pair<int, int> posicion(const string& nombre) const {
        if (torres.count(nombre) == 0)throw domain_error("Torre no existente");
        return{ torres.at(nombre).x,torres.at(nombre).y };
    }

    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
        if (torres.count(nombre) == 0)throw domain_error("Torre no existente");
        bool enc = false;
        Pos p = torres.at(nombre);
        auto it = mov_y.at(p.x).find(p.y);
        switch (dir) {
        case Direccion::Norte:
            it = mov_y.at(p.x).find(p.y);
            ++it;
            if (it != mov_y.at(p.x).end()) {
                pair<int, string>p = *it;
                return p.second;
            }
            else throw domain_error("No hay torres en esa direccion");
            break;
        case Direccion::Sur:
             it = mov_y.at(p.x).find(p.y);
            if (it != mov_y.at(p.x).begin()) {
                --it;
                pair<int, string>p = *it;
                return p.second;
            }
            else throw domain_error("No hay torres en esa direccion");
            break;
        case Direccion::Este:
             it = mov_x.at(p.y).find(p.x);
            ++it;
            if (it != mov_x.at(p.y).end()) {
                pair<int, string>p = *it;
                return p.second;
            }
            else throw domain_error("No hay torres en esa direccion");
            break;
        case Direccion::Oeste:
             it = mov_x.at(p.y).find(p.x);
            if (it != mov_x.at(p.y).begin()) {
                --it;
                pair<int, string>p = *it;
                return p.second;
            }
            else throw domain_error("No hay torres en esa direccion");
            break;
        }
    }

private:
    // Añade aquí los atributos que conforman la representación
    using mapaStr = map<int, string>;
    // interna del TAD
    //




    unordered_map<string, Pos>torres;
    unordered_map<int, mapaStr>mov_x;
    unordered_map<int, mapaStr>mov_y;
    // 
    // También puedes añadir métodos auxiliares privados

};



//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst, nombre; int x, y; Direccion dir;
    cin >> inst;
    if (!cin) return false;
    Desierto desierto;
    while (inst != "FIN") {
        try {
            if (inst == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (inst == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (inst == "posicion") {
                cin >> nombre;
                auto [x, y] = desierto.posicion(nombre);
                cout << x << ' ' << y << '\n';
            }
            else if (inst == "torre_en_posicion") {
                cin >> x >> y;
                auto [hay, nombre] = desierto.torre_en_posicion(x, y);
                if (hay) cout << "SI " << nombre << '\n';
                else cout << "NO\n";
            }
            else {
                cin >> nombre >> dir;
                nombre = desierto.torre_mas_cercana(nombre, dir);
                cout << nombre << '\n';
            }
        }
        catch (domain_error& e) {
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

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
