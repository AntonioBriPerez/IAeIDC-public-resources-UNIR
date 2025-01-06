#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Función recursiva de DFS limitada por profundidad
bool dfs_limitado(int nodo, int meta, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& visitados, int limite, vector<int>& camino) {
    visitados.insert(nodo);
    camino.push_back(nodo);

    if (nodo == meta) {
        return true; // Se encontró la meta
    }

    if (limite <= 0) {
        // Alcanzó el límite de profundidad sin encontrar la meta
        camino.pop_back();
        visitados.erase(nodo);
        return false;
    }

    if (grafo.find(nodo) != grafo.end()) {
        for (int sucesor : grafo.at(nodo)) {
            if (visitados.find(sucesor) == visitados.end()) {
                if (dfs_limitado(sucesor, meta, grafo, visitados, limite - 1, camino)) {
                    return true;
                }
            }
        }
    }

    // Retroceder si no se encontró la meta en este camino
    camino.pop_back();
    visitados.erase(nodo);
    return false;
}

// Función principal de IDDFS
vector<int> busqueda_en_profundidad_iterativa(int inicio, int meta, const unordered_map<int, vector<int>>& grafo, int profundidad_maxima) {
    for (int limite = 0; limite <= profundidad_maxima; ++limite) {
        unordered_set<int> visitados;
        vector<int> camino;

        if (dfs_limitado(inicio, meta, grafo, visitados, limite, camino)) {
            return camino; // Se encontró el camino
        }
    }

    // No se encontró la meta hasta la profundidad máxima
    return {}; // Retorna un vector vacío indicando fracaso
}

int main() {
    // Grafo representado como un mapa de listas de adyacencia
    unordered_map<int, vector<int>> grafo = {
        {1, {2, 3}},
        {2, {4}},
        {3, {5}},
        {4, {6}},
        {5, {6}},
        {6, {}}
    };

    int inicio = 1;
    int meta = 6;
    int profundidad_maxima = 5; // Puedes ajustar este valor según tus necesidades

    vector<int> resultado = busqueda_en_profundidad_iterativa(inicio, meta, grafo, profundidad_maxima);

    if (!resultado.empty()) {
        cout << "Camino encontrado: ";
        for (int nodo : resultado) {
            cout << nodo << " ";
        }
        cout << endl;
    } else {
        cout << "Fracaso: No se encontró un camino hasta la profundidad máxima." << endl;
    }

    return 0;
}
