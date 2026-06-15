#pragma once
#include <vector>
#include "Listing.h"

// 6. Capa de Motor Algorítmico
class Algorithms {
public:
    // Retorna los K alojamientos más baratos usando un Heap (Cola de Prioridad)
    static std::vector<Listing*> obtenerTopKBaratos(const std::vector<Listing>& datos, int k);
};