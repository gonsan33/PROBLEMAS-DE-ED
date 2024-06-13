
/* 
 Ya que hay operaciones que buscan por alumno, como puntuación o actualizar,
 y operaciones que buscan por profesor, como examen, utilizamos dos diccionarios.
 En uno las claves serán los alumnos, y la información asociada la puntuación del
 alumno y el profesor con el que actualmente está matriculado. Este diccionario
 no necesita estar ordenado.
 En el segundo diccionario, las claves serán los profesores, y la información
 asociada el conjunto (ordenado) de alumnos matriculados con el profesor (para poder 
 recorrerlos, de forma ordenada, en la operación examen). Este segundo diccionario 
 tampoco tiene que estar ordenado por clave.
 El coste de las operaciones se indica junto a su implementación.
 */

#ifndef AUTOESCUELA
#define AUTOESCUELA

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <stdexcept>
#include <vector>
using namespace std;

using alumno = string;
using profesor = string;

class autoescuela {
    
    // para cada alumno, el profesor con el que está actualmente matriculado
    //                   y su puntuación
    unordered_map<alumno, pair<profesor,int>> alumnos;
    
    // para cada profesor, el conjunto de alumnos actualmente matriculado con él
    unordered_map<profesor, set<alumno>> profesores;
    
public:
    
    // coste logarítmico respecto al número de alumnos, O(log A),
    // por las operaciones de inserción y eliminación en un conjunto ordenado
    void alta(alumno const& a, profesor const& p) {
        auto itA = alumnos.find(a);
        if (itA == alumnos.end()) { // el alumno no estaba
            alumnos.insert({a, {p,0}});
            profesores[p].insert(a); // O(log A)
        } else { // hay que cambiarlo de profesor
            profesores[itA->second.first].erase(a); // O(log A)
            itA->second.first = p;
            profesores[p].insert(a);
        }
    }
    
    // O(1), consulta a un diccionario no ordenado
    bool es_alumno(alumno const& a, profesor const& p) {
        auto itA = alumnos.find(a);
        return itA != alumnos.end() && itA->second.first == p;
    }
    
    // O(1), consulta a un diccionario no ordenado
    int puntuacion(alumno const& a) const {
        auto itA = alumnos.find(a);
        if (itA != alumnos.end()) {
            return itA->second.second;
        } else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }
    
    // O(1), consulta y modificación en un diccionario no ordenado
    void actualizar(alumno const& a, int puntos) {
        auto itA = alumnos.find(a);
        if (itA != alumnos.end()) {
            itA->second.second += puntos;
        } else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }
    
    // coste lineal en el número de alumnos, O(A), por el recorrido del conjunto
    // asociado al profesor. Las consultas en el diccionario de alumnos para
    // saber la puntuación de cada uno son de coste constante.
    vector<alumno> examen(profesor const& p, int n) const {
        vector<alumno> res;
        auto itP = profesores.find(p);
        if (itP != profesores.end()) {
            for (alumno const& a : itP->second) { // A vueltas en el caso peor
                if (alumnos.at(a).second >= n)
                    res.push_back(a);
            }
        }
        return res;
    }
    
    // coste logaritmico en el número de alumnos, O(log A), porque hay que borrarlo
    // del conjunto ordenado asociado a su profesor
    void aprobar(alumno const& a) {
        auto itA = alumnos.find(a);
        if (itA != alumnos.end()) {
            profesores[itA->second.first].erase(a); // O(log A)
            alumnos.erase(itA);
        } else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }
    
};


#endif
