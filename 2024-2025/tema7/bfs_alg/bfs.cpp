#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

// Implementación de BFS
std::vector<int> bfs(int inicio, auto es_meta, auto generar_sucesores) {
    std::queue<int> abierta;
    std::unordered_set<int> cerrada;
    std::unordered_map<int, int> punteros;

    abierta.push(inicio);

    while (!abierta.empty()) {
        int nodo = abierta.front();
        abierta.pop();

        if (cerrada.count(nodo)) continue;
        cerrada.insert(nodo);

        if (es_meta(nodo)) {
            std::vector<int> camino;
            while (nodo) {
                camino.push_back(nodo);
                nodo = punteros.count(nodo) ? punteros[nodo] : 0;
            }
            std::reverse(camino.begin(), camino.end());
            return camino;
        }

        for (int sucesor : generar_sucesores(nodo)) {
            if (!cerrada.count(sucesor)) {
                abierta.push(sucesor);
                punteros[sucesor] = nodo;
            }
        }
    }
    return {}; // Fracaso
}

// Funciones auxiliares para el ejemplo
bool es_meta(int nodo) { return nodo == 6; }

std::vector<int> generar_sucesores(int nodo) {
    static std::unordered_map<int, std::vector<int>> grafo = {
        {1, {2, 3}}, {2, {4, 5}}, {3, {6}}, {4, {}}, {5, {}}, {6, {}}
    };
    return grafo[nodo];
}

int main() {
    int estado_inicial = 1;

    std::vector<int> resultado = bfs(estado_inicial, es_meta, generar_sucesores);

    if (!resultado.empty()) {
        std::cout << "Camino encontrado: ";
        for (int n : resultado) std::cout << n << " ";
    } else {
        std::cout << "Fracaso: No se encontró el objetivo.";
    }

    return 0;
}
