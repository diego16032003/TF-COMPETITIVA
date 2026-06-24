#include "../include/Indexer.h"
#include <iostream>

// Constructor: Inicializa la tabla Hash con la cantidad de baldes vacíos
Indexer::Indexer() {
    tablaHash.resize(capacidadHash);
}

// FUNCION HASH MATEMÁTICA
int Indexer::funcionHash(int id) {
    return id % capacidadHash;
}

// Función que construye TODOS los índices al iniciar
void Indexer::construirHash(std::vector<Listing>& baseDatos) {
    std::cout << "Construyendo indices en memoria RAM..." << std::endl;
    for (size_t i = 0; i < baseDatos.size(); i++) {
        
        // 1. Inserción en Tabla Hash Clásica (Manejo de colisiones por Encadenamiento)
        int posicion = funcionHash(baseDatos[i].listing_id);
        tablaHash[posicion].push_back(&baseDatos[i]);
        
        // 2. Indice Trie para los nombres (Búsqueda parcial)
        trieNombres.insertar(baseDatos[i].name, &baseDatos[i]);
    }
    std::cout << "Tabla Hash y Arbol Trie (Nombres) operativos." << std::endl;
}

// ---------------------------------------------------------
// FUNCIONES DE BÚSQUEDA
// ---------------------------------------------------------

// Búsqueda Exacta en O(1) usando nuestra tabla Hash
Listing* Indexer::buscarPorId(int id) {
    int posicion = funcionHash(id);
    
    for (Listing* alojamiento : tablaHash[posicion]) {
        if (alojamiento->listing_id == id) {
            return alojamiento; // ¡Lo encontramos!
        }
    }
    return nullptr; // Si el bucle termina, el ID no existe
}

// Búsqueda Parcial en O(L) usando el Árbol Trie
std::vector<Listing*> Indexer::buscarPorNombre(const std::string& prefijo) {
    return trieNombres.buscarPorPrefijo(prefijo);
}