#include "../include/Trie.h"
#include <algorithm>
#include <cctype>

Trie::Trie() {
    raiz = new TrieNode();
}

std::string Trie::aMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}

void Trie::insertar(const std::string& palabra, Listing* alojamiento) {
    TrieNode* actual = raiz;
    std::string palabraMin = aMinusculas(palabra);

    for (char letra : palabraMin) {
        if (actual->hijos.find(letra) == actual->hijos.end()) {
            actual->hijos[letra] = new TrieNode();
        }
        actual = actual->hijos[letra];
    }
    // Al final de la palabra, guardamos el puntero al alojamiento
    actual->alojamientos.push_back(alojamiento);
}

void Trie::recolectar(TrieNode* nodo, std::vector<Listing*>& resultados) {
    if (!nodo) return;
    
    // Agregar los alojamientos de este nodo
    for (Listing* aloj : nodo->alojamientos) {
        resultados.push_back(aloj);
    }
    
    // Búsqueda recursiva (DFS) en todos los hijos
    for (auto& par : nodo->hijos) {
        recolectar(par.second, resultados);
    }
}

std::vector<Listing*> Trie::buscarPorPrefijo(const std::string& prefijo) {
    TrieNode* actual = raiz;
    std::vector<Listing*> resultados;
    std::string prefijoMin = aMinusculas(prefijo);

    // Navegar hasta el final del prefijo ingresado
    for (char letra : prefijoMin) {
        if (actual->hijos.find(letra) == actual->hijos.end()) {
            return resultados; // No hay coincidencias, retorna vector vacío
        }
        actual = actual->hijos[letra];
    }

    // Recolectar todas las palabras que completan este prefijo
    recolectar(actual, resultados);
    return resultados;
}