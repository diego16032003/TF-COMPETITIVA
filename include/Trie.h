#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Listing.h"

// Nodo del Árbol de Prefijos
struct TrieNode {
    std::unordered_map<char, TrieNode*> hijos;
    std::vector<Listing*> alojamientos; // Alojamientos que coinciden hasta esta letra
};

// Clase Trie (Capa 3 y 6)
class Trie {
private:
    TrieNode* raiz;
    // Función recursiva para buscar todas las ramificaciones de un prefijo
    void recolectar(TrieNode* nodo, std::vector<Listing*>& resultados);
    // Función auxiliar para convertir a minúsculas
    std::string aMinusculas(const std::string& texto);

public:
    Trie();
    void insertar(const std::string& palabra, Listing* alojamiento);
    std::vector<Listing*> buscarPorPrefijo(const std::string& prefijo);
};