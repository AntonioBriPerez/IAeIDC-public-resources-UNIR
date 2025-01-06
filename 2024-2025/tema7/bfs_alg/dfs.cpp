// COMPILE AND EXECUTE 
// THIS PROGRAM WITH C++20
// @author: Antonio Bri Perez

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// DFS usando una pila (LIFO)
vector<int> busqueda_en_profundidad(int inicio, int meta, const unordered_map<int, vector<int>>& grafo) {
    stack<int> abierta;               // Pila LIFO para nodos a explorar
    unordered_map<int, int> punteros; // Para rastrear el camino (nodo -> padre)
    vector<int> camino_actual;        // Camino a construir

    abierta.push(inicio);
    bool exito = false;

    while (!abierta.empty() && !exito) {
        int nodo = abierta.top();
        abierta.pop();

        camino_actual.push_back(nodo); // Agregar al camino actual

        // Si el nodo tiene sucesores
        if (grafo.find(nodo) != grafo.end()) {
            for (int sucesor : grafo.at(nodo)) {
                if (punteros.find(sucesor) == punteros.end()) { // No visitado
                    abierta.push(sucesor);
                    punteros[sucesor] = nodo; // Crear puntero hacia el nodo padre

                    if (sucesor == meta) { // Verificar si es el nodo meta
                        exito = true;
                        break;
                    }
                }
            }
        }

        // Si no se encontraron sucesores válidos, eliminar del camino actual
        if (!exito && abierta.empty()) {
            camino_actual.pop_back();
        }
    }

    // Si encontramos el objetivo, reconstruimos el camino
    if (exito) {
        vector<int> camino_reconstruido;
        int nodo = meta;
        while (nodo != inicio) {
            camino_reconstruido.push_back(nodo);
            nodo = punteros[nodo];
        }
        camino_reconstruido.push_back(inicio);
        reverse(camino_reconstruido.begin(), camino_reconstruido.end());
        return camino_reconstruido;
    }

    return {}; // Devolver vacío si no se encuentra solución
}

int main() {
    // Grafo representado como un mapa de listas de adyacencia
    unordered_map<int, vector<int>> grafo = {
        {1, {2, 3}},
        {2, {4, 5}},
        {3, {6}},
        {4, {}},
        {5, {}},
        {6, {}}
    };

    int inicio = 1;
    int meta = 6;

    vector<int> resultado = busqueda_en_profundidad(inicio, meta, grafo);

    if (!resultado.empty()) {
        cout << "Camino encontrado: ";
        for (int nodo : resultado) {
            cout << nodo << " ";
        }
        cout << endl;
    } else {
        cout << "Fracaso: No se encontró un camino." << endl;
    }

    return 0;
}
