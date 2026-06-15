#include "../include/Indexer.h"
#include <iostream>

void Indexer::construirHash(std::vector<Listing>& baseDatos) {
    std::cout << "Construyendo indices en memoria RAM..." << std::endl;
    for (size_t i = 0; i < baseDatos.size(); i++) {
        hashById[baseDatos[i].listing_id] = &baseDatos[i];
        trieNombres.insertar(baseDatos[i].name, &baseDatos[i]);
    }
    std::cout << "Indice Hash (IDs) y Arbol Trie (Nombres) operativos." << std::endl;
}

Listing* Indexer::buscarPorId(int id) {
    if (hashById.find(id) != hashById.end()) {
        return hashById[id];
    }
    return nullptr; 
}

std::vector<Listing*> Indexer::buscarPorNombre(const std::string& prefijo) {
    return trieNombres.buscarPorPrefijo(prefijo);
}