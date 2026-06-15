#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Listing.h"
#include "Trie.h"  // <--- IMPORTANTE: Conectar con nuestro nuevo arbol

// 3. Capa de Indexacion
class Indexer {
private:
    // Estructura 1: Tabla Hash para busquedas exactas por ID
    std::unordered_map<int, Listing*> hashById;
    
    // Estructura 2: Arbol Trie para busquedas parciales por Nombre
    Trie trieNombres;

public:
    // Construye ambos indices al arrancar
    void construirHash(std::vector<Listing>& baseDatos);
    
    // 6. Motor Algoritmico: Busquedas
    Listing* buscarPorId(int id);
    std::vector<Listing*> buscarPorNombre(const std::string& prefijo);
};