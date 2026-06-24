#pragma once
#include <vector>
#include <string>
#include "Listing.h"
#include "Trie.h"

// 3. Capa de Indexacion
class Indexer {
private:
    // Estructura 1: Tabla Hash CLASICA 
    // Usamos un numero primo grande para reducir colisiones
    int capacidadHash = 100003; 
    std::vector<std::vector<Listing*>> tablaHash;
    
    // Nuestra propia Función Hash
    int funcionHash(int id);

    // Estructura 2: Arbol Trie para busquedas parciales por Nombre
    Trie trieNombres;

public:
    Indexer(); // Constructor
    
    void construirHash(std::vector<Listing>& baseDatos);
    Listing* buscarPorId(int id);
    std::vector<Listing*> buscarPorNombre(const std::string& prefijo);
};