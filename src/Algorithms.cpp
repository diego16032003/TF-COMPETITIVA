#include "../include/Algorithms.h"
#include <queue>
#include <algorithm>

// Comparador personalizado para nuestro Heap
// Como queremos los MÁS BARATOS, usamos un Max-Heap para ir botando a los más caros.
struct ComparadorPrecio {
    bool operator()(Listing* a, Listing* b) {
        return a->price < b->price; 
    }
};

std::vector<Listing*> Algorithms::obtenerTopKBaratos(const std::vector<Listing>& datos, int k) {
    // Definimos nuestra Cola de Prioridad (Estructura Heap)
    std::priority_queue<Listing*, std::vector<Listing*>, ComparadorPrecio> maxHeap;

    for (const auto& alojamiento : datos) {
        // Ignoramos registros corruptos sin precio
        if (alojamiento.price <= 0) continue;

        // Insertamos el alojamiento actual (pasando su dirección de memoria)
        maxHeap.push(const_cast<Listing*>(&alojamiento));

        // Si el Heap supera el tamaño K, expulsamos al más caro
        if (maxHeap.size() > k) {
            maxHeap.pop(); 
        }
    }

    // Extraemos los K alojamientos restantes (los más baratos)
    std::vector<Listing*> resultados;
    while (!maxHeap.empty()) {
        resultados.push_back(maxHeap.top());
        maxHeap.pop();
    }

    // Como el Max-Heap saca primero al mayor de los baratos, invertimos la lista 
    // para que el #1 sea el más barato de absolutamente todos.
    std::reverse(resultados.begin(), resultados.end());
    
    return resultados;
}