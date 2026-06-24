#pragma once
#include <vector>
#include <string>
#include "Listing.h"

// Nodo del Arbol de Prefijos Clasico 
struct TrieNode {
    // Un puntero para cada caracter posible
    TrieNode* hijos[256]; 
    std::vector<Listing*> alojamientos; // Alojamientos que terminan en esta rama

    // Constructor del nodo: inicializa todos los caminos en nulo
    TrieNode() {
        for (int i = 0; i < 256; i++) {
            hijos[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* raiz;
    void recolectar(TrieNode* nodo, std::vector<Listing*>& resultados);
    std::string aMinusculas(const std::string& texto);

public:
    Trie();
    void insertar(const std::string& palabra, Listing* alojamiento);
    std::vector<Listing*> buscarPorPrefijo(const std::string& prefijo);
};