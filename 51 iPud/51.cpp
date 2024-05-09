
// ALBERTO VERDEJO

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <list>
#include <unordered_map>
#include <fstream>
#include <stack>
#include <algorithm>
using namespace std;

using cancion = string;
using artista = string;

class iPud {
public:
   iPud()  {
       ttotal = 0; 
   
   }
   
   void addSong(cancion S, artista A, int D) {
       if (canciones.count(S)) throw std::domain_error("addSong");
       else canciones[S] = Song{A,D,lista.end(),recientes.end()};
   }
   
   void addToPlaylist(cancion S) {
       if(!canciones.count(S)) throw  std::domain_error("addToPlaylist");
       Song& song = canciones.at(S); 
       if (song.it_lista == lista.end() ) {
           //hay que insertarlo en la lista 
           song.it_lista = lista.insert(lista.end(), S); 
           //se añade el tiempo 
           this->ttotal += song.dur; 
       }
   }
   
   cancion current() const {
       if(lista.size() == 0) throw std::domain_error("current");
       return *lista.begin();
   }
   
   void play() {
       if (lista.size() > 0) {
           string& s = lista.front(); 
           
           auto nuevo_it = recientes.insert(recientes.end(), s); 

           Song& song = canciones.at(s); 
           lista.pop_front(); 

           ttotal -= song.dur; 
           song.it_lista = lista.end(); 
           
           if (song.it_recientes != recientes.end()) { //hay que dejar solo la última reproducción
               recientes.erase(song.it_recientes); 
           }

           song.it_recientes = nuevo_it; 
       }
   }
   
   int totalTime() const {
       return ttotal; 
   }
   
   list<cancion> recent(int N) const {
       list<cancion> l; 
       int i = 0; 
       for (auto it = recientes.rbegin(); it != recientes.rend() && i < N; ++it) {
           l.push_back(*it); 
           ++i; 
       }
       return l; 
   }
   
   void deleteSong(cancion S) {
       if (canciones.count(S)) {
           Song& song = canciones.at(S); 
           if (song.it_lista != lista.end()) {
               lista.erase(song.it_lista);
               ttotal -= song.dur; 
           }
           if (song.it_recientes != recientes.end()) recientes.erase(song.it_recientes); 
           canciones.erase(S); 
       }
   }

private:

    list<cancion> lista;
    list<cancion> recientes;


    struct Song {
        artista artist; 
        int dur; 
        list<cancion>::iterator it_lista;
        list<cancion>::iterator it_recientes; 
    };
    unordered_map<cancion,Song> canciones;


    int ttotal = 0; 
};


bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            } else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlaylist(tit);
            } else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            } else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                } catch (domain_error & e) {
                    cout << "No hay canciones en la lista\n";
                }
            } else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            } else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            } else { // if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            }
        } catch (domain_error & e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main(){
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  while (resuelve()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif


  return 0;
}
