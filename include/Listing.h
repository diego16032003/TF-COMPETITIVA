#pragma once
#include <string>

// 5. Capa de Datos: Estructura base
struct Listing {
    int listing_id;
    std::string name;
    int host_id;
    std::string neighbourhood;
    float price;
    int availability_365;
};