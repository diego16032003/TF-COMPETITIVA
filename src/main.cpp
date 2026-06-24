#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include "../include/FileAccess.h"
#include "../include/Indexer.h"
#include "../include/Algorithms.h"

void mostrarMenu() {
    std::cout << "\n=====================================" << std::endl;
    std::cout << "    SISTEMA INTELIGENTE AIRBNB       " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "1. Buscar alojamiento por ID Exacto " << std::endl;
    std::cout << "2. Buscar alojamientos por Nombre " << std::endl;
    std::cout << "3. Ver los Top K alojamientos mas baratos" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Elija una opcion: ";
}

int main() {
    std::string rutaCSV = "data/listings.csv"; 
    
    std::cout << "Iniciando carga de datos..." << std::endl;
    std::vector<Listing> misAlojamientos = cargarDatasetCSV(rutaCSV);

    Indexer miIndice;
    miIndice.construirHash(misAlojamientos);

    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore();

        // 1. BUSQUEDA POR ID
        if (opcion == 1) {
            int idBuscado;
            std::cout << "\nIngrese el ID a buscar: ";
            std::cin >> idBuscado;

            auto inicio = std::chrono::high_resolution_clock::now();
            Listing* resultado = miIndice.buscarPorId(idBuscado);
            auto fin = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> tiempo = fin - inicio;

            if (resultado != nullptr) {
                std::cout << "\n[EXITO] Encontrado en " << tiempo.count() << " ms:" << std::endl;
                std::cout << "- Nombre: " << resultado->name << " | Precio: $" << resultado->price << std::endl;
            } else {
                std::cout << "\n[ERROR] No encontrado. Tiempo: " << tiempo.count() << " ms." << std::endl;
            }
        } 
        // 2. BUSQUEDA POR NOMBRE (TRIE)
        else if (opcion == 2) {
            std::string prefijo;
            std::cout << "\nIngrese el inicio del nombre: ";
            std::getline(std::cin, prefijo);

            auto inicio = std::chrono::high_resolution_clock::now();
            std::vector<Listing*> resultados = miIndice.buscarPorNombre(prefijo);
            auto fin = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> tiempo = fin - inicio;
            
            std::cout << "\n[RESULTADO] " << resultados.size() << " coincidencias en " << tiempo.count() << " ms." << std::endl;
            int limite = std::min((int)resultados.size(), 5);
            for (int i = 0; i < limite; i++) {
                std::cout << i+1 << ". " << resultados[i]->name << std::endl;
            }
        } 
        // 3. TOP K BARATOS (HEAPS)
        else if (opcion == 3) {
            int k;
            std::cout << "\nCuantos alojamientos desea ver?: ";
            std::cin >> k;

            auto inicio = std::chrono::high_resolution_clock::now();
            std::vector<Listing*> topBaratos = Algorithms::obtenerTopKBaratos(misAlojamientos, k);
            auto fin = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> tiempo = fin - inicio;

            std::cout << "\n--- TOP " << k << " MAS BARATOS (" << tiempo.count() << " ms) ---" << std::endl;
            for (auto* item : topBaratos) {
                std::cout << "$ " << item->price << " | " << item->name << std::endl;
            }
        }

    } while (opcion != 4);

    std::cout << "Saliendo del sistema..." << std::endl;
    return 0;
}