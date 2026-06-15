#pragma once
#include <vector>
#include <string>
#include "Listing.h"

// 4. Capa de Acceso a Archivos: Declaración
std::vector<Listing> cargarDatasetCSV(const std::string& rutaArchivo);