//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la representación empleada. 




// Indicar el coste de cada método en un comentario al principio del método.





#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector> 
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std; 
// añade las librerías de la STL que necesites



using artista = std::string;
using obra = std::string;

// Elige el tipo representante adecuado para el TAD GaleriaArte e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.

class galeriaArte {

    // escribe aquí los atributos privados
    
public:
    galeriaArte(): maxVenta(0) {}
    
    void nueva_obra(obra const& c, artista const& a, int p) { //O(1) 
        if (mapa_obras.count(c)) throw invalid_argument("Obra ya en la galería"); 
        else {
            mapa_obras.insert({ c, InfoObra{p,lista_obras.insert(lista_obras.end(), c), a} }); 
            mapa_artistas[a].obras_del_artista.insert(c); 
        }
    }
    
    void venta_obra (obra const& c) { //O(1) 
        InfoObra& infoObra = getInfoObra(c); 
        InfoArtista& infoArtista = getInfoArtista(infoObra.artista); 

        lista_obras.erase(infoObra.it); 
        infoArtista.obras_del_artista.erase(c); 
        infoArtista.ventas += infoObra.precio; 

        anyadirAlMax(infoObra.artista, infoArtista); 

        mapa_obras.erase(c); 
    }
    
    std::vector<artista> mas_vendidos() const { //
        vector<artista> v; 
        for (const artista& a : artistas_mas_vendidos) v.push_back(a); 
        return v; 
    }
    
    std::vector<obra> obras_por_antiguedad(int k) const {
        vector<obra> v; 
        int i = 0; 
        auto it = lista_obras.begin(); 
        while (i < k && it != lista_obras.end()) v.push_back(*it++); 
        return v; 
    }

private: 
    
    struct InfoObra {
        int precio; 
        list<obra>::iterator it; 
        artista artista; 
    };

    struct InfoArtista { 
        unordered_set<obra> obras_del_artista; 
        int ventas; 
    };

    list<obra> lista_obras; 
    unordered_map<artista, InfoArtista> mapa_artistas; 
    unordered_map<obra, InfoObra> mapa_obras; 

    int maxVenta; 
    set<artista> artistas_mas_vendidos; 

    InfoArtista& getInfoArtista(const artista& art) { //O(1) 
        auto it = mapa_artistas.find(art); 
        if (it == mapa_artistas.end()) throw invalid_argument("Artista no existente");
        else return it->second; 
    }

    const InfoArtista& getInfoArtista(const artista& art) const { //O(1)
        auto it = mapa_artistas.find(art);
        if (it == mapa_artistas.end()) throw invalid_argument("Artista no existente");
        else return it->second;
    }

    InfoObra& getInfoObra(const obra& ob) { //O(1)
        auto it = mapa_obras.find(ob);
        if (it == mapa_obras.end()) throw invalid_argument("Obra no existente");
        else return it->second;
    }

    const InfoObra& getInfoObra(const obra& ob) const { //O(1)
        auto it = mapa_obras.find(ob);
        if (it == mapa_obras.end()) throw invalid_argument("Obra no existente");
        else return it->second;
    }

    void anyadirAlMax(const artista& art ,const InfoArtista& info) { //O(A + log A), donde A es el número de artistas, caso peor. Pero si se divide el coste de eliminar un artista al insertarlo, saldría amortizado constante si se elimina, log A si no
        if (info.ventas > maxVenta) {
            maxVenta = info.ventas;
            artistas_mas_vendidos.clear(); //O(A) 
            artistas_mas_vendidos.insert(art);
        }
        else if (info.ventas == maxVenta) artistas_mas_vendidos.insert(art); //como no admite duplicados...
    }
};





// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    std::string op;
    std::cin >> op;
    if (!std::cin) return false;
    
    galeriaArte galeria;
    while (op != "FIN") {
        try {
            if (op == "nueva_obra") {
                obra c; artista a; int p;
                std::cin >> c >> a >> p;
                galeria.nueva_obra(c,a,p);
            }
            else if (op == "venta_obra") {
                obra c; 
                std::cin >> c;
                galeria.venta_obra(c);
            }
            else if (op == "mas_vendidos") {
                std::vector<artista> sol = galeria.mas_vendidos();
                std::cout << "Los artistas que mas han vendido son:\n";
                for (auto n : sol) std::cout << n << '\n';
            }
            else if (op == "obras_por_antiguedad") {
                int k; 
                std::cin >> k;
                std::vector<obra> v = galeria.obras_por_antiguedad(k);
                std::cout << "Obras mas antiguas en la galeria:\n";
                for (obra o : v) std::cout  << o << '\n';
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
    std::ifstream in("casos3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif 
    
    while (resuelveCaso()) ;
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
  
    return 0;
}

