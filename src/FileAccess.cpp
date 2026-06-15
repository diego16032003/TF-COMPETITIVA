#include "../include/FileAccess.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Función para separar columnas correctamente ignorando comas dentro de comillas
std::vector<std::string> separarColumnas(const std::string& linea) {
    std::vector<std::string> columnas;
    std::string valorActual = "";
    bool dentroDeComillas = false;

    for (char c : linea) {
        if (c == '"') {
            dentroDeComillas = !dentroDeComillas;
        } else if (c == ',' && !dentroDeComillas) {
            columnas.push_back(valorActual);
            valorActual = "";
        } else {
            valorActual += c;
        }
    }
    columnas.push_back(valorActual);
    return columnas;
}

std::vector<Listing> cargarDatasetCSV(const std::string& rutaArchivo) {
    std::vector<Listing> baseDeDatosRAM;
    std::ifstream archivo(rutaArchivo);
    std::string linea, buffer;

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo en: " << rutaArchivo << std::endl;
        return baseDeDatosRAM;
    }

    // Saltamos la fila de encabezados
    std::getline(archivo, linea);

    while (std::getline(archivo, buffer)) {
        
        // --- BLOQUE BLINDADO: Detecta saltos de línea dentro de descripciones ---
        int conteoComillas = 0;
        for (char c : buffer) if (c == '"') conteoComillas++;
        
        // Si hay un número impar de comillas, significa que el salto de línea 
        // quedó atrapado en medio de un campo (ej. descripción con enter)
        while (conteoComillas % 2 != 0 && std::getline(archivo, linea)) {
            buffer += " " + linea; 
            for (char c : linea) if (c == '"') conteoComillas++;
        }
        // ------------------------------------------------------------------------

        std::vector<std::string> cols = separarColumnas(buffer);

        // Validar que la fila tenga al menos las columnas necesarias (tu archivo tiene >70)
        if (cols.size() < 50) continue; 

        Listing alojamiento;
        try {
            // Mapeo adaptado a tu dataset:
            alojamiento.listing_id = std::stoi(cols[0]);      // ID
            alojamiento.name = cols[1];                       // Nombre
            alojamiento.host_id = cols[8].empty() ? 0 : std::stoi(cols[8]); // Host ID
            alojamiento.neighbourhood = cols[4];              // Usamos room_type como barrio
            
            // Columna 43 es ttm_avg_rate (Precio)
            std::string precioStr = cols[43];
            alojamiento.price = precioStr.empty() ? 0.0f : std::stof(precioStr);
            
            // Columna 54 es ttm_available_days (Disponibilidad)
            alojamiento.availability_365 = cols[54].empty() ? 0 : std::stoi(cols[54]);

            baseDeDatosRAM.push_back(alojamiento);
        } catch (...) {
            // Fila con datos no numéricos inválidos: la saltamos
        }
    }

    archivo.close();
    std::cout << "Carga exitosa: " << baseDeDatosRAM.size() << " registros subidos." << std::endl;
    return baseDeDatosRAM;
}