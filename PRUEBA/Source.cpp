#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

// Funci�n para imprimir los elementos de un contenedor comprendidos
// entre los iteradores begin y end (excluyendo este �ltimo).
template <typename T>
void imprimir_contenedor(T begin, T end) {
    T current = begin;
    bool primero = true;
    cout << "[";
    while (current != end) {
        if (!primero) { cout << ", "; }
        cout << *current;
        primero = false;
        ++current;
    }
    cout << "]";
}

int main() {
    int array[] = { 10, 6, 9, 3, 10, 5, 23 };
    int num_elems = sizeof(array) / sizeof(int);
    vector<int> vec;

    // 1. Copia los elementos del array al vector utilizando copy()
    copy(array, array + num_elems, vec.begin());

    imprimir_contenedor(vec.begin(), vec.end()); cout << endl;


    // 2. Ordena el vector resultante utilizando sort()

    imprimir_contenedor(vec.begin(), vec.end()); cout << endl;

    // 3. Utilizando la funci�n de b�squeda binaria, determina si el 6 est�
    // dentro del vector.

    // 4. Utilizando la funci�n de b�squeda binaria, determina si el 2 est�
    // dentro del vector.

    return 0;
}