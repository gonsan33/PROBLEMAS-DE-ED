
// ALBERTO VERDEJO, E93

// las explicaciones se encuentran en el fichero set_modificado.h


#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#include "set_modificado.h"


bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;
    
    set<int> cjto;
    int elem;
    // insertamos los elementos leídos en un conjunto
    for (int i = 0; i < N; ++i) {
        cin >> elem;
        cjto.insert(elem);
    }
    
    int preguntas;
    cin >> preguntas;
    // para cada pregunta, se imprime su lower bound, si existe
    for (int i = 0; i < preguntas; ++i) {
        cin >> elem;
        auto res = cjto.lower_bound(elem);
        if (res.first) {
            cout << res.second << '\n';
        } else
            cout << "NO HAY\n";
    }
    cout << "---\n";
    return true;
}

//#define DOMJUDGE

int main() {
    
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("sample2-in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());

    
    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
